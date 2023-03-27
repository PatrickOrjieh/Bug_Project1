//
// Created by orjie on 20/03/2023.
//

#ifndef BUG_PROJECT_BUG_H
#define BUG_PROJECT_BUG_H

#include <string>
#include <utility>
#include <list>

//Abstract Base Class) ( Data members to be declared as “private”)
class Bug {
private:
    //Identification number (id) for a bug (1,2,3,4,…)
    int id;

    //Co-ordinate pair (x,y) represented in a ‘pair’ struct from
    //<utility> standard library. (0,0) is top left cell on board.
    std::pair<int, int> position;

    //direction in which the bug is facing :
    //1=North, 2=East, 3=South, 4=West (or use enum)
    enum Direction {
        North = 1,
        East = 2,
        South = 3,
        West = 4
    } direction;

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

    //methods
    //All derived classes must implement logic to move a bug
    //from its current position to a new position based on
    //movement rules for the particular bug type. No
    //implementation is require in the Bug base class, so move()
    //can be made a pure virtual function in the Bug class.
    virtual void move() = 0;

    //Checks if a bug is against an edge of the board AND if it is
    //facing in the direction of that edge. If so, its way is blocked.
    //[Used by the move() function]
    bool isWayBlocked();

    ~Bug(); //destructor
};


#endif //BUG_PROJECT_BUG_H
