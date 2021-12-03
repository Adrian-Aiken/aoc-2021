#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // Start result at -3 to counter first three readings; these don't count
    int reading, baseSum = 0, i = 0, result = -3;
    int buckets[3] = { 0, 0, 0 };    
    ifstream inputFile;

    inputFile.open("input");

    while (inputFile >> reading)
    {
        // Fill the buckets
        buckets[0] += reading; buckets[1] += reading; buckets[2] += reading;

        if (buckets[i] > baseSum) result++;

        // Empty bucket, set up for next loop
        baseSum = buckets[i];
        buckets[i] = 0;
        i = ++i % 3;
    }
    
    cout << "Number of increases: " << result;
}