#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

const string open =     "([{<";
const string closed =   ")]}>";
const int points[4] =   {1, 2, 3, 4};

int main(int argc, char *argv[])
{
    if (argc < 2) { std::cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);

    vector<unsigned long long> scores;
    int invalidCount = 0;
    int validCount = 0;

    while (!input.eof()) {
        input >> line;
        stack<char> chunks;

        for (auto c: line) {
            if (open.find(c) != string::npos) {
                chunks.push(c);
            } else {
                // Chunk Valid
                if (open.find(chunks.top()) == closed.find(c)) {
                    chunks.pop();
                }
                // Chunk Invalid
                else {
                    while (!chunks.empty()) chunks.pop();
                    break;
                }
            }
        }

        unsigned long long lineScore = 0;
        while (!chunks.empty()) { 
            int i = open.find(chunks.top());
            chunks.pop();
 
            lineScore *= 5;
            lineScore += points[i];
        }

        if (lineScore > 0) scores.push_back(lineScore);
    }

    std::sort(scores.begin(), scores.end());

    std::cout << "Scores:\n";
    for (auto s: scores) std::cout << "\t" << s << endl;

    unsigned long long middle = scores[(scores.size()/2)];
    std::cout << "\nMiddle: " << middle << endl;
}