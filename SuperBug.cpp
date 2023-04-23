//
// Created by orjie on 20/04/2023.
//

#include "SuperBug.h"
////
//// Created by orjie on 22/03/2023.
////
//
//
//#include "Crawler.h"
//#include <iostream>
//#include "Direction.h"
//
////default constructor
//Crawler::Crawler() : Bug() {
//
//}
//
////make up different constructors with different parameters
//Crawler::Crawler(int id, std::pair<int, int> position, Direction direction, int size, bool alive) : Bug(id, position,
//                                                                                                        direction, size,
//                                                                                                        alive) {
//
//}
//
////A Crawler bug moves according to these rules:
////- moves by 1 unit in the direction it is currently facing
////- if at edge of board and can’t move in current direction (because
////its way is blocked), then, set a new direction at random. (Repeat
////until bug can move forward). - record new position in the crawler's path history
////note that board size is 10x10
//void Crawler::move() {
//    // if the bug is at the edge of the board and can't move in the current direction, set a new direction at random
//    while (isWayBlocked()) {
//        int newDirection = rand() % 4 + 1;
//        setDirection((Direction) newDirection);
//    }
//
//    //get the current position of the bug
//    std::pair<int, int> currentPosition = getPosition();
//    //get the current direction of the bug
//    Direction currentDirection = getDirection();
//    //get the current path of the bug
//    std::list<std::pair<int, int>> currentPath = getPath();
//
//    //move the bug by 1 unit in the direction it is currently facing
//    switch (currentDirection) {
//        case North:
//            currentPosition.second -= 1;
//            break;
//        case South:
//            currentPosition.second += 1;
//            break;
//        case East:
//            currentPosition.first += 1;
//            break;
//        case West:
//            currentPosition.first -= 1;
//            break;
//    }
//    //set the new position of the bug
//    setPosition(currentPosition);
//    //add the new position to the path of the bug
//    addPath(currentPosition);
//}
//
////method to display the bug in a good way with all its attributes
////like this 101 Crawler (3,4) 18 East Dead
////dhow twh action direction no tjust the number
//void Crawler::displayBug() {
//    std::cout << getId() << " Crawler (" << getPosition().first << "," << getPosition().second << ") " << getSize()
//              << " ";
//    switch (getDirection()) {
//        case North:
//            std::cout << "North ";
//            break;
//        case South:
//            std::cout << "South ";
//            break;
//        case East:
//            std::cout << "East ";
//            break;
//        case West:
//            std::cout << "West ";
//            break;
//    }
//    if (isAlive()) {
//        std::cout << "Alive" << std::endl;
//    } else {
//        std::cout << "Dead" << std::endl;
//    }
//}
//
////destructor
//Crawler::~Crawler() {
//
//}

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