#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define p pair<int,int>
#define LENGTH 50
#define SIZE (LENGTH * 2) + 1

using namespace std;

struct step {
    bool on;
    p xRange, yRange, zRange;
};

int countOn(bool core[SIZE][SIZE][SIZE]) {
    int count = 0;
    for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
    for (int z = 0; z < SIZE; z++)
        if (core[x][y][z]) count++;
    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string command, line;
    input.open(argv[1]);

    vector<step> steps;
    while (!input.eof()) {
        input >> command;
        input >> line;

        step s;
        s.on = command == "on";

        int i = 2; string foo = "";
        while (line[i] != '.') foo += line[i++];
        s.xRange.first = stoi(foo);
        i+= 2; foo = "";
        while (line[i] != ',') foo += line[i++];
        s.xRange.second = stoi(foo);
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.yRange.first = stoi(foo);
        i+= 2; foo = "";
        while (line[i] != ',') foo += line[i++];
        s.yRange.second = stoi(foo);
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.zRange.first = stoi(foo);
        i+= 2; foo = "";
        while (i <= line.size()) foo += line[i++];
        s.zRange.second = stoi(foo);

        steps.push_back(s);
    }

    // Initialize the core
    bool core[SIZE][SIZE][SIZE] = {};

    for (auto step: steps) {
        // Ignore steps that are out of range
        if (step.xRange.first < -50 || step.xRange.first > 50) continue;

        for (int x = step.xRange.first; x <= step.xRange.second; x++)
        for (int y = step.yRange.first; y <= step.yRange.second; y++)
        for (int z = step.zRange.first; z <= step.zRange.second; z++)
            core[LENGTH+x][LENGTH+y][LENGTH+z] = step.on;

        printf("Light count: %d\n", countOn(core));
    }
}