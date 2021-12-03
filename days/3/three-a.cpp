#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream input;
    input.open("input.txt");

    string line;
    int lines = 0;
    int sums[12] = {};

    // Read in counts of inputs
    while (input >> line) {
        lines++;
        for (int i = 0; i < 12; i++)
            if (line.at(i) == '1') sums[i]++;
    }
    int hline = lines / 2;

    // Calculate Gamma and Epsilon
    int gamma = 0, epsilon = 0;
    for (int j = 0; j < 12; j++) {
        gamma <<= 1; epsilon <<= 1;
        sums[j] > hline ? gamma += 1 : epsilon += 1;
    }

    cout << "+----------------------+\n"
         << "| Diagnostic complete! |\n"
         << "+----------------------+\n"
         << "| Gamma:   " << gamma << "\n"
         << "|\n"
         << "| Epsilon: " << epsilon << "\n"
         << "|\n"
         << "| Power Consumption:\n"
         << "|    " << gamma * epsilon << "\n"
         << "+----------------------+\n";
}