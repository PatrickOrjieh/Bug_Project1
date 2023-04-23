//
// Created by orjie on 28/03/2023.
//

#ifndef BUG_PROJECT_BOARD_H
#define BUG_PROJECT_BOARD_H

#include "Bug.h"
#include <vector>
#include "Direction.h"
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

class Board {
    //private members
    static const int BOARD_SIZE = 10;
    //initializing the board to be a vector of bug cells
    std::vector <Bug*> cells[100];
    std::vector <Bug*> bugs;
// to keep track of the number of rounds played
    int rounds = 0;
public:
    //default constructor
    Board();

    bool initialiseBoard(const std::string& filename);

    bool isValidBugData(const std::string& bugType, const std::string& bugIdStr, const std::string& bugXStr, const std::string& bugYStr, const std::string& directionStr, const std::string& sizeStr, const std::string& hopLengthStr, const std::string& bishopLengthStr) const;

    void createHopperBug(int bugId, int bugX, int bugY, int direction, int size, int hopLength);

    void createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size);

    void createBishopBug(int bugId, int bugX, int bugY, int direction, int size, int bisLength);

    void displayAllBugs() const;

    bool isBoardEmpty() const;

    void findBugById() const;

    void tapBoard();

    int countAliveBugs() const;

    Bug* findLastAliveBug() const;

    //to simulate the fight between bugs in the same cell  this is without graphics
    void simulate();

    //was done this way so that the method could be reused in the writeLifeHistoryOfAllBugsToFile() method
    void displayLifeHistoryOfAllBugs(std::ostream& out = std::cout) const;

    void writeLifeHistoryOfAllBugsToFile() const;

    void displayAllCells() const;

    //to draw the board  with the SFML library
    //this is the simulation of the board with graphics and superbug
    void drawBoard();

    void rotate(Bug *const &bug, sf::Sprite &sprite, float &offsetX, float &offsetY) const;

    bool isCellEmpty(int x, int y);

    //destructor
    ~Board();
};


#endif //BUG_PROJECT_BOARD_H
