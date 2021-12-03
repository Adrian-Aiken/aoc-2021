#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int width = 12;

void getSums(vector<string> input, int* sums) 
{
    sums[width] = {};

    for (auto line : input)
        for (int i = 0; i < width; i++)
            if (line.at(i) == '1') sums[i]++;
}

int main()
{
    ifstream input;
    input.open("input.txt");

    string line;
    vector<string> lines;

    // Read in counts of inputs
    while (input >> line) lines.push_back(line);

    // Calculate Oxygen rating
    vector<string> oxygen (lines);
    int i = 0;
    while (oxygen.size() > 1  && i < width)
    {
        vector<string> candidates;
        int sums[width] = {};
        getSums(oxygen, sums);
        char target = sums[i] >= ((oxygen.size()+1)/2) ? '1' : '0';

        std::copy_if(oxygen.begin(), oxygen.end(), std::back_inserter(candidates),
            [&i, &target](string s){ return s.at(i) == target; });

        oxygen = candidates;
        i++;
    }

    // Calculate Oxygen rating
    vector<string> co2 (lines);
    i = 0;
    while (co2.size() > 1 && i < width)
    {
        vector<string> candidates;
        int sums[width] = {};
        getSums(co2, sums);
        char target = sums[i] >= ((co2.size()+1)/2) ? '0' : '1';
                
        std::copy_if(co2.begin(), co2.end(), std::back_inserter(candidates),
            [&i, &target](string s){ return s.at(i) == target; });

        co2 = candidates;
        i++;
    }

    int oox = stoi(oxygen.at(0), 0, 2);
    int oc2 = stoi(co2.at(0), 0, 2);

    cout << "+----------------------+\n"
         << "| Diagnostic complete! |\n"
         << "+----------------------+\n"
         << "| Oxygen:\t" << oox << "\n"
         << "|\n"
         << "| CO2:   \t" << oc2 << "\n"
         << "|\n"
         << "| Answer:\t" << oox * oc2 << "\n"
         << "+----------------------+\n";
}