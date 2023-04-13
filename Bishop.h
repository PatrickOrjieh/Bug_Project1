//
// Created by orjie on 14/04/2023.
//

#ifndef BUG_PROJECT1_BISHOP_H
#define BUG_PROJECT1_BISHOP_H

//int bisLength; The distance/length that a particular bishop bug can move (in
//range (1-6 units)
//just like the bishop in chess game, the bishop can only move diagonally
//void move(){} A Bishop bug moves according to these rules:
//- moves by “bisLength” units in current direction
//- if at edge of board and can’t move over edge in
//current direction, set a new direction at random
//(repeat until bug can move forward) and then
//move.
//- if bug can’t hop the full ‘hopLength’, then the bug
//does move but ‘hits’ the edge and falls on the
//square where it hit the edge/wall
//- record new position in hoppers path history

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


#endif //BUG_PROJECT1_BISHOP_H
