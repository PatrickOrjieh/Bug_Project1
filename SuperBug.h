//
// Created by orjie on 20/04/2023.
//

#ifndef BUG_PROJECT_SUPERBUG_H
#define BUG_PROJECT_SUPERBUG_H


#include "Bug.h"

class SuperBug: public Bug {

public:

//default constructor
    SuperBug();

    //make up different constructors with different parameters
    SuperBug(int id, std::pair<int, int> position, Direction direction, int size, bool alive);

    //methods
    //All derived classes must implement logic to move a bug
    //from its current position to a new position based on
    //movement rules for the particular bug type. No
    //implementation is require in the Bug base class, so move()
    //can be made a pure virtual function in the Bug class.
    void move() override;

    void displayBug() override;

    ~SuperBug(); //destructor

};


#endif //BUG_PROJECT_SUPERBUG_H
