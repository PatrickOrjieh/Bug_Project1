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
#include "Direction.h"

class Board {
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
    void initialiseBoard(const std::string& filename);

    //bool Board::isValidBugData(const std::string& bugType, const std::string& bugIdStr, const std::string& bugXStr, const std::string& bugYStr, const std::string& directionStr, const std::string& sizeStr, const std::string& hopLengthStr) const {
    bool isValidBugData(const std::string& bugType, const std::string& bugIdStr, const std::string& bugXStr, const std::string& bugYStr, const std::string& directionStr, const std::string& sizeStr, const std::string& hopLengthStr) const;

    //void Board::createHopperBug(int bugId, int bugX, int bugY, int direction, int size, int hopLength) {
    void createHopperBug(int bugId, int bugX, int bugY, int direction, int size, int hopLength);

    //void Board::createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size) {
    void createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size);

    //method to display all bugs on the board
    void displayAllBugs() const;

    //to check if the bugs is empty
    bool isBugVectorEmpty() const;

    //find bug by id
    void findBugById() const;

    //4. Tap the Bug Board
    //This option simulates tapping the bug board, which prompts all the bugs to move. This will require
    //calling the move() function on all bugs. The move() method must be implemented differently for
    //Crawler and Hopper. (See class details above). Later you will be asked to implement fight/eat.
    //We recommend that you implement only move() initially. The fight and eat behaviour can be
    //developed later, when all other functionality has been implemented.
    void tapBoard();

    //destructor
    ~Board();
};


#endif //BUG_PROJECT_BOARD_H
