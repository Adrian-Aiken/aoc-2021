#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct firstGreater {
    bool operator()(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    int xmin, xmax, ymin, ymax;

    while (!input.eof()) {
        input >> line;

        int i = 2; string foo = "";
        if (line[0] == 'x') {
            while (line[i] != '.')
                foo += line[i++];
            xmin = stoi(foo);
            foo = ""; i += 2;
            while (line[i] != ',')
                foo += line[i++];
            xmax = stoi(foo);
        }

        else if (line[0] == 'y') {
            while (line[i] != '.')
                foo += line[i++];
            ymin = stoi(foo);
            foo = ""; i += 2;
            while (i <= line.size())
                foo += line[i++];
            ymax = stoi(foo);
        }
    }

    // Calculate valid X velocities; namely, velocities which for at least one
    // value, will be in the target range. Fails if it stops moving without entering
    // the target area;
    vector<int> xVs; 
    for (int i = 0; i <= xmax; i++) {
        int v = i, pos = 0;
        while (v != 0) {
            pos += v--;
            if (pos >= xmin && pos <= xmax) { xVs.push_back(i); break; }
        }
    }

    // Calculate valid velocities
    vector<pair<int, pair<int, int>>> coords;
    for (auto x: xVs)
    for (int y = 0; y < 500; y++) {
        int highest = 0, v = y, pos = 0;
        while (v >= ymin) {
            pos += v--;
            highest = max(highest, pos);
            if (pos >= ymin && pos <= ymax) {
                coords.push_back(pair<int, pair<int, int>>(highest, pair<int, int>(x, y)));
                break;
            }
        }
    }

    pair<int, pair<int, int>> highest = coords[0];
    for (auto c: coords)
        if (c.first > highest.first)
            highest = c;

    printf("There are %d valid velocity pairs\n", coords.size());
    printf("The shot (%d, %d) will reach %d", highest.second.first, highest.second.second, highest.first);
}