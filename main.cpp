#include <iostream>
#include <string>
#include "Board.h"
#include "Utils.h"
using namespace std;

//void to print the menu
void printMenu();

int main() {
    Board board;
    string filename = utils::readString("Please enter the name of the file to read the bug data from: ");
    board.initialiseBoard(filename);

    while(true){
        printMenu();
        int choice = utils::readInt("Please enter your choice: ");
        switch(choice){
            case 1:
                cout << "Displaying all the bugs on the board" << endl;
                if(board.isBoardEmpty()){
                    cout << "There are no bugs on the board" << endl;
                } else {
                    board.displayAllBugs();
                }
                break;
            case 2:
                cout << "Finding a bug by id" << endl;
                board.findBugById();
                break;
            case 3:
                cout << "Tapping the bug board" << endl;
                board.tapBoard();
                break;
            case 4:
                cout << "Displaying the life history of all the bugs" << endl;
                board.displayLifeHistoryOfAllBugs();
                break;
            case 5:
                cout << "Exiting" << endl;
                board.writeLifeHistoryOfAllBugsToFile();
                return 0;
            case 6:
                cout << "Displaying all cells" << endl;
                board.displayAllCells();
                break;
            default:
                cout << "Invalid choice, please enter a number between 1 and 6" << endl;
                break;
        }
    }
    return 0;
}

//void to print the menu
void printMenu() {
    std::cout << "Welcome to the Bug Game!" << std::endl;
    std::cout << "Please select an option from the menu below:" << std::endl;
//    std::cout << "1. Initialise the bug board" << std::endl;
    //display all the bugs in the bug vector
    std::cout << "1. Display all the bugs on the board" << std::endl;
    //find  a bug by id
    std::cout << "2. Find a bug by id" << std::endl;
    //tap the bug board
    std::cout << "3. Tap the bug board" << std::endl;
    //diaply the life history of all the bugs
    std::cout << "4. Display the life history of all the bugs" << std::endl;
    //6. Exit - Write the life history of all bugs to a text file called “bugs_life_history_date_time.out”
    std::cout << "5. Exit" << std::endl;
    //display all cells
    std::cout << "6. Display all cells" << std::endl;
}
