#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream input;
    input.open("input");

    int depth = 0, pos = 0, aim = 0, val;
    string line, sval;

    while (std::getline(input, line, ' '))
    {
        std::getline(input, sval, '\n');
        val = stoi(sval);

        if (line == "down")             aim += val;
        else if (line == "up")          aim -= val;
        else if (line == "forward") {   pos += val; depth += aim * val; }
    }
    
    cout << "Current position: [D" << depth << ", H" << pos <<"]\n"
        << "\t(The answer is " << depth * pos << ")";
}