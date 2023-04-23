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
    int id;

    std::pair<int, int> position;

    int size;

    bool alive;

    std::list<std::pair<int, int>> path;

    Direction direction;

    int predator;

    std::string type;

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

    //get and set the type of the bug
    std::string getType() const;

    void setType(const std::string& type);

    //to get and set the eaten by
    int getPredator() const;

    void setEatenBy(const int& predator);

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
