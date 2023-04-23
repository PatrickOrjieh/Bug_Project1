//
// Created by orjie on 20/03/2023.
//

#include "Bug.h"
#include "Direction.h"
#include <iostream>

//default constructor
Bug::Bug(){
    this->id = 0;
    this->position = std::make_pair(0,0);
    this->direction = Direction::North; // set default direction to North using enum
    this->size = 0;
    this->alive = false;
}

//constructor
Bug::Bug(int id, std::pair<int, int> position, Direction direction, int size, bool alive) {
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

const std::pair<int, int> &Bug::getPosition() const {
    return position;
}

void Bug::setPosition(const std::pair<int, int> &p) {
    Bug::position = p;
}

//direction in which the bug is facing :
//1=North, 2=East, 3=South, 4=West (or use enum)
Direction Bug::getDirection() const {
    return direction;
}

void Bug::setDirection(Direction d) {
    Bug::direction = d;
}

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

const std::list<std::pair<int, int>> & Bug::getPath() const {
    return path;
}

void Bug::setPath(const std::list<std::pair<int, int>>& p) {
    Bug::path = p;
}

//to add a position to the path
void Bug::addPath(const std::pair<int, int>& position) {
    path.push_back(position);
}

int Bug::getPredator() const {
    return predator;
}

void Bug::setEatenBy(const int& p) {
    Bug::predator = p;
}

//getter and setter for bug type
std::string Bug::getType() const {
    return type;
}

void Bug::setType(const std::string& t) {
    Bug::type = t;
}

//Checks if a bug is against an edge of the board AND if it is
//facing in the direction of that edge. If so, its way is blocked.
//[Used by the move() function], board is siz2 10x10
//    bool isWayBlocked();
bool Bug::isWayBlocked() {
    const int BOARD_SIZE = 10;
    bool wayBlocked = false;
    switch (direction) {
        case Direction::North:
            wayBlocked = (position.second == 0);
            break;
        case Direction::East:
            wayBlocked = (position.first == (BOARD_SIZE - 1));
            break;
        case Direction::South:
            wayBlocked = (position.second == (BOARD_SIZE - 1));
            break;
        case Direction::West:
            wayBlocked = (position.first == 0);
            break;
        case Direction::NorthEast:
            wayBlocked = (position.first == (BOARD_SIZE - 1) || position.second == 0);
            break;
        case Direction::SouthEast:
            wayBlocked = (position.first == (BOARD_SIZE - 1) || position.second == (BOARD_SIZE - 1));
            break;
        case Direction::SouthWest:
            wayBlocked = (position.first == 0 || position.second == (BOARD_SIZE - 1));
            break;
        case Direction::NorthWest:
            wayBlocked = (position.first == 0 || position.second == 0);
            break;
        default:
            // handle invalid direction
            break;
    }

    return wayBlocked;
}

//the virtual destructor
Bug::~Bug() {
    std::cout << "Bug destructor called" << std::endl;
}