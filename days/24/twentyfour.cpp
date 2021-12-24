#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#define PROG_LEN 18

using namespace std;

class ALU {
    private:
    vector<string> program;

    public:
    int w, x, y, z;

    ALU(){}
    ALU(vector<string> prog) { program = prog; w = 0; x = 0; y = 0; z = 0; }
    //void Print() { printf("W = [%2.1d]\tX = [%2.1d]\tY = [%2.1d]\tZ = [%2.1d]\n", w, x, y, z); }

    void RunProgram(string input) {
        int a, b;
        map<char, int> s; // State
        s['w'] = 0; s['x'] = 0; s['y'] = 0; s['z'] = 0;
        for (auto i: program) {
            if (i[1] != 'n') { // Not Input 
                a = i[6] >= 'w' && i[6] <= 'z';
                if (!a) b = stoi(i.substr(6));
            }

            switch(i[1]) { // Second character is unique for each instruction
                case 'n': s[i[4]] = input[0] - '0'; input.erase(0,1); break; // iNput
                case 'd': s[i[4]] += a ? s[i[6]] : b; break; // aDd
                case 'u': s[i[4]] *= a ? s[i[6]] : b; break; // mUltiply
                case 'i': s[i[4]] /= a ? s[i[6]] : b; break; // dIvide
                case 'o': s[i[4]] %= a ? s[i[6]] : b; break; // mOdulo
                case 'q': s[i[4]] = s[i[4]] == (a ? s[i[6]] : b); break; // eQual
            }
            //printf("W = [%2.1d]\tX = [%2.1d]\tY = [%2.1d]\tZ = [%2.1d]\t%s\n", s['w'], s['x'], s['y'], s['z'], i.c_str());
        }
        w = s['w']; x = s['x']; y = s['y']; z = s['z'];
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string ref, line;
    input.open(argv[1]);

    vector<string> slice;
    while (getline(input, line)) {
        slice.push_back(line);
    }

    for (char e = '1'; e <= '9'; e++) 
    for (char f = '1'; f <= '9'; f++) 
    {
        ALU alu = ALU(slice);
        string s = "51147191161261";
        s[0] = e; s[13] = f;
        alu.RunProgram(s);
        if (alu.z <= pow(26, 0))
            printf("[%c][%c]: %d\n", e, f, alu.z);
    }
}