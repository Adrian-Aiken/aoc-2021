#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    vector<vector<int>> map;

    while (!input.eof()) {
        input >> line;
        vector<int> row;
        for (auto num: line)
            row.push_back(num - '0');
        map.push_back(row);
    }

    int totalRisk = 0;

    for (int x = 0; x < map.size(); x++)
    for (int y = 0; y < map[x].size(); y++) {
        int c = map[x][y];
        if (y > 0               && c >= map[x][y-1]) continue; // Left
        if (x > 0               && c >= map[x-1][y]) continue; // Up
        if (y < map[x].size()-1 && c >= map[x][y+1]) continue; // Right
        if (x < map.size()-1    && c >= map[x+1][y]) continue; // Down
        totalRisk += 1 + map[x][y];
    }

    cout << "Total calculated risk: " << totalRisk << endl;
}