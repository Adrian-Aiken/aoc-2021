#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define ssort(x) std::sort(x.begin(), x.end())

using namespace std;

bool matchCount (string unknown, string known, int goal) {
    int match = 0;
    for (int i = 0; i < known.size(); i++)
        if (unknown.find(known[i]) != string::npos)
            match++;

    return match == goal;
}

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    // Toss the digit values, keep read-out values
    int sumTotal = 0;
    while (!input.eof()) {
        vector<string> fives, sixes; 
        string known[10] = {};
        // Check the read-out values
        int i;
        for (i = 0; i < 10; i++) {
            input >> line;
            ssort(line);

            // Filter out 1478
            switch (line.size()) {
                case 2: known[1] = line; break;
                case 3: known[7] = line; break;
                case 4: known[4] = line; break;
                case 7: known[8] = line; break;
                case 5: fives.push_back(line); break;
                case 6: sixes.push_back(line); break;
            }   
        }

        // 3 - contains all of 7
        for (i = 0; i < 3; i++) {
            if (matchCount(fives[i], known[7], 3)) {
                known[3] = fives[i];
                fives.erase(fives.begin() + i);
                break;
            }
        }

        // 2 contains 2 of the num 4; 5 contains 3
        if (matchCount(fives[0], known[4], 2)) {
            known[2] = fives[0];
            known[5] = fives[1];
        } else {
            known[2] = fives[1];
            known[5] = fives[0];
        }

        // 6 - contains 1 seg of 1
        for (i = 0; i < 3; i++) {
            if (matchCount(sixes[i], known[1], 1)) {
                known[6] = sixes[i];
                sixes.erase(sixes.begin() + i);
                break;
            }
        }

        // 9 Contains 4 of 4; 0 contains 3
        if (matchCount(sixes[0], known[4], 4)) {
            known[9] = sixes[0];
            known[0] = sixes[1];
        } else {
            known[9] = sixes[1];
            known[0] = sixes[0];
        }

        // Finally on to the actual problem!!
        // 1) Toss the delimiter
        getline(input, line, '|');

        // 2) Loop over incoming data segments
        int data = 0;
        for (i = 0; i < 4; i++) {
            input >> line;
            ssort(line);

            data *= 10;
            for (int j = 0; j < 10; j++) {
                if (line == known[j]) {
                    data += j;
                    break;
                }
            }
        }
        sumTotal += data;
    }

    cout << "======================================\n"
         << "Num Found: " << sumTotal << "\n"
         << "======================================\n";
}