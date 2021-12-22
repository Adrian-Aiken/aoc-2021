#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <inttypes.h>

#define p pair<int64_t,int64_t>
#define LENGTH 50
#define SIZE (LENGTH * 2) + 1

using namespace std;

vector<int> xs, ys, zs;

int findIndex(const vector<int> &arr, int item) {
    auto ret = std::find(arr.begin(), arr.end(), item);

    if (ret != arr.end())
        return ret - arr.begin();
    return -1;
}

int countOn(bool core[SIZE][SIZE][SIZE]) {
    int count = 0;
    for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
    for (int z = 0; z < SIZE; z++)
        if (core[x][y][z]) count++;
    return count;
}

vector<int> getIntersectPoints(p base, p newLine) {
    vector<int> points;
    points.push_back(base.first);
    if (newLine.first > base.first) points.push_back(newLine.first);
    if (newLine.second < base.second) points.push_back(newLine.second);
    points.push_back(base.second);
    return points;
}

class Cuboid;
class Cuboid {
    public:
    p xRange, yRange, zRange;

    Cuboid(){}
    Cuboid(p x, p y, p z) { xRange = x; yRange = y; zRange = z; }
    Cuboid(string s) {
        int i = 0; string f = "";
        while (s[i] != ',') f += s[i++];
        xRange.first = stoi(f); i++; f = "";
        while (s[i] != ',') f += s[i++];
        xRange.second = stoi(f); i++; f = "";
        while (s[i] != ',') f += s[i++];
        yRange.first = stoi(f); i++; f = "";
        while (s[i] != ',') f += s[i++];
        yRange.second = stoi(f); i++; f = "";
        while (s[i] != ',') f += s[i++];
        zRange.first = stoi(f); i++; f = "";
        while (i < s.size()) f += s[i++];
        zRange.second = stoi(f); i++; f = "";
    }

    uint64_t volume() { return abs(xRange.second - xRange.first) * abs(yRange.second - yRange.first) * abs(zRange.second - zRange.first); }
    string to_string() { stringstream s; s << xRange.first << ',' << xRange.second << ',' << yRange.first << ',' << yRange.second << ',' << zRange.first << ',' << zRange.second; return s.str(); }

    bool intersects(Cuboid c) {
        return xRange.first < c.xRange.second
            && xRange.second > c.xRange.first
            && yRange.first < c.yRange.second
            && yRange.second > c.yRange.first
            && zRange.first < c.zRange.second
            && zRange.second > c.zRange.first;
    }

    Cuboid intersection(Cuboid c) {
        p x = p( max(xRange.first, c.xRange.first), min(xRange.second, c.xRange.second));
        p y = p( max(yRange.first, c.yRange.first), min(yRange.second, c.yRange.second));
        p z = p( max(zRange.first, c.zRange.first), min(zRange.second, c.zRange.second));
        return Cuboid(x,y,z);
    }

    vector<Cuboid> split(Cuboid c) {
        vector<Cuboid> newCubes;

        vector<int> newX = getIntersectPoints(xRange, c.xRange);
        vector<int> newY = getIntersectPoints(yRange, c.yRange);
        vector<int> newZ = getIntersectPoints(zRange, c.zRange);

        newX.erase(unique(newX.begin(), newX.end()), newX.end());
        newY.erase(unique(newY.begin(), newY.end()), newY.end());
        newZ.erase(unique(newZ.begin(), newZ.end()), newZ.end());

        vector<p> newXp, newYp, newZp;
        newXp.push_back(p(newX[0], newX[1]));
        for (int i = 1; i < newX.size()-1; i++)
            newXp.push_back(p(newX[i]+1,newX[i+1]));

        newYp.push_back(p(newY[0], newY[1]));
        for (int i = 1; i < newY.size()-1; i++)
            newYp.push_back(p(newY[i]+1,newY[i+1]));

        newZp.push_back(p(newZ[0], newZ[1]));
        for (int i = 1; i < newZ.size()-1; i++)
            newZp.push_back(p(newZ[i]+1,newZ[i+1]));

        for (auto x: newXp)
        for (auto y: newYp)
        for (auto z: newZp)
            newCubes.push_back(Cuboid(x, y, z));

        return newCubes;
    }

