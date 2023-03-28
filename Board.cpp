//
// Created by orjie on 28/03/2023.
//

#include "Board.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Bug.h"
////
//// Created by orjie on 28/03/2023.
////
//
//#ifndef BUG_PROJECT_BOARD_H
//#define BUG_PROJECT_BOARD_H
//
////For convenience we want to be able to store all bugs in a vector of some type – that will store both
////Crawlers and Hoppers – so that we can iterate over all bugs and treat then in a similar way.
////However, we can’t use a vector of Bug objects ( vector<Bug> ), because the derived class objects
////(e.g. Hopper) would not fit into a Bug object vector element. So, one option is to create a vector of
////pointers to Bug objects ( vector<Bug *> ). The elements of this vector are of type ‘pointer to Bug’, so
////they can point at any derived class objects of Bug (e.g. Crawler or Hopper).
////Therefore, we must declare a vector of pointers to Bug objects [ in main() ], and populate it by
////reading data from a text file (“bugs.txt”), instantiating Bug objects dynamically on the Heap, and
////adding their addresses to the vector.
////vector<Bug*> bug_vector;
////Board Class
////Board class encapsulates the vector and cells. No access to internal workings of board is to be
////‘leaked’ outside the Board class, so no references or pointers to any internal objects are to be
////returned. Return only copies of data if required. (So, internally pointers can be passed around, but
////for public interface functions, provide only copies of objects. Consider the interface.)
//
//#include "Bug.h"
//#include <vector>
//#include <adomd.h>
//
//class Board {
//    //private members
//    static const int BOARD_SIZE = 10;
//    //vector of pointers to Bug objects
//    std::vector<Bug*> bug_vector;
//    // 2D array of pairs representing the cells on the board
//    std::pair<int,int> cells[BOARD_SIZE][BOARD_SIZE];
//
//public:
//    //default constructor
//    Board();
//
//    //methos ot initialise the board from a text file that has the bug data
//    void initialiseBoard(std::string filename);
//
//    //destructor
//    ~Board();
//};
//
//
//#endif //BUG_PROJECT_BOARD_H

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
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File not found" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> lineData;
        string bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr;
        getline(lineStream, bugType, ';');
        getline(lineStream, bugIdStr, ';');
        getline(lineStream, bugXStr, ';');
        getline(lineStream, bugYStr, ';');
        getline(lineStream, directionStr, ';');
        getline(lineStream, sizeStr, ';');
        getline(lineStream, hopLengthStr, ';');

        if (!isValidBugData(bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr)) {
            cout << "Error: Invalid bug data" << endl;
            continue;
        }

        int bugId = stoi(bugIdStr);
        int bugX = stoi(bugXStr);
        int bugY = stoi(bugYStr);
        int direction = stoi(directionStr);
        int size = stoi(sizeStr);
        int hopLength = stoi(hopLengthStr);

        if (bugType == "H") {
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

//destructor
Board::~Board() {
    //delete the bugs
    for (auto & i : bug_vector) {
        delete i;
    }
}