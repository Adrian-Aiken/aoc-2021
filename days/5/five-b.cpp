#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 1000;
int board[BOARD_SIZE][BOARD_SIZE] = {};

int comp (int a, int b) {
    if (a > b) return -1;
    if (a < b) return 1;
    return 0;
}

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
        
        int len = max(std::abs(x1 - x2), std::abs(y1 - y2));
        int xdir = comp(x1, x2);
        int ydir = comp(y1, y2);

        for (int x = x1, y = y1, i = 0;
                i <= len;
                x += xdir, y += ydir, i++)
                board[x][y]++;
    }

    // Count crossing paths
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[i][j] > 1)
            count++;

    cout << "Number of spaces to avoid: " << count << "\n";
}