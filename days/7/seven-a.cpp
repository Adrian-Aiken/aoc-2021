#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    vector<int> crabs;
    int maxPos = 0;

    while (!input.eof()) {
        getline(input, line, ',');
        int crabPos = stoi(line);
        crabs.push_back(crabPos);

        if (crabPos > maxPos) maxPos = crabPos;
    }

    // Brute force it; check the fuel needed for all positions
    int bestPos = 0, bestFuel = INT_MAX;

    for (int i = 0; i < maxPos; i++) {
        int curFuel = 0;
        for (auto crab: crabs)
            curFuel += abs(crab - i);

        if (curFuel < bestFuel) {
            bestPos = i;
            bestFuel = curFuel;
        }
    }

    cout << "======================================\n"
         << "Best Position: " << bestPos << "\n"
         << "Fuel spent:    " << bestFuel << "\n"
         << "======================================\n";
}