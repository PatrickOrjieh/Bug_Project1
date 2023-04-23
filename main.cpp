#include <iostream>
#include <string>
#include "Board.h"
#include "Utils.h"
using namespace std;

//void to print the menu
void printMenu();

int main() {
    Board board;
    while(true){
        string filename = utils::readString("Please enter the name of the file to read the bug data from: ");
        bool isFileValid = board.initialiseBoard(filename);
        if(isFileValid){
            break;
        }
        cout << "File is Invalid or No Bug was created from the File" << endl;
    }

    while(true){
        printMenu();
        int choice = utils::readInt("Please enter your choice: ");
        switch(choice){
            case 1:
                cout << "Displaying all the bugs on the board" << endl;
                board.displayAllBugs();
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
            case 7:
                cout << "Running simulation" << endl;
                board.simulate();
                break;
            case 8:
                board.drawBoard();
                break;
            default:
                cout << "Invalid choice, please enter a number between 1 and 8" << endl;
                break;
        }
    }
    return 0;
}

//void to print the menu
void printMenu() {
    std::cout << "Welcome to the Bug Game!" << std::endl;
    std::cout << "Please select an option from the menu below:" << std::endl;
    std::cout << "1. Display all the bugs on the board" << std::endl;
    std::cout << "2. Find a bug by id" << std::endl;
    std::cout << "3. Tap the bug board" << std::endl;
    std::cout << "4. Display the life history of all the bugs" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "6. Display all cells" << std::endl;
    std::cout << "7. Run simulation Without Graphics" << std::endl;
    std::cout << "8. Play board GUI" << std::endl;
}
