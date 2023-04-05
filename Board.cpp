//
// Created by orjie on 28/03/2023.
//

#include "Board.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Bug.h"
#include "Direction.h"
#include "Utils.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//default constructor
Board::Board() {
    //initialise the cells
//    for (int i = 0; i < BOARD_SIZE; i++) {
//        for (int j = 0; j < BOARD_SIZE; j++) {
//            cells[i][j] = std::make_pair(i,j);
//        }
//    }
}

//method to initialise the board from a text file that has the bug data with proper error handling and error checking
//the data is in the following format:bug_type = char, bug_id = int, bug_x = int, bug_y = int, direction = 1/2/3/4,
//size = int and if the bug is a hopper then the hop distance is also included and as the data is read checks that
//the position is valid and that the bug is not already in that position. for all parts do proper error handling and error checking
void Board::initialiseBoard(const std::string &filename) {
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
bool Board::isValidBugData(const std::string &bugType, const std::string &bugIdStr, const std::string &bugXStr,
                           const std::string &bugYStr, const std::string &directionStr, const std::string &sizeStr,
                           const std::string &hopLengthStr) const {
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
    Hopper *hopper = new Hopper(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true,
                                hopLength);

    //add the first position to the path
    hopper->addPath(std::make_pair(bugX, bugY));
    //using the formula for the cells
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(hopper);
}

//method to create a crawler bug
void Board::createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size) {
    //    Crawler(int id, std::pair<int, int> position, Direction direction, int size, bool alive);
    Crawler *crawler = new Crawler(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true);
    //add the first position to the path#
    crawler->addPath(std::make_pair(bugX, bugY));
    //using the formula for the cells
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(crawler);
}

//check if the bugs are empty
//bool Board::isBugVectorEmpty() const {
//    return bug_vector.empty();
//}

//check if the board is empty
bool Board::isBoardEmpty() const {
    return cells->empty();
}

//to display all bugs
//void Board::displayAllBugs() const {
//    for (const auto& bug : bug_vector) {
//        std::cout << bug->getId() << " ";
//        if (dynamic_cast<Crawler*>(bug)) {
//            std::cout << "Crawler ";
//        } else {
//            std::cout << "Hopper ";
//        }
//        std::cout << "(" << bug->getPosition().first << "," << bug->getPosition().second << ") ";
//        std::cout << bug->getSize() << " ";
//
//        switch (bug->getDirection()) {
//            case Direction::North:
//                std::cout << "North ";
//                break;
//            case Direction::East:
//                std::cout << "East ";
//                break;
//            case Direction::South:
//                std::cout << "South ";
//                break;
//            case Direction::West:
//                std::cout << "West ";
//                break;
//        }
//
//        if (dynamic_cast<Hopper*>(bug)) {
//            std::cout << dynamic_cast<Hopper*>(bug)->getHopLength() << " ";
//        } else {
//            std::cout << "- ";
//        }
//
//        if (bug->isAlive()) {
//            std::cout << "Alive";
//        } else {
//            std::cout << "Dead";
//        }
//
//        std::cout << std::endl;
//    }
//}

void Board::displayAllBugs() const {
    //using an iterator through vector<Bug*> cells[]
    for (int i = 0; i < 100; i++) {
        for (std::vector<Bug *>::const_iterator it = cells[i].cbegin(); it != cells[i].cend(); ++it) {
            //use the displayBug method from the Crawler and Hopper classes
            (*it)->displayBug();
        }
    }
}

////3. Find a Bug
//    //User to be asked to input a bug id, and the system will search for that bug. Display bug details if
//    //found, otherwise display “bug xxx not found”
//    void findBugById() const; make use of the displayBug from the Crawler and Hopper classes
void Board::findBugById() const {
    int bugId = utils::readInt("Enter bug id: ");
    //i tried looking for teh most efficient way to do this, but i couldn't find anything
    for (int i = 0; i < 100; i++) {
        for (std::vector<Bug *>::const_iterator it = cells[i].cbegin(); it != cells[i].cend(); ++it) {
            if ((*it)->getId() == bugId) {
                (*it)->displayBug();
                return;
            }
        }
    }
    std::cout << "Bug " << bugId << " not found" << std::endl;
}

//4. Tap the Bug Board
//This option simulates tapping the bug board, which prompts all the bugs to move. This will require
//calling the move() function on all bugs. The move() method must be implemented differently for
//Crawler and Hopper. (See class details above). Later you will be asked to implement fight/eat.
//We recommend that you implement only move() initially. The fight and eat behaviour can be
//developed later, when all other functionality has been implemented.
//void Board::tapBoard() {
//    for (Bug* bug : bug_vector) {
//        bug->move();
//    }
//}