    vector<string> subDivs() {
        int xStart = findIndex(xs, xRange.first);
        int yStart = findIndex(ys, yRange.first);
        int zStart = findIndex(zs, zRange.first);

        vector<string> hashes;

        for (int x = xStart; xs[x] != xRange.second; x++)
        for (int y = yStart; ys[y] != yRange.second; y++)
        for (int z = zStart; zs[z] != zRange.second; z++) {
            stringstream s;
            s << xs[x] << ',' << xs[x+1] << ',' << ys[y] << ',' << ys[y+1] << ',' << zs[z] << ',' << zs[z+1];
            hashes.push_back(s.str());
        }
        int a = hashes.size();
        return hashes;
    }
};
struct step {
    bool on;
    Cuboid cuboid;
};

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
        s.cuboid.xRange.first = stoi(foo);
        i+= 2; foo = "";
        while (line[i] != ',') foo += line[i++];
        s.cuboid.xRange.second = stoi(foo)+1;
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.cuboid.yRange.first = stoi(foo);
        i+= 2; foo = "";
        while (line[i] != ',') foo += line[i++];
        s.cuboid.yRange.second = stoi(foo)+1;
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.cuboid.zRange.first = stoi(foo);
        i+= 2; foo = "";
        while (i <= line.size()) foo += line[i++];
        s.cuboid.zRange.second = stoi(foo)+1;

        xs.push_back(s.cuboid.xRange.first); xs.push_back(s.cuboid.xRange.second+1);
        ys.push_back(s.cuboid.yRange.first); ys.push_back(s.cuboid.yRange.second+1);
        zs.push_back(s.cuboid.zRange.first); zs.push_back(s.cuboid.zRange.second+1);

        steps.push_back(s);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    sort(zs.begin(), zs.end());

    printf("==========================================================================\n");
    printf("================== Beginning procedure with [%2d] cubes ===================\n", steps.size());
    printf("==========================================================================\n");

    vector<vector<vector<bool>>> core;
    core.resize(xs.size(), vector<vector<bool>>(ys.size(), vector<bool>(zs.size())));

    int i = 0;
    // Mark sub-cubes on or off based on lighting
    for (auto s: steps) {
        int xBegin = lower_bound(xs.begin(), xs.end(), s.cuboid.xRange.first) - xs.begin();
        int xEnd =   lower_bound(xs.begin(), xs.end(), s.cuboid.xRange.second+1) - xs.begin();
        int yBegin = lower_bound(ys.begin(), ys.end(), s.cuboid.yRange.first) - ys.begin();
        int yEnd =   lower_bound(ys.begin(), ys.end(), s.cuboid.yRange.second+1) - ys.begin();
        int zBegin = lower_bound(zs.begin(), zs.end(), s.cuboid.zRange.first) - zs.begin();
        int zEnd =   lower_bound(zs.begin(), zs.end(), s.cuboid.zRange.second+1) - zs.begin();

        for (int x = xBegin; x < xEnd; x++)
        for (int y = yBegin; y < yEnd; y++)
        for (int z = zBegin; z < zEnd; z++)
            core[x][y][z] = s.on;
    }

    uint64_t totalCount = 0;
    for (int x = 0; x < xs.size()-1; x++)
    for (int y = 0; y < ys.size()-1; y++)
    for (int z = 0; z < zs.size()-1; z++)
        if (core[x][y][z])
            totalCount += (int64_t)(abs(xs[x+1] - xs[x]) * abs(ys[y+1] - ys[y]) * abs(zs[z+1] - zs[z]));  

    printf("================= TOTAL COUNT: [%18.1" PRIu64 "] cubes ================\n", totalCount);
    printf("==========================================================================\n\n");
}
