//
// Created by orjie on 28/03/2023.
//

#ifndef BUG_PROJECT_BOARD_H
#define BUG_PROJECT_BOARD_H

//For convenience we want to be able to store all bugs in a vector of some type – that will store both
//Crawlers and Hoppers – so that we can iterate over all bugs and treat then in a similar way.
//However, we can’t use a vector of Bug objects ( vector<Bug> ), because the derived class objects
//(e.g. Hopper) would not fit into a Bug object vector element. So, one option is to create a vector of
//pointers to Bug objects ( vector<Bug *> ). The elements of this vector are of type ‘pointer to Bug’, so
//they can point at any derived class objects of Bug (e.g. Crawler or Hopper).
//Therefore, we must declare a vector of pointers to Bug objects [ in main() ], and populate it by
//reading data from a text file (“bugs.txt”), instantiating Bug objects dynamically on the Heap, and
//adding their addresses to the vector.
//vector<Bug*> bug_vector;
//Board Class
//Board class encapsulates the vector and cells. No access to internal workings of board is to be
//‘leaked’ outside the Board class, so no references or pointers to any internal objects are to be
//returned. Return only copies of data if required. (So, internally pointers can be passed around, but
//for public interface functions, provide only copies of objects. Consider the interface.)

#include "Bug.h"
#include <vector>
#include <adomd.h>

class Board: public Bug {
    //private members
    static const int BOARD_SIZE = 10;
    //vector of pointers to Bug objects
    std::vector<Bug*> bug_vector;
    // 2D array of pairs representing the cells on the board
    std::pair<int,int> cells[BOARD_SIZE][BOARD_SIZE];

public:
    //default constructor
    Board();

    //methos ot initialise the board from a text file that has the bug data
    void initialiseBoard(std::string filename);

    //destructor
    ~Board();
};


#endif //BUG_PROJECT_BOARD_H
