//
// Created by orjie on 27/03/2023.
//

#ifndef BUG_PROJECT_HOPPER_H
#define BUG_PROJECT_HOPPER_H


//int hopLength; The distance/length that a particular hopper bug can hop (in
//range (2-4 units)
//void move(){} A Hopper bug moves according to these rules:
//- moves by “hopLength” units in current direction
//- if at edge of board and can’t move over edge in
//current direction, set a new direction at random
//(repeat until bug can move forward) and then
//move.
//- if bug can’t hop the full ‘hopLength’, then the bug
//does move but ‘hits’ the edge and falls on the
//square where it hit the edge/wall
//- record new position in hoppers path history

#include "Bug.h"

class Hopper: public Bug {
private:
    int hopLength;

public:
    //default constructor
    Hopper();

    //make up different constructors with all the parameters
    Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int hopLength);

    //i don't know if this is necessary to have the getter and setter for hopLength but i just put it here
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
