//
// Created by orjie on 20/04/2023.
//
#include "SuperBug.h"
#include <iostream>
#include "Direction.h"
#include <SFML/Graphics.hpp>

//default constructor
SuperBug::SuperBug() : Bug() {

}

//make up different constructors with different parameters
SuperBug::SuperBug(int id, std::pair<int, int> position, Direction direction, int size, bool alive) : Bug(id, position,
                                                                                                          direction, size,
                                                                                                          alive) {

}

//A SuperBug bug moves according to these rules but is controlled by the user with the arrow keys:
//can move left, right, up, down by 1 unit but can’t move off the board so if iswayblocked() is true, then don’t move
//record new position in the superbug's path history
//note that board size is 10x10
void SuperBug::move() {
    std::pair<int, int> currentPosition = getPosition();
    int x = position.first;
    int y = position.second;
    if (x > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (!isWayBlocked()) {
            position.first -= 1;
        }
    }
    if (x < 9 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (!isWayBlocked()) {
            position.first += 1;
        }
    }
    if (y > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!isWayBlocked()) {
            position.second -= 1;
        }
    }
    if (y < 9 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!isWayBlocked()) {
            position.second += 1;
        }
    }
    addPath(currentPosition);
}

void SuperBug::displayBug() {
    std::cout << getId() << " SuperBug (" << getPosition().first << "," << getPosition().second << ") " << getSize()
              << " ";
    switch (getDirection()) {
        case North:
            std::cout << "North ";
            break;
        case South:
            std::cout << "South ";
            break;
        case East:
            std::cout << "East ";
            break;
        case West:
            std::cout << "West ";
            break;
    }
    if (isAlive()) {
        std::cout << "Alive" << std::endl;
    } else {
        std::cout << "Dead" << std::endl;
    }
}

//destructor
SuperBug::~SuperBug() {

}