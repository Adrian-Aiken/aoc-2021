#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

#define CAVES map<string, vector<string>>

using namespace std;

bool isSmall(string cave) { return (cave[0] >= 'a' && cave[0] <= 'z'); }

vector<vector<string>> nextPaths(CAVES caves, vector<string> path) {
    vector<vector<string>> nextSteps;

    for (auto neighbor: caves[path.back()]) {
        if (!isSmall(neighbor)
            || (isSmall(neighbor) && (find(path.begin(), path.end(), neighbor) == path.end()))
        ) {
            vector<string> nextStep = vector<string>(path);
            nextStep.push_back(neighbor);
            nextSteps.push_back(nextStep);
        }
    }

    return nextSteps;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string left, right;
    input.open(argv[1]);

    CAVES caves;
    while (!input.eof()) {
        getline(input, left, '-');
        getline(input, right, '\n');

        caves[left].push_back(right);
        caves[right].push_back(left);
    }

    vector<vector<string>> fullPaths;
    queue<vector<string>> toCheck;
    vector<string> startPath;
    startPath.push_back("start");
    toCheck.push(startPath);

    while (!toCheck.empty()) {
        vector<string> curPath = toCheck.front();
        toCheck.pop();

        if (curPath.back() == "end") {
            fullPaths.push_back(curPath);
        } else {
            vector<vector<string>> next = nextPaths(caves, curPath);
            for (auto path: next) toCheck.push(path);
        }
    }

    cout << "Paths: " << fullPaths.size() << endl;
}