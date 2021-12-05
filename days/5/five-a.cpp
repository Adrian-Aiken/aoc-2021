#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 1000;
int board[BOARD_SIZE][BOARD_SIZE] = {};

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    int i = -1;
    while (!input.eof()) {
        getline(input, line, ','); int x1 = stoi(line);
        getline(input, line, ' '); int y1 = stoi(line);
        input >> line; // Toss the arrow
        getline(input, line, ','); int x2 = stoi(line);
        getline(input, line, '\n'); int y2 = stoi(line);

        // Vertical case  
        if (x1 == x2) {
            auto pair = std::minmax({y1, y2});
            for (int i = pair.first; i <= pair.second; i++) board[x1][i]++;
        }

        // Horizontal case
        if (y1 == y2) {
            auto pair = std::minmax({x1, x2});  
            for (int i = pair.first; i <= pair.second; i++) board[i][y1]++;
        }

        // All other cases tossed for now
    }

    // Count crossing paths
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[i][j] > 1)
            count++;

    cout << "Number of spaces to avoid: " << count << "\n";
}