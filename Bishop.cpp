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
    //will implement later
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