void Board::tapBoard() {
    for (int i = 0; i < 100; i++) {
        for (Bug *bug: cells[i]) {
            bug->move();
        }
    }
}

//5. Display Life History of all bugs
//Display each bug’s details and the path that it travelled from beginning to death. The history will be
//recorded in the path field (which is a chronological list of positions). (Type list must be used)
//101 Crawler Path: (0,0),(0,1),(1,1),(2,1),(3,1) Eaten by 203
//102 Hopper Path: (2,2),(2,3), Alive!
//void Board::displayLifeHistoryOfAllBugs() const {
//    for (Bug* bug : bug_vector) {
//        std::cout << bug->getId() << " ";
//        if (dynamic_cast<Crawler*>(bug)) {
//            std::cout << "Crawler";
//        } else if (dynamic_cast<Hopper*>(bug)) {
//            std::cout << "Hopper";
//        }
//        std::cout << " Path: ";
//        for (auto const& pos : bug->getPath()) {
//            std::cout << "(" << pos.first << "," << pos.second << ")";
//            if (&pos != &bug->getPath().back()) {
//                std::cout << ",";
//            }
//        }
//        std::cout << std::endl;
//    }
//}

void Board::displayLifeHistoryOfAllBugs(std::ostream &out) const {
    for (int i = 0; i < 100; i++) {
        for (Bug *bug: cells[i]) {
            out << bug->getId() << " ";
            if (dynamic_cast<Crawler *>(bug)) {
                out << "Crawler";
            } else if (dynamic_cast<Hopper *>(bug)) {
                out << "Hopper";
            }
            out << " Path: ";
            for (auto const &pos: bug->getPath()) {
                out << "(" << pos.first << "," << pos.second << ")";
                if (&pos != &bug->getPath().back()) {
                    out << ",";
                }
            }
            out << std::endl;
        }
    }
}



//6. Exit - Write the life history of all bugs to a text file called “bugs_life_history_date_time.out”
//where date_time is the current date and time. The file should be in the same format as the
//displayLifeHistoryOfAllBugs() function above. The file should be created in the same directory as
//the executable.
void Board::writeLifeHistoryOfAllBugsToFile() const {
    // Get the directory path to put the file
    std::filesystem::path dir_path = std::filesystem::current_path().parent_path();

    // Get the file name for the output file
    std::string file_name = "bugs_life_history_" + utils::getCurrentDateTime() + ".out";
    // Replace invalid characters with '_'
    std::replace(file_name.begin(), file_name.end(), ':', '_');
    // Combine the directory path and file name to create the file path
    std::filesystem::path file_path = dir_path / file_name;

    // Open the output file
    std::ofstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing.");
    }

    // Write the life history of all bugs to the output file
    displayLifeHistoryOfAllBugs(file);
    if (!file.good()) {
        throw std::runtime_error("Error writing to file.");
    }

    cout << "Life history of all bugs written to file: " << file_path << endl;
    // Close the output file
    file.close();
}

//7. Display all Cells
//Display all cells in sequence, and the name and id of all bugs currently occupying each cell.
//(0,0): empty // meaning: cell (0,0) is empty
//(0,1): empty
//(0,2): Crawler 101, Crawler 103 // i.e. the 2 Crawler bugs in this cell
//(etc…)
//(1,0): Hopper 102
//(1,1): Crawler 105, Hopper 107, Crawler 109
//void displayAllCells() const;
void Board::displayAllCells() const {
    //starting from (0,0) till (9,9)
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int check = j * BOARD_SIZE + i;
            std::cout << "(" << i << "," << j << "): ";
            if(cells[check].empty()){
                std::cout << "empty" << std::endl;
            } else {
                for (Bug *bug: cells[check]) {
                    if (dynamic_cast<Crawler *>(bug)) {
                        std::cout << "Crawler " << bug->getId() << " ";
                    } else if (dynamic_cast<Hopper *>(bug)) {
                        std::cout << "Hopper " << bug->getId() << " ";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}

//destructor
//Board::~Board() {
//    //delete the bugs
//    for (auto & i : bug_vector) {
//        delete i;
//    }
//}

//destructors
Board::~Board() {
    //    std::vector <Bug*> cells[99];
    for (int i = 0; i < 99; i++) {
        //using an iterator to delete the bugs
        for (std::vector<Bug *>::iterator it = cells[i].begin(); it != cells[i].end(); ++it) {
            delete *it;
            cout << "deleting bug" << endl;
        }
    }
}