//
// Created by orjie on 22/03/2023.
//

#ifndef BUG_PROJECT1_CRAWLER_H
#define BUG_PROJECT1_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug{

    //A Crawler bug moves according to these rules:
    //- moves by 1 unit in the direction it is currently facing
    //- if at edge of board and can’t move in current direction (because
    //its way is blocked), then, set a new direction at random. (Repeat
    //until bug can move forward). - record new position in the crawler's path history
public:
    //default constructor
    Crawler();

    //make up different constructors with different parameters
    Crawler(int id, std::pair<int, int> position, int direction, int size, bool alive);

    //move function
    //void move(){}
    void move() override;

    //destructor
    ~Crawler();
};

#endif //BUG_PROJECT1_CRAWLER_H
