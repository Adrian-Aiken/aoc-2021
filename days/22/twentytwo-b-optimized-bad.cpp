#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <inttypes.h>

#define p pair<int64_t,int64_t>
#define LENGTH 50
#define SIZE (LENGTH * 2) + 1

using namespace std;

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

    int64_t volume() { return abs(xRange.second - xRange.first) * abs(yRange.second - yRange.first) * abs(zRange.second - zRange.first); }

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
        s.cuboid.xRange.second = stoi(foo);
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.cuboid.yRange.first = stoi(foo);
        i+= 2; foo = "";
        while (line[i] != ',') foo += line[i++];
        s.cuboid.yRange.second = stoi(foo);
        i += 3; foo = "";
        while (line[i] != '.') foo += line[i++];
        s.cuboid.zRange.first = stoi(foo);
        i+= 2; foo = "";
        while (i <= line.size()) foo += line[i++];
        s.cuboid.zRange.second = stoi(foo);

        steps.push_back(s);
    }

    printf("==========================================================================\n");
    printf("================== Beginning procedure with [%2d] cubes ===================\n", steps.size());
    printf("==========================================================================\n\n");

    
    uint64_t totalCount = 0;
    for (int i = 0; i < steps.size(); i++) {
        if (!steps[i].on) { printf("[%2d] OFF cube; skipping\n"); continue; }

        Cuboid c = steps[i].cuboid;

        vector<Cuboid> stillIn;
        stillIn.push_back(c);
        int64_t initCount = c.volume();

        for (int j = i+1; j < steps.size(); j++) {
            Cuboid n = steps[j].cuboid;

            // Sanity check; ignore if there's no intersection with the original cube
            if (!c.intersects(n)) continue; 

            vector<Cuboid> nextIn;
            for (auto next: stillIn) {
                vector<Cuboid> split = next.split(n);
                for (auto g: split)
                    if (!g.intersects(n)) 
                        nextIn.push_back(g);
            }
            stillIn = nextIn;

            int mistakes = 0;
            // Extra sanity check, to see if there's double counting
            for (int a =   0; a < stillIn.size(); a++)
            for (int b = a+1; b < stillIn.size(); b++)
                if (stillIn[a].intersects(stillIn[b]))
                    mistakes++;
            
            int64_t count = 0;
            for (auto a: stillIn) {
                int64_t vol = a.volume();
                count += vol;
            }

            int a = 4;
        }

        int64_t count = 0;
        for (auto a: stillIn) count += a.volume();

        printf("[%2d] ON Cube | Initial volume [%16.1" PRIu64 "] | Final Contribution: [%16.1" PRIu64 "]\n", i, c.volume(), count);

        /*
        // Find and account for intersecting cubes
        vector<Cuboid> intersections;
        for (int j = i+1; j < steps.size(); j++) {
            Cuboid n = steps[j].cuboid;
            if (!c.intersects(n)) continue;
            Cuboid intersection = c.intersection(n);
            count -= intersection.volume();
            intersections.push_back(intersection);
        }

        // Undo double-counting by checking intersections of intersections
        for (int j =   0; j < intersections.size(); j++)
        for (int k = j+1; k < intersections.size(); k++) {
            if (!intersections[j].intersects(intersections[k])) continue;
            Cuboid doubleIntersect = intersections[j].intersection(intersections[k]);
            count += doubleIntersect.volume();
        }

        printf("[%2d] ON Cube | [%2.1d] Intersections | Initial volue [%16.1" PRIu64 "] | Final Contribution: [%16.1" PRIu64 "]\n", i, intersections.size(), c.volume(), count);

        if (count < 0) printf("WE HAVE A MAJOR ISSUE, SHOULD NOT BE NEGATIVE");
        if (count > c.volume()) printf("OVERCORRECTED, OHGOD OVERCORRECRTED\n");
        totalCount += count;*/
    }

    printf("\n==========================================================================\n");
    printf("================ TOTAL COUNT: [%18.1" PRIu64 "] cubes =================\n", totalCount);
    printf("==========================================================================\n\n");
}
