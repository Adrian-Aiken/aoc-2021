#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FINAL_SCORE 1000

using namespace std;

int dRoll = -1, dieRolls = 0;
int getDRoll() { dieRolls++; ++dRoll %= 100; return dRoll+1; }

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string ref, line;
    input.open(argv[1]);

    vector<int> pawns;
    vector<int> scores;
    int player = 0;

    while (!input.eof()) {
        std::getline(input, line);
        pawns.push_back(stoi(line.substr(line.length()-1)));
        scores.push_back(0);
    }

    while (true) {
        int roll = (getDRoll() + getDRoll() + getDRoll() + pawns[player]) % 10;
        if (roll == 0) roll = 10;
        pawns[player] = roll;
        scores[player] += roll;

        if (scores[player] >= FINAL_SCORE) break;
        player = (player + 1) % pawns.size();
    }

    // Output for part 1
    printf("Losing score : %d\nDice rolls   : %d\nAnswer       : %d", scores[(player+1)%pawns.size()], dieRolls, dieRolls*scores[(player+1)%pawns.size()]);
}