#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define BOARD vector<vector<int>>
using namespace std;

const int DAYS = 100;
const int WIDTH = 10;

int flashes = 0;
BOARD board;

void flash(int x, int y) {
    if (board[x][y] <= 9) return;

    flashes++;
    board[x][y] = 0;
    for (int i = max(x-1, 0); i <= min(x+1, WIDTH-1); i++)
    for (int j = max(y-1, 0); j <= min(y+1, WIDTH-1); j++)
        // 0 = just flashed; don't re-flash
        if (board[i][j] != 0)
            // If threshold met, recursively flash
            if (++board[i][j] > 9)
                flash(i, j);
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    while (!input.eof()) {
        input >> line;
        vector<int> row;
        for (auto a: line) row.push_back(a - '0');
        board.push_back(row);
    }

    int steps = 0;
    while (true) {
        steps++;
        // Step 1: increase energy
        for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < WIDTH; y++)
            board[x][y]++;

        // Step 2: flash area
        for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < WIDTH; y++)
            flash(x, y);
            
        // step 3: Check for full syncronicity
        int octoSum = 0;
        for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < WIDTH; y++)
            octoSum += board[x][y];

        if (octoSum == 0) break;
    }

    cout << "Octopuses syncronized after " << steps << " steps (" << flashes << " total flashes)\n";
}