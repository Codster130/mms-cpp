#include <iostream>
#include <string>
#include <stack>
#include "API.h"

using namespace std;
using std::string;

//easy output to console
void log(const string& text) {
    std::cerr << text << std::endl;
}

//initialize robot to be facing forward, starting at (0,15) as the array is flipped vertically
int currentX = 0;
int currentY = 15;
char currentDirection = 'n';
int map[16][16]{
        {14, 13, 12, 11, 10, 9, 8 ,7 ,7 ,8, 9, 10, 11, 12, 13, 14},
        {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
        {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
        {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
        {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
        {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
        {8, 7, 6, 5, 4, 3, 2, 1 ,1, 2 ,3, 4, 5 ,6, 7, 8},
        {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6 ,7},
        {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6 ,7},
        {8, 7, 6, 5, 4, 3, 2, 1 ,1, 2 ,3, 4, 5 ,6, 7, 8},
        {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
        {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
        {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
        {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
        {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
        {14, 13, 12, 11, 10, 9, 8 ,7 ,7 ,8, 9, 10, 11, 12, 13, 14},
};



int main(int argc, char* argv[]) {
    log("Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    return 0;
}
