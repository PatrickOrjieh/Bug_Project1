//
// Created by orjie on 27/03/2023.
//

#ifndef BUG_PROJECT_HOPPER_H
#define BUG_PROJECT_HOPPER_H

#include "Bug.h"

class Hopper: public Bug {
private:
    int hopLength;

public:
    //default constructor
    Hopper();

    //make up different constructors with all the parameters
    Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int hopLength);

    int getHopLength() const;

    void setHopLength(int hopLength);

    //move the bug
    void move() override;

    //display the bug
    void displayBug() override;

    //destructor
    ~Hopper();
};


#endif //BUG_PROJECT_HOPPER_H
