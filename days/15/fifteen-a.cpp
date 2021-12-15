#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define NODE pair<int, pair<int, int>>

using namespace std;

struct safer {
    bool operator()(const NODE& a, const NODE& b) {
        return a.first > b.first;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    vector<vector<int>> cavern;
    vector<NODE> riskQueue;

    // Populate cavern
    while (!input.eof()) {
        input >> line;
        vector<int> row;
        for (auto c: line) 
            row.push_back(c -'0');
        cavern.push_back(row);
    }
    cavern[0][0] = 0; // Starting position does not count
    
    int width = cavern[0].size() - 1;
    int height = cavern.size() - 1;

    // Seed heap
    riskQueue.push_back(NODE(0, pair<int, int>(0, 0)));
    make_heap(riskQueue.begin(), riskQueue.end(), safer());

    while (!riskQueue.empty()) {
        NODE node = riskQueue.front();
        pop_heap(riskQueue.begin(), riskQueue.end(), safer());
        riskQueue.pop_back();

        int risk = node.first;
        int x = node.second.first;
        int y = node.second.second;

        // Check if the end
        if (node.second.first == height && node.second.second == width) {
            cout << "Total risk is: " << node.first << endl;
            return 0;
        }

        // Top, Bottom, Left, Right
        if (x > 0 && cavern[x-1][y] > 0) { 
            riskQueue.push_back(NODE(risk + cavern[x-1][y], pair<int, int>(x-1, y)));
            push_heap(riskQueue.begin(), riskQueue.end(), safer());
            cavern[x-1][y] = -1;
        }
        if (x < width && cavern[x+1][y] > 0) { 
            riskQueue.push_back(NODE(risk + cavern[x+1][y], pair<int, int>(x+1, y)));
            push_heap(riskQueue.begin(), riskQueue.end(), safer());
            cavern[x+1][y] = -1;
        }
        if (y > 0 && cavern[x][y-1] > 0) { 
            riskQueue.push_back(NODE(risk + cavern[x][y-1], pair<int, int>(x, y-1)));
            push_heap(riskQueue.begin(), riskQueue.end(), safer());
            cavern[x][y-1] = -1;
        }
        if (y < height && cavern[x][y+1] > 0) { 
            riskQueue.push_back(NODE(risk + cavern[x][y+1], pair<int, int>(x, y+1)));
            push_heap(riskQueue.begin(), riskQueue.end(), safer());
            cavern[x][y+1] = -1;
        }
    }
}