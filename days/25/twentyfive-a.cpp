#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    vector<string> board;
    while (getline(input, line))
        board.push_back(line);

    int h = board.size(), w = board[0].size();
    int steps = 0;
    while(true) {
        steps++;

        vector<string> next = board;
        // 1: East facing cucumbers
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (next[i][j] == '>' && board[i][(j+1)%w] == '.') {
                    next[i][j] = '.';
                    next[i][(j+1)%w] = '>';
                    j++;
                } 
            }
        }

        // 2: South facing cucumbers
        set<pair<int, int>> moved;
        for (int i = 0; i < h; i++) {
            string nextLine;
            for (int j = 0; j < w; j++) {
                if (next[i][j] == 'v' && next[(i+1)%h][j] == '.' 
                    && moved.find(pair(i, j))       == moved.end()
                    && moved.find(pair((i+1)%h, j)) == moved.end()) {
                    next[i][j] = '.';
                    next[(i+1)%h][j] = 'v';
                    moved.insert(pair(i, j));
                    moved.insert(pair(i+1, j));
                }
            }
        }

        //printf("After %d steps:\n", steps);
        //for (auto n: next) cout << n << endl;
        //cout << endl;

        if (board == next) {
            printf("Cucumbers stopped after [%d] steps!\n", steps);
            return 0;
        }

        board = next;
    }
}