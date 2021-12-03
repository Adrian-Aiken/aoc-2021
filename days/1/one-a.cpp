#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inputFile;
    inputFile.open("input");

    int baseNum, reading, result = 0;

    // First measurement is baseline - ignored for the first 'reading'
    inputFile >> baseNum;

    while (inputFile >> reading)
    {
        if (reading > baseNum) result++;
        baseNum = reading;
    }
    
    cout << "Number of increases: " << result;
}