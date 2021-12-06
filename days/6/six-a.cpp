#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_DAYS = 80;

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    vector<int> feesh;

    while (!input.eof()) {
        getline(input, line, ',');
        feesh.push_back(stoi(line));
    }

    for (int i = 0; i < NUM_DAYS; i++) {
        // 1) Age fish, keeping track of new fish
        int newFish = 0;
        for (int j = 0; j < feesh.size(); j++) {
            if (feesh[j] == 0) {
                feesh[j] = 6;
                newFish++;
            } else {
                feesh[j]--;
            }
        }

        // 2) Add new fish to the end
        while (newFish-- > 0) feesh.push_back(8);
    }

    cout << "There are " << feesh.size() << " fish";
}