//
// Created by orjie on 28/03/2023.
//

#include "Board.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Bug.h"
#include "Direction.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//default constructor
Board::Board() {
    //initialise the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cells[i][j] = std::make_pair(i,j);
        }
    }
}

//method to initialise the board from a text file that has the bug data with proper error handling and error checking
//the data is in the following format:bug_type = char, bug_id = int, bug_x = int, bug_y = int, direction = 1/2/3/4,
//size = int and if the bug is a hopper then the hop distance is also included and as the data is read checks that
//the position is valid and that the bug is not already in that position. for all parts do proper error handling and error checking
void Board::initialiseBoard(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: File not found" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<std::string> lineData;
        std::string bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr;
        std::getline(lineStream, bugType, ';');
        std::getline(lineStream, bugIdStr, ';');
        std::getline(lineStream, bugXStr, ';');
        std::getline(lineStream, bugYStr, ';');
        std::getline(lineStream, directionStr, ';');
        std::getline(lineStream, sizeStr, ';');
        if (bugType == "H") {
            std::getline(lineStream, hopLengthStr, ';');
        }

        if (!isValidBugData(bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr)) {
            std::cout << "Error: Invalid bug data" << std::endl;
            continue;
        }

        int bugId = std::stoi(bugIdStr);
        int bugX = std::stoi(bugXStr);
        int bugY = std::stoi(bugYStr);
        int direction = std::stoi(directionStr);
        int size = std::stoi(sizeStr);
        int hopLength = 0;
        if (bugType == "H") {
            hopLength = std::stoi(hopLengthStr);
            createHopperBug(bugId, bugX, bugY, direction, size, hopLength);
        } else {
            createCrawlerBug(bugId, bugX, bugY, direction, size);
        }
    }
}

//method to check if the bug data is valid
bool Board::isValidBugData(const std::string& bugType, const std::string& bugIdStr, const std::string& bugXStr, const std::string& bugYStr, const std::string& directionStr, const std::string& sizeStr, const std::string& hopLengthStr) const {
    int bugId = stoi(bugIdStr);
    int bugX = stoi(bugXStr);
    int bugY = stoi(bugYStr);
    int direction = stoi(directionStr);
    int size = stoi(sizeStr);

    if (bugType != "C" && bugType != "H") {
        return false;
    }
    if (bugId <= 0) {
        return false;
    }
    if (bugX < 0 || bugX >= BOARD_SIZE) {
        return false;
    }
    if (bugY < 0 || bugY >= BOARD_SIZE) {
        return false;
    }
    if (direction < 1 || direction > 4) {
        return false;
    }
    if (size <= 0) {
        return false;
    }
    if (bugType == "H") {
        int hopLength = stoi(hopLengthStr);
        if (hopLength <= 0) {
            return false;
        }
    }
    return true;
}

//method to create a hopper bug
void Board::createHopperBug(int bugId, int bugX, int bugY, int direction, int size, int hopLength) {
    //    Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int hopLength);
    Hopper* hopper = new Hopper(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true, hopLength);
    bug_vector.push_back(hopper);
}

//method to create a crawler bug
void Board::createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size) {
    //    Crawler(int id, std::pair<int, int> position, Direction direction, int size, bool alive);
    Crawler* crawler = new Crawler(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true);
    bug_vector.push_back(crawler);
}

//to display all bugs
void Board::displayAllBugs() const {
    for (const auto& bug : bug_vector) {
        std::cout << bug->getId() << " ";
        if (dynamic_cast<Crawler*>(bug)) {
            std::cout << "Crawler ";
        } else {
            std::cout << "Hopper ";
        }
        std::cout << "(" << bug->getPosition().first << "," << bug->getPosition().second << ") ";
        std::cout << bug->getSize() << " ";

        switch (bug->getDirection()) {
            case Direction::North:
                std::cout << "North ";
                break;
            case Direction::East:
                std::cout << "East ";
                break;
            case Direction::South:
                std::cout << "South ";
                break;
            case Direction::West:
                std::cout << "West ";
                break;
        }

        if (dynamic_cast<Hopper*>(bug)) {
            std::cout << dynamic_cast<Hopper*>(bug)->getHopLength() << " ";
        } else {
            std::cout << "- ";
        }

        if (bug->isAlive()) {
            std::cout << "Alive";
        } else {
            std::cout << "Dead";
        }

        std::cout << std::endl;
    }
}


//destructor
Board::~Board() {
    //delete the bugs
    for (auto & i : bug_vector) {
        delete i;
    }
}