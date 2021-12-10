#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

const string open =     "([{<";
const string closed =   ")]}>";
const int points[4] = {3, 57, 1197, 25137};

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    int score = 0;

    while (!input.eof()) {
        input >> line;
        stack<char> chunks;

        for (auto c: line) {
            if (open.find(c) != string::npos) {
                chunks.push(c);
            } else {
                // Chunk Valid
                if (open.find(chunks.top()) == closed.find(c)) {
                    chunks.pop();
                }
                // Chunk Invalid
                else {
                    score += points[closed.find(c)];
                    cout << "Chunk error! [" << c << "] Total points: \t" << score << "\n";
                    break;
                }

            }
        }
    }

    cout << "===========================================\n";
    cout << "\tFinal Score: " << score << endl;
}