#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<char, string> conversion = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
};

int takeBits(string &message, int length) {
    int val = 0;
    for (int i = 0; i < length; i++) {
        val <<= 1;
        val += message[i] - '0';
    }

    message = message.substr(length);
    return val;
}

int takeLiteral(string &message) {
    int val = 0, next;
    do {
         next = takeBits(message, 5);
         val <<= 4;
         val += next & 0x0F;
    } while (next & 0x10);
    return val;
}

int parsePacket(string &message) {
    int version = takeBits(message, 3);
    int type = takeBits(message, 3);

    int totalSum = version;

    switch (type) {
        case 4: {
            int literal = takeLiteral(message);
            printf("Literal: %d\n", literal);
            break;
        }

        default:
            int lengthId = takeBits(message, 1);
            int packetLength;
            switch(lengthId) {
                case 0: {
                    int packetLength = takeBits(message, 15);
                    string packets = message.substr(0, packetLength);
                    message = message.substr(packetLength);

                    while (!packets.empty())
                        totalSum += parsePacket(packets);

                    break;
                }
                case 1: {
                    int subPackets = takeBits(message, 11);
                    for (int i = 0; i < subPackets; i++)
                        totalSum += parsePacket(message);
                    break;
                }
            }

            break;
    }

    return totalSum;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line, message;
    input.open(argv[1]);

    input >> line;
    for (auto c: line) 
        message += conversion[c];

    int sum = parsePacket(message);

    printf("Version Sum: %d\n", sum);
}