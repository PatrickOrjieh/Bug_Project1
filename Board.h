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
#include <iostream>

class Board {
    //private members
    static const int BOARD_SIZE = 10;
    //vector of pointers to Bug objects
//    std::vector<Bug*> bug_vector;
    // 2D array of pairs representing the cells on the board
//    std::pair<int,int> cells[BOARD_SIZE][BOARD_SIZE];

    //initializing the board to be a vector of bug cells
    std::vector <Bug*> cells[100];

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

    //display all bugs
    void displayAllBugs() const;

    //check if the bugs are empty
    bool isBoardEmpty() const;

    //3. Find a Bug
    //User to be asked to input a bug id, and the system will search for that bug. Display bug details if
    //found, otherwise display “bug xxx not found”
    void findBugById() const;

    //4. Tap the Bug Board
    //This option simulates tapping the bug board, which prompts all the bugs to move. This will require
    //calling the move() function on all bugs. The move() method must be implemented differently for
    //Crawler and Hopper. (See class details above). Later you will be asked to implement fight/eat.
    //We recommend that you implement only move() initially. The fight and eat behaviour can be
    //developed later, when all other functionality has been implemented.
    void tapBoard();

    //5. Display Life History of all bugs
    //Display each bug’s details and the path that it travelled from beginning to death. The history will be
    //recorded in the path field (which is a chronological list of positions). (Type list must be used)
    //101 Crawler Path: (0,0),(0,1),(1,1),(2,1),(3,1) Eaten by 203
    //102 Hopper Path: (2,2),(2,3), Alive!
//    void displayLifeHistoryOfAllBugs() const;
    void displayLifeHistoryOfAllBugs(std::ostream& out = std::cout) const;

    //6. Exit - Write the life history of all bugs to a text file called “bugs_life_history_date_time.out”
    //where date_time is the current date and time. The format of the file should be the same as the
    //displayLifeHistoryOfAllBugs() function above.
    void writeLifeHistoryOfAllBugsToFile() const;

    //7. Display all Cells
    //Display all cells in sequence, and the name and id of all bugs currently occupying each cell.
    //(0,0): empty // meaning: cell (0,0) is empty
    //(0,1): empty
    //(0,2): Crawler 101, Crawler 103 // i.e. the 2 Crawler bugs in this cell
    //(etc…)
    //(1,0): Hopper 102
    //(1,1): Crawler 105, Hopper 107, Crawler 109
    void displayAllCells() const;

    //destructor
    ~Board();
};


#endif //BUG_PROJECT_BOARD_H
