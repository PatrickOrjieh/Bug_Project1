#include <iostream>
using namespace std;

//void to print the menu
void printMenu();

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

//void to print the menu
void printMenu() {
    std::cout << "Welcome to the Bug Game!" << std::endl;
    std::cout << "Please select an option from the menu below:" << std::endl;
    std::cout << "1. Initialise the bug board" << std::endl;
    //display all the bugs in the bug vector
    std::cout << "2. Display all the bugs on the board" << std::endl;
    //find  a bug by id
    std::cout << "3. Find a bug by id" << std::endl;
    //tap the bug board
    std::cout << "4. Tap the bug board" << std::endl;
    //diaply the life history of all the bugs
    std::cout << "5. Display the life history of all the bugs" << std::endl;
    //6. Exit - Write the life history of all bugs to a text file called “bugs_life_history_date_time.out”
    std::cout << "6. Exit" << std::endl;
    //display all cells
    std::cout << "7. Display all cells" << std::endl;
}