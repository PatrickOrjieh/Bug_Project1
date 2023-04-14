//
// Created by orjie on 14/04/2023.
//

#include "Bishop.h"
#include <iostream>

Bishop::Bishop() {
    bisLength = 0;
}

//make up different constructors with all the parameters set the hop length to a random number between 2 and 4
Bishop::Bishop(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int bisLength) : Bug(id, position, direction, size, alive) {
    this->bisLength = bisLength;
}

//getter amd setter for bisLength
int Bishop::getBisLength() const {
    return bisLength;
}

void Bishop::setBisLength(int b) {
    Bishop::bisLength = b;
}

//int bisLength; The distance/length that a particular bishop bug can bis (in
//range (1-6 units)
//void move(){} A Bishop bug moves according to these rules:
//- moves by “bisLength” units in current direction
//- if at edge of board and can’t move over edge in
//current direction, set a new direction at random
//(repeat until bug can move forward) and then
//move.
//- if bug can’t bis the full ‘bisLength’, then the bug
//does move but ‘hits’ the edge and falls on the
//square where it hit the edge/wall
//- record new position in bishops path history
//note that the bishop can only move diagonally
void Bishop::move(){
    //if the bug is at the edge of the board and can't move in the current direction, set a new direction at random
    while (isWayBlocked()) {
        int newDirection = rand() % 4 + 5;
        setDirection((Direction) newDirection);
    }

    // get the current position, direction and path of the bug
    std::pair<int, int> currentPosition = getPosition();
    Direction currentDirection = getDirection();
    std::list<std::pair<int, int>> currentPath = getPath();

    // calculate the maximum distance the bug can hop in the current direction
    //note that the bishop can only move diagonally
    int maxHopDistance = 0;
    switch (currentDirection) {
        case NorthEast:
            maxHopDistance = std::min(currentPosition.second, 9 - currentPosition.first);
            break;
        case SouthEast:
            maxHopDistance = std::min(9 - currentPosition.second, 9 - currentPosition.first);
            break;
        case SouthWest:
            maxHopDistance = std::min(9 - currentPosition.second, currentPosition.first);
            break;
        case NorthWest:
            maxHopDistance = std::min(currentPosition.second, currentPosition.first);
            break;
    }

    // if the bug can hop the full distance, move it and update its position
    if (maxHopDistance >= bisLength) {
        switch (currentDirection) {
            case NorthEast:
                currentPosition.first += bisLength;
                currentPosition.second -= bisLength;
                break;
            case SouthEast:
                currentPosition.first += bisLength;
                currentPosition.second += bisLength;
                break;
            case SouthWest:
                currentPosition.first -= bisLength;
                currentPosition.second += bisLength;
                break;
            case NorthWest:
                currentPosition.first -= bisLength;
                currentPosition.second -= bisLength;
                break;
        }
        setPosition(currentPosition);
        currentPath.push_back(currentPosition);
        setPath(currentPath);
    } else {
        // if the bug can't hop the full distance, move it to the edge and update its position
        switch (currentDirection) {
            case NorthEast:
                currentPosition.first += maxHopDistance;
                currentPosition.second -= maxHopDistance;
                break;
            case SouthEast:
                currentPosition.first += maxHopDistance;
                currentPosition.second += maxHopDistance;
                break;
            case SouthWest:
                currentPosition.first -= maxHopDistance;
                currentPosition.second += maxHopDistance;
                break;
            case NorthWest:
                currentPosition.first -= maxHopDistance;
                currentPosition.second -= maxHopDistance;
                break;
        }
        setPosition(currentPosition);
        currentPath.push_back(currentPosition);
        setPath(currentPath);
    }
}

//display the bug's information
//102 Bishop (5,8) 13 NorthEast 4 Alive
void Bishop::displayBug() {
    std::cout << getId() << " Bishop (" << getPosition().first << "," << getPosition().second << ") " << getSize() << " ";
    switch (getDirection()) {
        case NorthEast:
            std::cout << "NorthEast ";
            break;
        case SouthEast:
            std::cout << "SouthEast ";
            break;
        case SouthWest:
            std::cout << "SouthWest ";
            break;
        case NorthWest:
            std::cout << "NorthWest ";
            break;
    }
    std::cout << bisLength << " ";
    if (isAlive()) {
        std::cout << "Alive" << std::endl;
    } else {
        std::cout << "Dead" << std::endl;
    }
}

Bishop::~Bishop() {

}


