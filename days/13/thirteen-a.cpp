#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void printPaper(vector<vector<bool>> paper) {
    // Print paper
    for (int x = 0; x < paper.size(); x++) {
        for (int y = 0; y < paper[x].size(); y++)
            cout << (paper[x][y] ? "#" : ".");
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    vector<vector<bool>> paper;

    ifstream input; string line;
    input.open(argv[1]);

    // Just parse in the data first
    vector<pair<int, int>> pairs;
    int rows = 0, cols = 0;
    while (true) {
        input >> line;
        if (line == "fold") break;

        pair<int, int> coord;
        std::stringstream ss(line); string s;
        getline(ss, s, ',');
        coord.first = stoi(s);
        getline(ss, s, '\n');
        coord.second = stoi(s);

        rows = max(coord.second, rows);
        cols = max(coord.first, cols);

        pairs.push_back(coord);
    }
    rows++; cols++;

    // Set up map
    for (int x = 0; x < rows; x++) paper.push_back(vector<bool>(cols, false));

    // Mark paper
    for (auto coords: pairs) 
        paper[coords.second][coords.first] = true;
        
    // Read in folds
    while (!input.eof()) {
        input >> line;
        if (line == "fold" || line == "along") continue;

        std::stringstream ss(line);
        string dir, s;
        getline(ss, dir, '=');
        getline(ss, s, '\n');
        int foldAt = stoi(s);

        cout << "Folding along " << dir << " at: " << foldAt << endl;

        if (dir == "x") {
            // Step 1: Move Marks
            for (int y = 0; y < paper.size(); y++)
            for (int x = 0; x < cols-foldAt; x++)
                if (paper[y][foldAt+x])
                    paper[y][foldAt-x] = true;

            // Step 2: Remove folded rows
            for (int y = 0; y < paper.size(); y++)
                paper[y].erase(paper[y].begin()+foldAt, paper[y].end());
        } else if (dir == "y") {
            // Step 1: Move marks
            for (int y = 0; y < rows-foldAt; y++)
            for (int x = 0; x < paper[y].size(); x++)
                if (paper[foldAt+y][x])
                    paper[foldAt-y][x] = true;

            // Step 2: Remove folded rows
            paper.erase(paper.begin()+foldAt, paper.end());
        }

        int marks = 0;
        for (auto a: paper)
        for (auto b: a)
            if (b) marks++;
        cout << "Total marks: " << marks << endl << endl;
        break;
    }

    printPaper(paper);

}