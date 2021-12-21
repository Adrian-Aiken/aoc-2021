#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <inttypes.h>

using namespace std;

#define p pair<int, int>
#define m map
#define UNIVERSE m<p, m<p, uint64_t>>
#define MAX_SCORE 21

const m<uint64_t, uint64_t> splits = { {3,1}, {4,3}, {5,6}, {6,7}, {7,6}, {8,3}, {9,1} };

int getMove(int start, int move) { return ( (start + move - 1) % 10 ) + 1; }

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string ref, line;
    input.open(argv[1]);

    // Universe = map<score, map<spaces, universes>>
    UNIVERSE u;
    uint64_t wins[2] = {};

    std::getline(input, line);
    int p1space = stoi(line.substr(line.length()-1));
    std::getline(input, line);
    int p2Space = stoi(line.substr(line.length()-1));

    u[p(0,0)][p(p1space,p2Space)] = 1;

    bool p1turn = true;
    while (u.size() != 0) {
        UNIVERSE next;

        for (auto ss: u) //ScoreSpace
        for (auto bs: ss.second) //BoardSpace
        for (auto ms: splits) { //MoveSpace
            if (p1turn) {
                p nextScore = p(ss.first.first + getMove(bs.first.first, ms.first), ss.first.second);
                if (nextScore.first >= MAX_SCORE) { wins[0] += bs.second * ms.second; continue; }
                p nextSpace = p(getMove(bs.first.first, ms.first), bs.first.second);
                next[nextScore][nextSpace] += bs.second * ms.second;
            } else {
                p nextScore = p(ss.first.first, ss.first.second + getMove(bs.first.second, ms.first));
                if (nextScore.second >= MAX_SCORE) { wins[1] += bs.second * ms.second; continue; }
                p nextSpace = p(bs.first.first, getMove(bs.first.second, ms.first));
                next[nextScore][nextSpace] += bs.second * ms.second;
            }
        }
        uint64_t numUniverses = 0;
        for (auto x: next)
        for (auto y: x.second)
            numUniverses += y.second;

        printf("Player %d turn: %" PRIu64 " finishes, %" PRIu64 " universes\n", p1turn ? 1 : 0, wins[0]+wins[1], numUniverses);

        u = next;
        p1turn = !p1turn;
    }

    cout << "\n======================================================\n\n";
    cout << "Player 1 wins: " << wins[0] << endl;
    cout << "Player 2 wins: " << wins[1] << endl << endl;

    printf("Player %d has more wins!", wins[0] > wins[1] ? 1 : 0);
}