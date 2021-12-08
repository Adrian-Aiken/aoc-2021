#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    // Toss the digit values, keep read-out values
    int numFound = 0;
    while (!input.eof()) {
        // Toss up to delimiter
        getline(input, line, '|');

        // Check the read-out values
        for (int i = 0; i < 4; i++) {
            input >> line;

            if (line.size() == 2 || // 1
                line.size() == 4 || // 4
                line.size() == 3 || // 7
                line.size() == 7) { // 8
                numFound++;
            }
        }
    }

    cout << "======================================\n"
         << "Num Found: " << numFound << "\n"
         << "======================================\n";
}