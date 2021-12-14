#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

const int ITERATIONS = 40;

using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    map<string, unsigned long long> polymer;
    map<string, pair<string, string>> rules;
    input >> line;
    for (int i = 0; i < line.size()-1; i++) 
        polymer[line.substr(i, 2)]++;
    char lastElem = line[line.size()-1];

    while (!input.eof()) {
        string in, addition, out1, out2;
        input >> in;
        input >> line; // Toss arrow
        input >> addition;

        out1 = in[0] + addition;
        out2 = addition + in[1];

        rules[in] = pair<string, string>(out1, out2);
    }

    for (int i = 1; i <= ITERATIONS; i++) {
        map<string, unsigned long long> newPolymer;

        for (auto pairs: polymer) {
            pair<string, string> rule = rules[pairs.first];
            newPolymer[rule.first] += pairs.second;
            newPolymer[rule.second] += pairs.second;
        }

        polymer = newPolymer;;
    }

    map<char, unsigned long long> counts;
    unsigned long long highest = 0, lowest = ULLONG_MAX;
    for (auto c: polymer) counts[c.first[0]] += c.second;
    counts[lastElem]++;
    for (auto v: counts) {
        highest = max(highest, v.second);
        lowest = min(lowest, v.second);
    }

    cout << "Result:\t" << highest - lowest << endl;
}