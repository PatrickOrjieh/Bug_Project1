//
// Created by orjie on 14/04/2023.
//

#ifndef BUG_PROJECT_BISHOP_H
#define BUG_PROJECT_BISHOP_H

#include "Bug.h"

class Bishop : public Bug {
private:
    int bisLength;

public:
    //default constructor
    Bishop();

    //make up different constructors with all the parameters
    Bishop(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int bisLength);

    //i don't know if this is necessary to have the getter and setter for hopLength but i just put it here
    int getBisLength() const;

    void setBisLength(int bisLength);

    //move the bug
    void move() override;

    //display the bug
    void displayBug() override;

    //destructor
    ~Bishop();

};


#endif //BUG_PROJECT_BISHOP_H
