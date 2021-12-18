#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum NumState { None, Explode, ExplodeLeft, ExplodeRight, Split, NotDone };
enum Dir { Left, Right };
class SFNum;
class SFNum {
    public:
        int num = -1;
        int passup = -1;
        pair<SFNum, SFNum> *child;

        SFNum(){};
        SFNum(int i){ num = i; };
        SFNum(SFNum a, SFNum b) { num = -1; child = new pair(a, b); }

        SFNum(string s) {
            if (s.length() == 1) {
                num = stoi(s);
                return;
            }
            int nested = 0, splitIndex = -1;

            for (int i = 0; i < s.length(); i++) {
                if (splitIndex >= 0) break;
                switch(s[i]) {
                    case '[': nested++; break;
                    case ']': nested--; break;

                    case ',':
                        if (nested == 1) {
                            splitIndex = i;
                        }
                        break;                        
                }
            }

            string left = s.substr(1, splitIndex-1);
            string right = s.substr(splitIndex+1, string::npos);
            right.pop_back();

            child = new pair(SFNum(left), SFNum(right));
        };

        string ToString() {
            if (num >= 0) return std::to_string(num);
            return "[" + child->first.ToString() + "," + child->second.ToString() + "]";
        }

        NumState reduce(int level = 0) {
            passup = -1;
            
            if (num >= 0) return NumState::None;
            if (level >= 4) return NumState::Explode;

            NumState leftState = child->first.reduce(level+1);
            switch(leftState) {
                case NumState::Explode:
                    passup = child->first.child->first.num;
                    child->second.explode(child->first.child->second.num, Dir::Left);
                    child->first = SFNum(0);
                    return NumState::ExplodeLeft;
                
                case NumState::None:
                    break;

                case NumState::ExplodeLeft:
                    passup = child->first.passup;
                    child->second.passup = -1;
                    return NumState::ExplodeLeft;

                case NumState::ExplodeRight:
                    child->second.explode(child->first.passup, Dir::Left);
                    return NumState::NotDone;

                default:
                    return NumState::NotDone;
            }

            NumState rightState = child->second.reduce(level+1);
            switch(rightState) {
                case NumState::Explode:
                    passup = child->second.child->second.num;
                    child->first.explode(child->second.child->first.num, Dir::Right);
                    child->second = SFNum(0);
                    return NumState::ExplodeRight;
                
                case NumState::None:
                    break;

                case NumState::ExplodeLeft:
                    child->first.explode(child->second.passup, Dir::Right);
                    return NumState::NotDone;

                case NumState::ExplodeRight:
                    passup = child->second.passup;
                    child->first.passup = -1;
                    return NumState::ExplodeRight;
                    
                default:
                    return NumState::NotDone;
            }            

            return NumState::None;
        };

        void explode(int n, Dir d) {
            if (num >= 0) {
                num += n;
            } else if (d == Dir::Right) {
                child->second.explode(n, d);
            } else if (d == Dir::Left) {
                child->first.explode(n, d);
            }
        };

        NumState split() {
            if (num >= 0) {
                if (num > 9) {
                    int carry = num % 2;
                    int half = num / 2;
                    num = -1;
                    child = new pair(SFNum(half), SFNum(half+carry));
                    return NumState::Split;
                }
                return NumState::None;
            }

            NumState leftState = child->first.split();

            if (leftState != NumState::None) return leftState;

            return child->second.split();
        };

        int magnitude() {
            if (num >= 0) return num;
            return ( (3 * child->first.magnitude()) + (2 * child->second.magnitude()) );
        }
};
 
int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line;
    input.open(argv[1]);
    
    vector<string> lines;
    while (!input.eof()) {
        input >> line;
        if (line == "") break;
        lines.push_back(line);
    }

    int maxMagnitude = -1;
    for (int i = 0; i < lines.size(); i++)
    for (int j = 0; j < lines.size(); j++) {
        if (i == j) continue;

        SFNum num = SFNum(SFNum(lines[i]), SFNum(lines[j]));

        NumState state = NumState::NotDone;
        while (state != NumState::None) { 
            state = num.reduce();
            if (state == NumState::None)
                state = num.split();
        }

        maxMagnitude = max(maxMagnitude, num.magnitude());
    }

    printf("Max Magnitude:\t%d", maxMagnitude);
}