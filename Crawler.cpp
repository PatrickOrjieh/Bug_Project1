//
// Created by orjie on 22/03/2023.
//


#include "Crawler.h"
#include <iostream>

//default constructor
Crawler::Crawler() : Bug() {

}

//make up different constructors with different parameters
Crawler::Crawler(int id, std::pair<int, int> position, int direction, int size, bool alive) : Bug(id, position, direction, size, alive) {

}

//A Crawler bug moves according to these rules:
//- moves by 1 unit in the direction it is currently facing
//- if at edge of board and can’t move in current direction (because
//its way is blocked), then, set a new direction at random. (Repeat
//until bug can move forward). - record new position in the crawler's path history
//move function
//void move(){}
