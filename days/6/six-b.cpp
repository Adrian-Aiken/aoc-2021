#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_DAYS = 256;

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    unsigned long long feesh[9] = {};

    while (!input.eof()) {
        getline(input, line, ',');
        feesh[stoi(line)]++;
    }

    for (int i = 0; i < NUM_DAYS; i++) {w
        // 1) Mark fish ready for birth
        unsigned long long newFish = feesh[0];
        feesh[7] += feesh[0];

        // 2) Age all existing fish
        for (int j = 1; j < 9; j++) {
            feesh[j-1] = feesh[j];
        }

        // 3) Add in newly birthed fish
        feesh[8] = newFish;
    }

    // Sum total fish
    unsigned long long total = 0;
    for (int k = 0; k < 9; k++) 
        total += feesh[k];

    cout << "There are " << total << " fish"; 
}