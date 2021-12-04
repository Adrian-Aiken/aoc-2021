#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define ROW     vector<int>
#define BOARD   vector<ROW> 

using namespace std;

vector<int> split (const string &s, char delim) {
    vector<int> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) { 
        result.push_back(stoi(item));
    }

    return result;
}

bool checkBoard (BOARD board) {
    // Check rows
    for (auto row : board) {
        bool pass = true;
        for (auto space : row) {
            if (space == -1) continue;
            pass = false;
            break;
        }
        if (pass) return true;
    }

    // Check columns (trickier?)
    for (int i = 0; i < 5; i++) {
        bool pass = true;
        for (int j = 0; j < 5; j++) {
            if (board.at(j).at(i) == -1) continue;
            pass = false;
            break;
        }
        if (pass) return true;
    }

    return false;
}

int main()
{
    ifstream input; string line;
    input.open("input.txt");

    // Read in random numbers
    input >> line;
    ROW numbers = split(line, ',');

    // Construct boards
    vector<BOARD> boards;
    input >> line;
    while (!input.eof()) { // initial line blank
        BOARD board;
        for (int i = 0; i < 5; i++) {
            ROW row;
            for (int j = 0; j < 5; j++)  {
                row.push_back(stoi(line));
                input >> line;
            }
            board.push_back(row);
        }
        boards.push_back(board);
    }

    // Run simulation
    for (auto callout : numbers) {
        // Mark called out number
        for (int i = 0; i < boards.size(); i++)
        for (int j = 0; j < 5; j++)
        for (int k = 0; k < 5; k++)
            if (boards[i][j][k] == callout)
                boards[i][j][k] = -1;

        // Check boards for a winner
        for (int b = 0; b < boards.size(); b++) {
            if (checkBoard(boards[b])) {
                // Calculate sum of winning board
                int sum = 0;
                for (auto row : boards[b])
                for (auto num : row)
                    if (num != -1)
                        sum += num;

                cout << "Winner! Board [" << b << "] will give a winning score!\n"
                     << "\n\tWinning callout: " << callout
                     << "\n\tBoard sum: " << sum
                     << "\n\tFinal score: " << callout * sum
                     << "\n\n";

                return 0;
            }
        }
    }

    cout << "No winner. Too bad!";
}