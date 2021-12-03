#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream input;
    input.open("input");

    int depth = 0, pos = 0, dist;
    string line, val;

    while (std::getline(input, line, ' '))
    {
        std::getline(input, val, '\n');
        dist = stoi(val);

        if (line == "forward")      pos += dist;
        else if (line == "down")    depth += dist;
        else if (line == "up")      depth -= dist;
    }
    
    cout << "Current position: [D" << depth << ", H" << pos <<"]\n"
        << "\t(The answer is " << depth * pos << ")";
}