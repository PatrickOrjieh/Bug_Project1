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

#include <iostream>;
#include <fstream>;
#include <sstream>;
#include <vector>;
#include <string>;
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
void Board::initialiseBoard(std::string filename) {
    //open the file
    ifstream file(filename);
    //check if the file is open
    if (file.is_open()) {
        //read the file line by line
        string line;
        while (getline(file, line)) {
            //create a string stream to read the line
            stringstream ss(line);
            //create a string to store the data
            string data;
            //create a vector to store the data
            vector<string> data_vector;
            //read the line and store the data in the vector
            while (getline(ss, data, ',')) {
                data_vector.push_back(data);
            }
            //check if the data is valid
            if (data_vector.size() == 5 || data_vector.size() == 6) {
                //check if the bug type is valid
                if (data_vector[0] == "C" || data_vector[0] == "H") {
                    //check if the bug id is valid
                    if (stoi(data_vector[1]) > 0) {
                        //check if the bug x position is valid
                        if (stoi(data_vector[2]) >= 0 && stoi(data_vector[2]) < BOARD_SIZE) {
                            //check if the bug y position is valid
                            if (stoi(data_vector[3]) >= 0 && stoi(data_vector[3]) < BOARD_SIZE) {
                                //check if the bug direction is valid
                                if (stoi(data_vector[4]) >= 1 && stoi(data_vector[4]) <= 4) {
                                    //check if the bug size is valid
                                    if (stoi(data_vector[5]) > 0) {
                                        //check if the bug is a hopper
                                        if (data_vector[0] == "H") {
                                            //check if the hop distance is valid
                                            if (stoi(data_vector[6]) > 0) {
                                                //check if the bug is already in that position
                                                bool bug_in_position = false;
                                                for (int i = 0; i < bug_vector.size(); i++) {
                                                    if (bug_vector[i]->getPosition().first == stoi(data_vector[2]) && bug_vector[i]->getPosition().second == stoi(data_vector[3])) {
                                                        bug_in_position = true;
                                                    }
                                                }
                                                //if the bug is not in that position then create the bug and add it to the vector
                                                if (!bug_in_position) {
                                                    //create the bug
                                                    // Hopper(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int hopLength);
                                                    Bug *bug = new Hopper(stoi(data_vector[1]), std::make_pair(stoi(data_vector[2]), stoi(data_vector[3])), static_cast<Direction>(stoi(data_vector[4])), stoi(data_vector[5]), true, stoi(data_vector[6]));
                                                    //add the bug to the vector
                                                    bug_vector.push_back(bug);
                                                } else {
                                                    cout << "Error: Bug already in that position" << endl;
                                                }
                                            } else {
                                                cout << "Error: Invalid hop distance" << endl;
                                            }
                                        } else {
                                            //check if the bug is already in that position
                                            bool bug_in_position = false;
                                            for (int i = 0; i < bug_vector.size(); i++) {
                                                if (bug_vector[i]->getPosition().first == stoi(data_vector[2]) && bug_vector[i]->getPosition().second == stoi(data_vector[3])) {
                                                    bug_in_position = true;
                                                }
                                            }
                                            //if the bug is not in that position then create the bug and add it to the vector
                                            if (!bug_in_position) {
                                                //create the bug
                                                //Crawler(int id, std::pair<int, int> position, Direction direction, int size, bool alive);
                                                Bug *bug = new Crawler(stoi(data_vector[1]), std::make_pair(stoi(data_vector[2]), stoi(data_vector[3])), static_cast<Direction>(stoi(data_vector[4])), stoi(data_vector[5]), true);
                                                //add the bug to the vector
                                                bug_vector.push_back(bug);
                                            } else {
                                                cout << "Error: Bug already in that position" << endl;
                                            }
                                        }
                                    } else {
                                        cout << "Error: Invalid bug size" << endl;
                                    }
                                } else {
                                    cout << "Error: Invalid bug direction" << endl;
                                }
                            } else {
                                cout << "Error: Invalid bug y position" << endl;
                            }
                        } else {
                            cout << "Error: Invalid bug x position" << endl;
                        }
                    } else {
                        cout << "Error: Invalid bug id" << endl;
                    }
                } else {
                    cout << "Error: Invalid bug type" << endl;
                }
            } else {
                cout << "Error: Invalid data" << endl;
            }
        }
    } else {
        cout << "Error: File not found" << endl;
    }
}

//destructor
Board::~Board() {
    //delete the bugs
    for (int i = 0; i < bug_vector.size(); i++) {
        delete bug_vector[i];
    }
}