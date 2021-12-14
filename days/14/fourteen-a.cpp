#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

const int ITERATIONS = 10;

using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    string polymer;
    map<char, map<char, char>> rules;
    input >> polymer;

    while (!input.eof()) {
        string pair, addition;
        input >> pair;
        input >> line; // Toss arrow
        input >> addition;
        rules[pair[0]][pair[1]] = addition[0];
    }

    cout << "Template:\t\t" << polymer << endl;

    for (int i = 1; i <= ITERATIONS; i++) {
        stringstream newPolymer;
        for (int j = 0; j < polymer.size()-1; j++) {
            newPolymer << polymer[j];
            if (rules[polymer[j]][polymer[j+1]])
                newPolymer << rules[polymer[j]][polymer[j+1]];
        }
        newPolymer << polymer[polymer.size()-1];
        polymer = newPolymer.str();

        cout << "After step " << i << " (" << polymer.size() << "):\t" << polymer << endl;
    }

    cout << endl << "========================================" << endl;

    map<char, int> counts;
    int highest = 0, lowest = INT_MAX;
    for (auto c: polymer) counts[c]++;
    for (auto v: counts) {
        highest = max(highest, v.second);
        lowest = min(lowest, v.second);
    }

    cout << "Result:\t" << highest - lowest << endl;
}