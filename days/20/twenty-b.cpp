#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define ITERATIONS 50

void printImage(vector<string> image) { for (auto l: image) cout << l << endl; }
void rebuffer(vector<string> &image, char c) {
    for (int i = 0; i < image.size(); i++) {
        image[i].insert(image[i].begin(), c);
        image[i].insert(image[i].end(), c);
    }

    string top, bottom;
    top.insert(0, image[0].size(), c);
    bottom.insert(0, image[0].size(), c);

    image.insert(image.begin(), top);
    image.insert(image.end(), bottom);
}
int getIndex(vector<string> image, int x, int y) {
    int index = 0;
    for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++) 
        index = (index <<= 1) + (image[x+i][y+j] == '.' ? 0 : 1);

    return index;
}
int countLit(vector<string> image) {
    if (image[0][0] == '#') return -1; // This means 'infinite'
    int count = 0;
    for (auto l: image)
    for (auto c: l)
        if (c == '#')
            count++;
    return count;
}


int main(int argc, char *argv[])
{
    if (argc < 2) { cout << "No arguments!\n"; return -1; }

    ifstream input; string ref, line;
    input.open(argv[1]);

    // Get the algorithm
    input >> ref;

    // Construct the base image
    vector<string> image;
    for (int i = 0; i < 2; i++) 
    while (!input.eof()) {
        input >> line;
        image.push_back(line);
    }

    for (int i = 0; i < 5; i++) rebuffer(image, '.');

    printf("Starting Image:\n"); printImage(image); printf("\n");

    for (int iter = 0; iter < ITERATIONS; iter++) {
        vector<string> newImage;
        for (int x = 0; x < image.size(); x++) {
            string line;
            for (int y = 0; y < image[0].size(); y++) {                
                if (x == 0 || y == 0 || x == image.size()-1 || y == image[0].size()-1)
                    line += image[0][0] == '.' ? ref[0] : ref[511]; // literal edge case
                else
                    line += ref[getIndex(image, x, y)];
            }
            newImage.push_back(line);
        }
        rebuffer(newImage, newImage[2][2]);
        image = newImage;

        printf("Finished iteration %d\n", iter+1);
    }

    printf("[%4.1d] Enhanced\n", countLit(image)); printImage(image); printf("\n");
}