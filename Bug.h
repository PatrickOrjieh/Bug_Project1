//
// Created by orjie on 20/03/2023.
//

#ifndef BUG_PROJECT_BUG_H
#define BUG_PROJECT_BUG_H

#include <string>
#include <utility>
#include <list>
#include "Direction.h"

//Abstract Base Class) ( Data members to be declared as “private”)
class Bug {
protected:
    //Identification number (id) for a bug (1,2,3,4,…)
    int id;

    //Co-ordinate pair (x,y) represented in a ‘pair’ struct from
    //<utility> standard library. (0,0) is top left cell on board.
    std::pair<int, int> position;

    //Size of the bug (initially 1-20); biggest bug wins in a fight
    //and others on same cell are eaten. Winner grows during a
    //fight by the sum of the sizes of other bugs eaten.
    int size;

    //Flag indicating life status of a bug. All bugs set to ‘true’
    //initially. When eaten, this flag is set to ‘false’.
    //true => alive, false => dead
    bool alive;

    // Path taken by a bug. (i.e. the List of positions (on grid) that a
    //bug visited.)
    std::list<std::pair<int, int>> path;

    //for the direction of the bug
    Direction direction;

    //will keep a variable called predator to know the bug that ate the others
    std::string predator;

public:
    //default constructor
    Bug();

    //make up different constructors with different parameters
    Bug(int id, std::pair<int, int> position, Direction direction, int size, bool alive);

    //getters and setters
    int getId() const;

    void setId(int id);

    const std::pair<int, int>& getPosition() const;

    void setPosition(const std::pair<int, int>& position);

    Direction getDirection() const;

    void setDirection(Direction direction);

    int getSize() const;

    void setSize(int size);

    bool isAlive() const;

    void setAlive(bool alive);

    const std::list<std::pair<int, int>>& getPath() const;

    void setPath(const std::list<std::pair<int, int>>& path);

    void addPath(const std::pair<int, int>& position);

    //to get and set the eaten by
    std::string getPredator() const;

    void setEatenBy(const std::string& predator);

    //methods
    //All derived classes must implement logic to move a bug
    //from its current position to a new position based on
    //movement rules for the particular bug type. No
    //implementation is require in the Bug base class, so move()
    //can be made a pure virtual function in the Bug class.
    virtual void move() = 0;

    //make the displayBug() function virtual so that it can be overridden
    //in the derived classes (Crawler and Hopper)
    virtual void displayBug()=0;

    //Checks if a bug is against an edge of the board AND if it is
    //facing in the direction of that edge. If so, its way is blocked.
    //[Used by the move() function]
    bool isWayBlocked();

//    ~Bug(); //destructor
    //it might be better to make the destructor virtual
    virtual ~Bug();
};


#endif //BUG_PROJECT_BUG_H
