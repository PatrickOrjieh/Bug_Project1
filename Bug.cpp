//
// Created by orjie on 20/03/2023.
//

#include "Bug.h"
#include <iostream>

//default constructor
Bug::Bug(){
    this->id = 0;
    this->position = std::make_pair(0,0);
    this->direction = 0;
    this->size = 0;
    this->alive = false;
}

//constructor
Bug::Bug(int id, std::pair<int, int> position, int direction, int size, bool alive) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = alive;
}

//getters and setters
//Identification number (id) for a bug (1,2,3,4,…)
int Bug::getId() const {
    return id;
}

void Bug::setId(int d) {
    Bug::id = d;
}

//Co-ordinate pair (x,y) represented in a ‘pair’ struct from
//<utility> standard library. (0,0) is top left cell on board.
const std::pair<int, int> &Bug::getPosition() const {
    return position;
}

void Bug::setPosition(const std::pair<int, int> &p) {
    Bug::position = p;
}

//direction in which the bug is facing :
//1=North, 2=East, 3=South, 4=West (or use enum)
//make sure the direction is between 1 and 4 using enum
int Bug::getDirection() const {
    return direction;
}

void Bug::setDirection(int d) {
    Bug::direction = d;
}

//Size of the bug (initially 1-20); biggest bug wins in a fight
//and others on same cell are eaten. Winner grows during a
//fight by the sum of the sizes of other bugs eaten.
int Bug::getSize() const {
    return size;
}

void Bug::setSize(int s) {
    Bug::size = s;
}

//Flag indicating life status of a bug. All bugs set to ‘true’
//initially. When eaten, this flag is set to ‘false’.
//true => alive, false => dead
bool Bug::isAlive() const {
    return alive;
}

void Bug::setAlive(bool a) {
    Bug::alive = a;
}

//Path taken by a bug. (i.e. the List of positions (on grid) that a
//bug visited.)
//    const std::list<std::pair<int, int>> &getPath() const;
const std::list<std::pair<int, int>> & Bug::getPath() const {
    return path;
}

void Bug::setPath(const std::list<std::pair<int, int>> &p) {
    Bug::path = p;
}

//Checks if a bug is against an edge of the board AND if it is
//facing in the direction of that edge. If so, its way is blocked.
//[Used by the move() function], board is siz2 10x10
//    bool isWayBlocked();
bool Bug::isWayBlocked() {
    //if the bug is facing north and is at the top of the board
    if (this->direction == 1 && this->position.second == 0) {
        return true;
    }
    //if the bug is facing east and is at the right of the board
    if (this->direction == 2 && this->position.first == 9) {
        return true;
    }
    //if the bug is facing south and is at the bottom of the board
    if (this->direction == 3 && this->position.second == 9) {
        return true;
    }
    //if the bug is facing west and is at the left of the board
    if (this->direction == 4 && this->position.first == 0) {
        return true;
    }
    return false;
}

//All derived classes must implement logic to move a bug
//from its current position to a new position based on
//movement rules for the particular bug type. No
//implementation is require in the Bug base class, so move()
//can be made a pure virtual function in the Bug class.
//virtual void move() = 0;

Bug::~Bug() {
    std::cout << "Bug destructor called" << std::endl;
}