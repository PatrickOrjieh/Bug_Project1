//
// Created by orjie on 22/03/2023.
//

#ifndef BUG_PROJECT_CRAWLER_H
#define BUG_PROJECT_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    //default constructor
    Crawler();

    //make up different constructors with different parameters
    Crawler(int id, std::pair<int, int> position, Direction direction, int size, bool alive);

    void move() override;

    void displayBug() override;

    ~Crawler(); //destructor
};

#endif //BUG_PROJECT_CRAWLER_H
