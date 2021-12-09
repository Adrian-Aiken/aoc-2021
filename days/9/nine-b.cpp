#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

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

    // Calculate lowpoints for each basin
    vector<pair<int, int>> lowPoints;
    for (int x = 0; x < map.size(); x++)
    for (int y = 0; y < map[x].size(); y++) {
        int c = map[x][y];
        if (y > 0               && c >= map[x][y-1]) continue; // Left
        if (x > 0               && c >= map[x-1][y]) continue; // Up
        if (y < map[x].size()-1 && c >= map[x][y+1]) continue; // Right
        if (x < map.size()-1    && c >= map[x+1][y]) continue; // Down
        lowPoints.push_back(pair<int, int>(x, y));
    }

    // Calculate basin sizes
    vector<int> sizes;
    for (auto lowPoint: lowPoints) {
        queue<pair<int, int>> searchQueue;
        searchQueue.push(lowPoint);

        int basinSize = 0;
        while (!searchQueue.empty()) {
            pair<int, int> p = searchQueue.front();
            searchQueue.pop();

            // Ignore maxheight (9), and already searched (-1)
            if (map[p.first][p.second] == 9 || map[p.first][p.second] == -1) continue;

            basinSize++;
            map[p.first][p.second] = -1;

            // Enqueue next adjacencies
            if (p.first > 0)                searchQueue.push(pair<int, int>(p.first-1, p.second));
            if (p.second > 0)               searchQueue.push(pair<int, int>(p.first, p.second-1));
            if (p.first < map.size()-1)     searchQueue.push(pair<int, int>(p.first+1, p.second));
            if (p.second < map[0].size()-1) searchQueue.push(pair<int, int>(p.first, p.second+1));
        }
        cout << "Basin: " << basinSize << endl;
        sizes.push_back(basinSize);
    }

    sort(sizes.begin(), sizes.end(), greater<int>());

    cout << "=========================================================\n"
         << "Largest Basins Combined: " << sizes[0] * sizes[1] * sizes[2] << endl;
}