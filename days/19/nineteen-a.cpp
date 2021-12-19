#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Beacon;
class Beacon { 
    public:
    int x, y, z;
    Beacon(){};
    Beacon(int _x, int _y, int _z) { x = _x; y = _y; z = _z; }

    string offsetHash(Beacon b) { stringstream s; s << "[" << b.x-x << "," << b.y-y << "," << b.z-z << "]"; return s.str(); }
    bool operator==(const Beacon & b) { return (x == b.x) && (y == b.y) && (z == b.z); }
    bool operator< (const Beacon & b) { return x < b.x; }
};

void printScanner(vector<Beacon> s) {
    for (auto b: s)
        printf("%d,%d,%d\n", b.x, b.y, b.z);

}

#define IT(i, x, y, z) case i: for (auto b: ref) s.push_back(Beacon(x, y, z)); break;
vector<Beacon> getIteration(vector<Beacon> ref, int iteration) {
    vector<Beacon> s;
    switch (iteration) {
        IT( 0, b.x, b.y, b.z) IT( 1, b.x,-b.z, b.y) IT( 2, b.x,-b.y,-b.z) IT( 3, b.x, b.z,-b.y)
        IT( 4, b.y, b.z, b.x) IT( 5, b.y,-b.x, b.z) IT( 6, b.y,-b.z,-b.x) IT( 7, b.y, b.x,-b.z)
        IT( 8, b.z, b.x, b.y) IT( 9, b.z,-b.y, b.x) IT(10, b.z,-b.x,-b.y) IT(11, b.z, b.y,-b.x)
        IT(12,-b.z,-b.y,-b.x) IT(13,-b.z, b.x,-b.y) IT(14,-b.z, b.y, b.x) IT(15,-b.z,-b.x, b.y)
        IT(16,-b.y,-b.x,-b.z) IT(17,-b.y, b.z,-b.x) IT(18,-b.y, b.x, b.z) IT(19,-b.y,-b.z, b.x)
        IT(20,-b.x,-b.z,-b.y) IT(21,-b.x, b.y,-b.z) IT(22,-b.x, b.z, b.y) IT(23,-b.x,-b.y, b.z)
    }
    return s;
};

Beacon findTransform(vector<Beacon> a, vector<Beacon> b, string offset) {
    for (auto i: a)
    for (auto j: b)
        if (i.offsetHash(j) == offset)
            return Beacon(i.x-j.x, i.y-j.y, i.z-j.z);
    return Beacon();
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);
    
    queue<vector<Beacon>> scanners;
    vector<Beacon> scanner, grid;
    while (!input.eof()) {
        std::getline(input, line);
        if (line.find("scanner") != string::npos) {
            if (scanner.size() > 0) scanners.push(scanner);
            scanner = vector<Beacon>();
        } else if (line == "") {
            continue;
        } else {
            vector<int> vals;
            int c1 = line.find(",");
            int c2 = line.find(",", c1+1);
            int x = stoi(line.substr(0,c1));
            int y = stoi(line.substr(c1+1, c2-c1));
            int z = stoi(line.substr(c2+1));
            scanner.push_back(Beacon(x, y, z));
        }
    }
    if (scanner.size() > 0) scanners.push(scanner);

    // Initialize reference beacon as beacon 0
    grid = scanners.front();
    std::sort(grid.begin(), grid.end());
    scanners.pop();

    while (!scanners.empty()) {
        vector<Beacon> s = scanners.front();
        scanners.pop();

        pair<int, int> maxPair = pair(-1, 0);
        string maxOffset = "";

        for (int i = 0; i < 24; i++) {
            map<string, int> offsets;
            map<int, int> counts;
            vector<Beacon> iteration = getIteration(s, i);
            for (auto ref: grid)
            for (auto b: iteration)
                offsets[ref.offsetHash(b)]++;

            for (auto dist: offsets)
                counts[dist.second]++;

            for (auto c: counts) {
                if (c.first >= 12 && c.first > maxPair.second) {
                    maxPair = pair(i, c.first);
                    for (auto n: offsets)
                        if (n.second == c.first)                       
                            maxOffset = n.first;
                }
            }
        }

        if (maxPair.first == -1) {
            scanners.push(s);
            continue;
        }

        vector<Beacon> matching = getIteration(s, maxPair.first);
        Beacon t = findTransform(grid, matching, maxOffset);

        int dupeCount = 0;
        vector<Beacon> candidates;
        for (auto m: matching) {
            Beacon candidate = Beacon(m.x+t.x, m.y+t.y, m.z+t.z);
            bool dupe = false;
            for (auto g: grid)
                if (candidate == g) {
                    dupe = true;
                    dupeCount++;
                    break;
                }
            
            if (!dupe) candidates.push_back(candidate);
        }

        if (dupeCount < maxPair.second) {
            scanners.push(s);
            continue;
        }

        vector<Beacon> newGrid;
        sort(candidates.begin(), candidates.end());
        sort(grid.begin(), grid.end());
        merge(grid.begin(), grid.end(), candidates.begin(), candidates.end(), back_inserter(newGrid));
        newGrid.erase(unique(newGrid.begin(), newGrid.end()), newGrid.end());
        grid = newGrid;

        printf("[%2.1d left] Scanner orientation: [%2.1d] offset seen [%2.1d] times      | Offset: [%5.1d,%5.1d,%5.1d]      | Grid size now [%3.1d]\n", scanners.size(), maxPair.first, maxPair.second, t.x, t.y, t.z, grid.size());
    }
}