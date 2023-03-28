#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

//void to print the menu
void printMenu();
//to validate user int input
int readInt(const string& message);
//to validate user string input
string readString(const string& message);

int main() {
    Board board;
    string filename = readString("Please enter the name of the file to read the bug data from: ");
    board.initialiseBoard(filename);
    return 0;
}

//to validate user int input
int readInt(const std::string& message) {
    int input;
    while (true) {
        std::cout << message;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "Error: failed to read input\n";
            exit(1);
        }
        try {
            input = std::stoi(line);
            break;
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid input, please enter an integer.\n";
        } catch (std::out_of_range& e) {
            std::cout << "Input out of range, please enter an integer.\n";
        }
    }
    return input;
}

//to validate user string input
string readString(const std::string& message) {
    cout << message;
    string line;
    if (!getline(cin, line)) {
        cerr << "Error: failed to read input\n";
        exit(1);
    }
    return line;
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