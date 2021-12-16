#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, string> conversion = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
};

uint64_t takeBits(string &message, uint64_t length) {
    uint64_t val = 0;
    for (uint64_t i = 0; i < length; i++) {
        val <<= 1;
        val += message[i] - '0';
    }

    message = message.substr(length);
    return val;
}

uint64_t takeLiteral(string &message) {
    uint64_t val = 0, next;
    do {
         next = takeBits(message, 5);
         val <<= 4;
         val += next & 0x0F;
    } while (next & 0x10);
    printf("Literal: %u\n", val);
    return val;
}

uint64_t parsePacket(string &message) {
    uint64_t version = takeBits(message, 3);
    uint64_t type = takeBits(message, 3);

    if (type == 4) return takeLiteral(message);

    printf("Type: %u\n", type);

    uint64_t lengthId = takeBits(message, 1);
    vector<uint64_t> values;
    switch(lengthId) {
        case 0: {
            uint64_t packetLength = takeBits(message, 15);
            string packets = message.substr(0, packetLength);
            message = message.substr(packetLength);

            while (!packets.empty())
                values.push_back(parsePacket(packets));
            break;
        }
        case 1: {
            uint64_t subPackets = takeBits(message, 11);
            for (uint64_t i = 0; i < subPackets; i++)
                values.push_back(parsePacket(message));
            break;
        }
    }

    uint64_t ret = 0;
    switch (type) {
        case 0: // Sum
            for (auto n: values) ret += n;
            return ret;

        case 1: // Product
            ret = 1;
            for (auto n: values) ret *= n;
            return ret;
        
        case 2: // Minimum
            ret = ULLONG_MAX;
            for (auto n: values) ret = min(ret, n);
            return ret;

        case 3: // Maximum
            ret = 0;
            for (auto n: values) ret = max(ret, n);
            return ret;

        case 5: // Greater Than
            return values[0] > values[1] ? 1 : 0;
            
        case 6: // Less Than
            return values[0] < values[1] ? 1 : 0;

        case 7: // Equal To
            return values[0] == values[1] ? 1 : 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string line, message;
    input.open(argv[1]);

    input >> line;
    for (auto c: line) 
        message += conversion[c];

    uint64_t sum = parsePacket(message);

    cout << "Message: " << sum;
}