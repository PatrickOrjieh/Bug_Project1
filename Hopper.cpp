//
// Created by orjie on 27/03/2023.
//

#include "Hopper.h"

Hopper::Hopper() {
    hopLength = 0;
}

//make up different constructors with all the parameters set the hop length to a random number between 2 and 4
Hopper::Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int hopLength) : Bug(id, position, direction, size, alive) {
    this->hopLength = hopLength;
}

//getter amd setter for hopLength
int Hopper::getHopLength() const {
    return hopLength;
}

void Hopper::setHopLength(int h) {
    Hopper::hopLength = h;
}

//int hopLength; The distance/length that a particular hopper bug can hop (in
//range (2-4 units)
//void move(){} A Hopper bug moves according to these rules:
//- moves by “hopLength” units in current direction
//- if at edge of board and can’t move over edge in
//current direction, set a new direction at random
//(repeat until bug can move forward) and then
//move.
//- if bug can’t hop the full ‘hopLength’, then the bug
//does move but ‘hits’ the edge and falls on the
//square where it hit the edge/wall
//- record new position in hoppers path history
void Hopper::move() {
    // if the bug is at the edge of the board and can't move in the current direction, set a new direction at random
    while (isWayBlocked()) {
        int newDirection = rand() % 4 + 1;
        setDirection((Direction) newDirection);
    }
    // get the current position, direction and path of the bug
    std::pair<int, int> currentPosition = getPosition();
    Direction currentDirection = getDirection();
    std::list<std::pair<int, int>> currentPath = getPath();

    // calculate the maximum distance the bug can hop in the current direction
    int maxHopDistance = 0;
    switch (currentDirection) {
        case North:
            maxHopDistance = currentPosition.second;
            break;
        case East:
            maxHopDistance = 9 - currentPosition.first;
            break;
        case South:
            maxHopDistance = 9 - currentPosition.second;
            break;
        case West:
            maxHopDistance = currentPosition.first;
            break;
    }

    // if the bug can hop the full distance, move it and update its position
    if (maxHopDistance >= hopLength) {
        switch (currentDirection) {
            case North:
                currentPosition.second -= hopLength;
                break;
            case East:
                currentPosition.first += hopLength;
                break;
            case South:
                currentPosition.second += hopLength;
                break;
            case West:
                currentPosition.first -= hopLength;
                break;
        }
        setPosition(currentPosition);
        currentPath.push_back(currentPosition);
        setPath(currentPath);
    }
        // if the bug can't hop the full distance, it hits the edge and falls on that square
    else {
        switch (currentDirection) {
            case North:
                currentPosition.second = 0;
                break;
            case East:
                currentPosition.first = 9;
                break;
            case South:
                currentPosition.second = 9;
                break;
            case West:
                currentPosition.first = 0;
                break;
        }
        setPosition(currentPosition);
        currentPath.push_back(currentPosition);
        setPath(currentPath);
    }
}

Hopper::~Hopper() {

}


