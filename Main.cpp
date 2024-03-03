#include <iostream>
#include <string>
#include <random>
#include <stack>
#include "API.h"

using namespace std;
using std::string;

struct nonDirections{
    int left;
    int right;
    int back;
};

//initialize robot to be facing forward
int currentX = 0;
int currentY = 0;
char currentDirection = 'n';
int map[16][16]{
        {14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14},
        {13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13},
        {12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12},
        {11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11},
        {10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10},
        { 9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9},
        { 8,  7,  6,  5,  4,  3,  2,  1,  1,  2,  3,  4,  5,  6,  7,  8},
        { 7,  6,  5,  4,  3,  2,  1,  0,  0,  1,  2,  3,  4,  5,  6,  7},
        { 7,  6,  5,  4,  3,  2,  1,  0,  0,  1,  2,  3,  4,  5,  6,  7},
        { 8,  7,  6,  5,  4,  3,  2,  1,  1,  2,  3,  4,  5,  6,  7,  8},
        { 9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9},
        {10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10},
        {11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11},
        {12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12},
        {13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13},
        {14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14},
};
std::stack<int> xStack;

double rand3(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0,3.0);
    double tmp = dist(gen);
    return tmp;
}

//easy output to console
void log(const string& text) {
    std::cerr << text << std::endl;
}

//allow the user to tell current direction and turning direction and return the new direction
void setDirection(char Direction, int turningDirection){
    if (turningDirection == 'R' || turningDirection == 'L'){
        if (Direction == 'n'){
            if (turningDirection == 'L') {
                API::turnLeft();
                currentDirection = 'w';
                return;
            } else {
                API::turnRight();
                currentDirection = 'e';
                return;
            }
        }
        if (Direction == 'e'){
            if (turningDirection == 'L') {
                API::turnLeft();
                currentDirection = 'n';
                return;
            } else {
                API::turnRight();
                currentDirection = 's';
                return;
            }
        }
        if (Direction == 's'){
            if (turningDirection == 'L') {
                API::turnLeft();
                currentDirection = 'e';
                return;
            } else {
                API::turnRight();
                currentDirection = 'w';
                return;
            }
        }
        if (Direction == 'w'){
            if (turningDirection == 'L') {
                API::turnLeft();
                currentDirection = 's';
                return;
            } else {
                API::turnRight();
                currentDirection = 'n';
                return;
            }
        }
    } else {
        throw std::invalid_argument("Invalid turning direction");
    }
}

char directionLeft(char Direction){
    switch (Direction) {
        case 'n':
            return 'w';
        case 'e':
            return 'n';
        case 's':
            return 'e';
        case 'w':
            return 's';
        default:
            throw std::invalid_argument("Invalid direction");
    }
}

char directionRight(char Direction){
    switch (Direction) {
        case 'n':
            return 'e';
        case 'e':
            return 's';
        case 's':
            return 'w';
        case 'w':
            return 'n';
        default:
            throw std::invalid_argument("Invalid direction");
    }
}

void updateWallMap(int x, int y, char direction){
    if(API::wallFront()){
        API::setWall(x,y,direction);
    }
    if (API::wallLeft()){
        API::setWall(x, y, directionLeft(direction));
    }
    if (API::wallRight()){
        API::setWall(x, y, directionRight(direction));
    }
}

void updateCoordinates(){
    //update currentX and currentY here
    if (currentDirection == 'n'){
        currentY++;
    } else if (currentDirection == 'e'){
        currentX++;
    } else if (currentDirection == 's'){
        currentY--;
    } else {
        currentX--;
    }
}

void updateGrid(){
    for (int i = 0; i < 16; i++){
        for (int v = 0; v < 16; v++){
            API::setText(i, v, to_string(map[i][v]));
        }
    }
}

nonDirections nonFrontDirection(){
    nonDirections tmp;
    if (currentDirection == 'n'){
        tmp.left = map[currentX--][currentY];
        tmp.right = map[currentX++][currentY];
        tmp.back = map[currentX][currentY--];
    } else if (currentDirection == 'e'){
        tmp.left = map[currentX][currentY++];
        tmp.right = map[currentX][currentY--];
        tmp.back = map[currentX--][currentY];
    } else if (currentDirection == 's'){
        tmp.left = map[currentX++][currentY];
        tmp.right = map[currentX--][currentY];
        tmp.back = map[currentX][currentY++];
    } else {
        tmp.left = map[currentX][currentY--];
        tmp.right = map[currentX][currentY++];
        tmp.back = map[currentX++][currentY];
    }
    return tmp;
}

void updateStack(){
    xStack.push(map[currentX][currentY]);
    xStack.push(nonFrontDirection().left);
    xStack.push(nonFrontDirection().right);
    xStack.push(nonFrontDirection().back);
}

void mapMove() {
    double tmp = rand3();
    if (API::wallLeft() && API::wallRight() && API::wallFront()){
        setDirection(currentDirection, 'L');
        setDirection(currentDirection, 'L');
    } else if (!API::wallFront() && !API::wallRight() && !API::wallLeft()){
        if (tmp > 2){
            setDirection(currentDirection,'R');
        } else if (tmp > 1){
            setDirection(currentDirection, 'L');
        }
    } else if (!API::wallFront() && !API::wallRight()){
        if (tmp > 1.5){
            setDirection(currentDirection, 'R');
        }
    } else if (!API::wallFront() && !API::wallLeft()) {
        if (tmp > 1.5) {
            setDirection(currentDirection, 'L');
        }
    } else if (!API::wallRight() && !API::wallLeft()) {
        if (tmp > 1.5) {
            setDirection(currentDirection, 'L');
        } else {
            setDirection(currentDirection, 'R');
        }
    } else if (!API::wallRight()){
        setDirection(currentDirection, 'R');
    } else if (!API::wallLeft()){
        setDirection(currentDirection, 'L');
    }
    API::moveForward();
    updateCoordinates();
}

void resetStack(){
    //reset the stack to starting value
    while (!xStack.empty()){
        xStack.pop();
    }
}

void updateMap(){
    //update map with the theoretical shortest number of moves to the center
}

int main(int argc, char* argv[]) {
    log("Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    while(!(currentX == 7 && currentY == 7 || currentX == 7 && currentY == 8 || currentX == 8 && currentY == 7 || currentX == 8 && currentY == 8)){
        log("Update Wall Map Loop");
        updateWallMap(currentX, currentY, currentDirection);
        updateStack();
        mapMove();
        updateGrid();
        log("Current X: " + std::to_string(currentX) + " Current Y: " + std::to_string(currentY));
        if (API::wasReset()){
            currentDirection = 'n';
            currentX = 0;
            currentY = 0;
            resetStack();
            API::ackReset();
        }
    }
    return 0;
}