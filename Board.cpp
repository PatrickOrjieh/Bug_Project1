//
// Created by orjie on 28/03/2023.
//

#include "Board.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Bishop.h"
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
#include <thread>
#include <SFML/Graphics.hpp>

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
//new bug type is bishop and it moves in a diagonal direction and direction is 5/6/7/8 and the bishop can only move 1 -6 cells
// This function initializes the board by reading bug data from a file and creating bugs on the board. The file name is passed as an argument to the function.
void Board::initialiseBoard(const std::string &filename) {
    std::ifstream file(filename);
    //The function first opens the file and checks if it is open.
    // If it is not open, an error message is displayed and the function returns
    if (!file.is_open()) {
        std::cout << "Error: File not found" << std::endl;
        return;
    }
    //The function then reads each line from the file and extracts the bug data from each line using a stringstream.
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<std::string> lineData;
        std::string bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr, bishopLengthStr;
        std::getline(lineStream, bugType, ';');
        std::getline(lineStream, bugIdStr, ';');
        std::getline(lineStream, bugXStr, ';');
        std::getline(lineStream, bugYStr, ';');
        std::getline(lineStream, directionStr, ';');
        std::getline(lineStream, sizeStr, ';');
        if (bugType == "H") {
            std::getline(lineStream, hopLengthStr, ';');
        }
        if (bugType == "B") {
            std::getline(lineStream, bishopLengthStr, ';');
        }

        //The function checks if the bug data is valid using the helper function isValidBugData.
        // If the bug data is invalid, an error message is displayed and the function moves on to the next line.
        int numOfInvalid = 1;
        if (!isValidBugData(bugType, bugIdStr, bugXStr, bugYStr, directionStr, sizeStr, hopLengthStr,
                            bishopLengthStr)) {
            std::cout << "Error: Invalid bug data -" << numOfInvalid << std::endl;
            numOfInvalid++;
            continue;
        }

        //f the bug data is valid, the function converts the string values to integers using std::stoi
        // and creates a new bug of the appropriate type using
        // the helper functions createCrawlerBug, createHopperBug, and createBishopBug
        int bugId = std::stoi(bugIdStr);
        int bugX = std::stoi(bugXStr);
        int bugY = std::stoi(bugYStr);
        int direction = std::stoi(directionStr);
        int size = std::stoi(sizeStr);
        int hopLength = 0;
        int bishopLength = 0;
        if (bugType == "B") {
            bishopLength = std::stoi(bishopLengthStr);
            createBishopBug(bugId, bugX, bugY, direction, size, bishopLength);
        } else if (bugType == "H") {
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
                           const std::string &hopLengthStr, const std::string &bishopLengthStr) const {
    int bugId = stoi(bugIdStr);
    int bugX = stoi(bugXStr);
    int bugY = stoi(bugYStr);
    int direction = stoi(directionStr);
    int size = stoi(sizeStr);

    //The function checks if the bug type is "C" (CrawlerBug), "H" (HopperBug), or "B" (BishopBug).
    // If the bug type is not one of these three values, the function returns false.
    if (bugType != "C" && bugType != "H" && bugType != "B") {
        return false;
    }

    //The function checks if the bug ID is a positive integer.
    // If the bug ID is not positive, the function returns false
    if (bugId <= 0) {
        return false;
    }

    //The function checks if the bug's x-coordinate and y-coordinate are within the bounds of the board
    // (0 <= x < BOARD_SIZE and 0 <= y < BOARD_SIZE). If either coordinate is out of bounds,
    // the function returns false.
    if (bugX < 0 || bugX >= BOARD_SIZE) {
        return false;
    }
    if (bugY < 0 || bugY >= BOARD_SIZE) {
        return false;
    }

    //The function checks if the direction is an integer between 1 and 8 (inclusive).
    // If the direction is not within this range, the function returns false.
    if (direction < 1 || direction > 8) {
        return false;
    }

    //The function checks if the size of the bug is a positive integer.
    // If the size is not positive, the function returns false.
    if (size <= 0) {
        return false;
    }

    //If the bug type is "H" (HopperBug), the function checks if the hop length is a positive integer.
    // If the hop length is not positive, the function returns false.
    if (bugType == "H") {
        int hopLength = stoi(hopLengthStr);
        if (hopLength <= 0) {
            return false;
        }
    }

    //If the bug type is "B" (BishopBug), the function checks if the bishop length is a positive integer between 1 and 6 (inclusive).
    // f the bishop length is not within this range, the function returns false.
    if (bugType == "B") {
        int bishopLength = stoi(bishopLengthStr);
        if (bishopLength <= 0 || bishopLength > 6) {
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
    bugs.push_back(hopper);
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
    bugs.push_back(crawler);
}

//method to create a bishop bug
void Board::createBishopBug(int bugId, int bugX, int bugY, int direction, int size, int bishopLength) {
    //    Bishop(int id, std::pair<int, int> position, Direction direction, int size, bool alive, int bishopLength);
    Bishop *bishop = new Bishop(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true,
                                bishopLength);
    //add the first position to the path
    bishop->addPath(std::make_pair(bugX, bugY));
    //using the formula for the cells
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(bishop);
    bugs.push_back(bishop);
}

//check if the bugs are empty
//bool Board::isBugVectorEmpty() const {
//    return bug_vector.empty();
//}

//check if the board is empty
//bool Board::isBoardEmpty() const {
//    return cells->empty();
//}

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

//void Board::tapBoard() {
//    for (int i = 0; i < 100; i++) {
//        //so for each cell, we iterate through the vector of bugs and call the move method for each bug
//        for (auto it = cells[i].rbegin(); it != cells[i].rend(); ++it) {
//            (*it)->move();
//        }
//
//        //so after all bugs have moved, we check if there are any bugs in the same cell
//        //and if tthey are they fight/eat
//        //Implement functionality that will cause bugs that land on the same cell to fight. This will happen
//        //after a round of moves has taken place – invoked by menu option 4. ( Tap ….). The biggest bug in
//        //the cell will eat all other bugs, and will grow by the sum of the sizes of the bugs it eats. The eaten
//        //bugs will be marked as dead (‘alive=false’). We can keep ‘tapping’ the bug board until all the bugs
//        //are dead except one – the Last Bug Standing. Two or more bugs equal in size won’t be able to
//        //overcome each other so the winner is resolved at random.
//        //afte movement call teh fight method
//    }
//    fight();
//}

void Board::tapBoard() {
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            int oldPosition = bug->getPosition().second * BOARD_SIZE + bug->getPosition().first;
            bug->move();
            for (vector<Bug *>::iterator iter = cells[oldPosition].begin(); iter != cells[oldPosition].end(); ++iter) {
                if (*iter == bug) {
                    cells[oldPosition].erase(iter);
                    break;
                }
            }
            cells[bug->getPosition().second * BOARD_SIZE + bug->getPosition().first].push_back(bug);
        }
    }

    for (vector<Bug *> cell: cells) {
        if (cell.size() > 1) {
            Bug *biggestBug = NULL;
            for (Bug *bug: cell) {
                if (bug->isAlive()) {
                    if (biggestBug == NULL || bug->getSize() > biggestBug->getSize()) {
                        biggestBug = bug;
                    }
                }
            }
            if (biggestBug != NULL) {
                for (Bug *bug: cell) {
                    if (bug->isAlive() && bug != biggestBug) {
                        bug->setAlive(false);
                        bug->setEatenBy(biggestBug->getId());
                        cout << bug->getId() << " eaten by " << biggestBug->getId() << endl;
                        biggestBug->setSize(biggestBug->getSize() + bug->getSize());
                    }
                }
            }
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
            } else if (dynamic_cast<Bishop *>(bug)) {
                out << "Bishop";
            }
            out << " Path: ";
            for (auto const &pos: bug->getPath()) {
                out << "(" << pos.first << "," << pos.second << ")";
                if (&pos != &bug->getPath().back()) {
                    out << ",";
                }
            }
            // If the bug is dead, print the bug it was eaten by
            if (!bug->isAlive()) {
                out << " Eaten by " << bug->getPredator();
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

void Board::displayAllCells() const {
    // Loop through all possible positions on the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << "(" << i << "," << j << "): ";
            bool empty = true;
            // Loop through all bugs on the board to check if any are in this position
            for (const auto &cell: cells) {
                for (Bug *bug: cell) {
                    if (bug->getPosition() == std::make_pair(i, j) && bug->isAlive()) {
                        empty = false;
                        if (dynamic_cast<Crawler *>(bug)) {
                            std::cout << "Crawler " << bug->getId() << " ";
                        } else if (dynamic_cast<Hopper *>(bug)) {
                            std::cout << "Hopper " << bug->getId() << " ";
                        } else if (dynamic_cast<Bishop *>(bug)) {
                            std::cout << "Bishop " << bug->getId() << " ";
                        }
                    }
                }
            }
            if (empty) {
                std::cout << "empty" << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
    }
}

//Implement functionality to simulate the tapping of a board every 1 second from the tapBoard method
// until there is only one bug left in the cells and write Bug xxx is the survivor to the screen.
//Display progress on screen as simulation proceeds and write results to file.
void Board::simulate() {
    int numBugs = countAliveBugs();
    int round = 1;
    while (numBugs > 1) {
        cout << "Round " << round << ":" << endl;
        tapBoard();
        displayAllBugs();
        numBugs = countAliveBugs();
        round++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "Bug " << findLastAliveBug()->getId() << " is the survivor." << endl;
    writeLifeHistoryOfAllBugsToFile();
}

int Board::countAliveBugs() const {
    int count = 0;
    for (int i = 0; i < 100; i++) {
        for (Bug *bug: cells[i]) {
            if (bug->isAlive()) {
                count++;
            }
        }
    }
    return count;
}

Bug *Board::findLastAliveBug() const {
    for (int i = 0; i < 100; i++) {
        for (Bug *bug: cells[i]) {
            if (bug->isAlive()) {
                return bug;
            }
        }
    }
    return nullptr;
}

//void Board::drawBoard() {
//    //create a window
//    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bug Game");
//
//    //create a chess board of size 10x10 using a 2D array of squares
//    sf::RectangleShape squares[10][10];
//
//    //set the size of each square
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            squares[i][j].setSize(sf::Vector2f(100, 100));
//            squares[i][j].setPosition(i * 100, j * 100);
//
//            //set the color of each square
//            if ((i + j) % 2 == 0) {
//                squares[i][j].setFillColor(sf::Color::Black);
//            } else {
//                squares[i][j].setFillColor(sf::Color::White);
//            }
//        }
//    }
//
//    //load the bug textures
//    sf::Texture crawlerTexture;
//    if (!crawlerTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/crawler2.png")) {
//        std::cerr << "Failed to load crawler.png" << std::endl;
//        return;
//    }
//
//
//    sf::Texture hopperTexture;
//    if (!hopperTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/hopper2.png")) {
//        std::cerr << "Failed to load hopper.png" << std::endl;
//        return;
//    }
//
//    sf::Texture bishopTexture;
//    if (!bishopTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/bishop2.png")) {
//        std::cerr << "Failed to load bishop.png" << std::endl;
//        return;
//    }
//
//    //create a bug sprite for each bug on the board
//    for (auto &bug: bugs) {
//        sf::Sprite sprite;
//        if (dynamic_cast<Crawler *>(bug)) {
//            sprite.setTexture(crawlerTexture);
//        } else if (dynamic_cast<Hopper *>(bug)) {
//            sprite.setTexture(hopperTexture);
//        } else{
//            sprite.setTexture(bishopTexture);
//        }
//
//        //set the position of the bug sprite on the board
//        sprite.setPosition(bug->getPosition().first * 100, bug->getPosition().second * 100);
//
//        //draw the bug sprite on the board
//        window.draw(sprite);
//    }
//
//    // add a rectangle for menu options
//    sf::RectangleShape menu(sf::Vector2f(500, 1000));
//    menu.setPosition(1000, 0); // set the x-coordinate to 700
//    menu.setFillColor(sf::Color(128, 128, 128, 255)); // set the color to gray
//
//
//
//    // add event loop to handle user input
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//                // handle left mouse button press
//            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//                tapBoard();
//                // check if there is only one bug left
//                if (countAliveBugs() == 1) {
//                    // get the last alive bug
//                    Bug* lastBug = findLastAliveBug();
//                    // display "game over" and the winner's ID
//                    sf::Font font;
//                    if (!font.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/arial.ttf")) {
//                        std::cerr << "Failed to load font" << std::endl;
//                        return;
//                    }
//                    window.clear();
//                    sf::Text text;
//                    text.setFont(font);
//                    text.setString("Game over! Bug " + std::to_string(lastBug->getId()) + " wins!");
//                    text.setCharacterSize(50);
//                    text.setPosition(200, 200);
//                    text.setFillColor(sf::Color::Red);
//                    window.draw(text);
//                    window.display();
//
//                    // wait for 3 seconds before closing the window
//                    sf::sleep(sf::seconds(3));
//                    window.close();
//                }
//            }
//        }
//
//        window.clear();
//
//        for (int i = 0; i < 10; i++) {
//            for (int j = 0; j < 10; j++) {
//                window.draw(squares[i][j]);
//            }
//        }
//
//        window.draw(menu);
//
//        for (auto &bug: bugs) {
//            sf::Sprite sprite;
//            if(bug->isAlive()){
//            if (dynamic_cast<Crawler *>(bug)) {
//                sprite.setTexture(crawlerTexture);
//                sprite.setScale(0.2, 0.2);
////                sprite.setColor(sf::Color(255, 255, 255, 128)); // alpha value of 128 (50% transparency)
//            } else if (dynamic_cast<Hopper *>(bug)) {
//                sprite.setTexture(hopperTexture);
//                sprite.setScale(0.2, 0.2);
//            } else {
//                sprite.setTexture(bishopTexture);
//                sprite.setScale(0.35, 0.35);
//            }
//        }
//
//            sprite.setPosition(bug->getPosition().first * 100, bug->getPosition().second * 100);
//            window.draw(sprite);
//        }
//
//        window.display();
//    }
//}

void Board::drawBoard() {
    //create a window
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bug Game");

    //create a chess board of size 10x10 using a 2D array of squares
    sf::RectangleShape squares[10][10];

    //set the size of each square
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            squares[i][j].setSize(sf::Vector2f(100, 100));
            squares[i][j].setPosition(i * 100, j * 100);

            //set the color of each square
            if ((i + j) % 2 == 0) {
                squares[i][j].setFillColor(sf::Color::White);
                squares[i][j].setOutlineColor(sf::Color::Black);
                squares[i][j].setOutlineThickness(3);
            } else {
                squares[i][j].setFillColor(sf::Color::White);
                squares[i][j].setOutlineColor(sf::Color::Black);
                squares[i][j].setOutlineThickness(3);
            }
        }
    }

    //load the bug textures
    sf::Texture crawlerTexture;
    if (!crawlerTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/crawler2.png")) {
        std::cerr << "Failed to load crawler.png" << std::endl;
        return;
    }


    sf::Texture hopperTexture;
    if (!hopperTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/hopper3.png")) {
        std::cerr << "Failed to load hopper.png" << std::endl;
        return;
    }

    sf::Texture bishopTexture;
    if (!bishopTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/bishop2.png")) {
        std::cerr << "Failed to load bishop.png" << std::endl;
        return;
    }

    //create a bug sprite for each bug on the board
    for (auto &bug: bugs) {
        sf::Sprite sprite;
        if (dynamic_cast<Crawler *>(bug)) {
            sprite.setTexture(crawlerTexture);
        } else if (dynamic_cast<Hopper *>(bug)) {
            sprite.setTexture(hopperTexture);
        } else {
            sprite.setTexture(bishopTexture);
        }

        //set the position of the bug sprite on the board
        sprite.setPosition(bug->getPosition().first * 100, bug->getPosition().second * 100);

        //draw the bug sprite on the board
        window.draw(sprite);
    }

    // add a rectangle for menu options
    sf::RectangleShape menu(sf::Vector2f(500, 1000));
    menu.setPosition(1000, 0); // set the x-coordinate to 700
    menu.setFillColor(sf::Color(128, 128, 128, 255)); // set the color to gray

    // create a font for the timer text
    sf::Font font;
    if (!font.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // create a text object for the timer
//    sf::Text timerText("", font, 50);
//    timerText.setPosition(1050, 100); // set the position in the menu bar
//    timerText.setFillColor(sf::Color::White);

    // set the timer duration in seconds
    int timerDuration = 3;
    sf::Clock clock;
    sf::Time timeElapsed = clock.getElapsedTime();
    sf::Time timeRemaining = sf::seconds(timerDuration) - timeElapsed;
    //for rounds
    int round = 1;
    while (window.isOpen()) {
        // check if there is only one bug left
        if (countAliveBugs() == 1) {
            // get the last alive bug
            Bug *lastBug = findLastAliveBug();
            // display "game over" and the winner's ID
            sf::Text text;
            text.setFont(font);
            text.setString("Game over! Bug " + std::to_string(lastBug->getId()) + " wins!");
            text.setCharacterSize(50);
            text.setPosition(200, 200);
            text.setFillColor(sf::Color::Red);
            window.draw(text);
            window.display();

            // wait for 3 seconds before closing the window
            sf::sleep(sf::seconds(3));
            window.close();
        }
// update time elapsed and time remaining
        timeElapsed = clock.getElapsedTime();
        timeRemaining = sf::seconds(timerDuration) - timeElapsed;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
                // handle left mouse button press
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                tapBoard();
                round++;
                clock.restart();
            }
        }

        window.clear();

// draw the squares on the board
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                window.draw(squares[i][j]);
            }
        }

// draw the menu bar
        window.draw(menu);

// draw the bugs on the board
        for (auto &bug: bugs) {
            sf::Sprite sprite;
            if (bug->isAlive()) {
                if (dynamic_cast<Crawler *>(bug)) {
                    sprite.setTexture(crawlerTexture);
                    if (bug->getSize() >= 85) {
                        sprite.setScale(0.222, 0.222);
                    } else {
                        sprite.setScale(0.08 + 0.00118 * bug->getSize(), 0.08 + 0.00118 * bug->getSize());
                    }
                } else if (dynamic_cast<Hopper *>(bug)) {
                    sprite.setTexture(hopperTexture);
                    if (bug->getSize() >= 213) {
                        sprite.setScale(0.25, 0.25);
                    } else {
                        sprite.setScale(0.08 + 0.00094 * bug->getSize(), 0.08 + 0.00094 * bug->getSize());
                    }
                } else {
                    sprite.setTexture(bishopTexture);
                    if (bug->getSize() >= 118) {
                        sprite.setScale(0.4, 0.4);
                    } else {
                        sprite.setScale(0.12 + 0.00169 * bug->getSize(), 0.12 + 0.00169 * bug->getSize());
                    }
                }


                // Add a text object for the bug size
                sf::Text sizeText;
                sizeText.setFont(font);
                sizeText.setString(std::to_string(bug->getSize()));
                sizeText.setCharacterSize(30);
                sizeText.setPosition(bug->getPosition().first * 100 + 35, bug->getPosition().second * 100 + 55);
                sizeText.setFillColor(sf::Color::Red);
                window.draw(sizeText);

                //so now we want the bugs direction to be the direction they are facing
                //so we need to get the direction of the bug
                //then we need to rotate the sprite to face that direction
                //then we need to draw the sprite
//                switch (bug->getDirection()) {
//                    case Direction::North:
//                        sprite.setRotation(0);
//                        break;
//                    case Direction::South:
//                        sprite.setRotation(180);
//                        break;
//                    case Direction::West:
//                        sprite.setRotation(270);
//                        break;
//                    case Direction::East:
//                        sprite.setRotation(90);
//                        break;
//                    case Direction::NorthWest:
//                        sprite.setRotation(315);
//                        break;
//                    case Direction::NorthEast:
//                        sprite.setRotation(45);
//                        break;
//                    case Direction::SouthWest:
//                        sprite.setRotation(225);
//                        break;
//                    case Direction::SouthEast:
//                        sprite.setRotation(135);
//                        break;
//                }
            }
            sprite.setPosition(bug->getPosition().first * 100, bug->getPosition().second * 100);
            window.draw(sprite);
        }

// draw the timer in the menu bar
        sf::Text timerText;
        timerText.setFont(font);
        timerText.setString("Time Remaining: " + std::to_string((int) timeRemaining.asSeconds()) + " seconds");
        timerText.setCharacterSize(30);
        timerText.setPosition(1020, 20);
        timerText.setFillColor(sf::Color::Black);
        window.draw(timerText);

        //draw the number of rounds in the menu bar
        //create a text object to keep track of rounds
        sf::Text roundsText;
        roundsText.setFont(font);
        roundsText.setString("Round: " + std::to_string((int)round));
        roundsText.setCharacterSize(30);
        roundsText.setPosition(1020, 100); // set the position in the menu bar
        roundsText.setFillColor(sf::Color::Black);
        window.draw(roundsText);



// check if time is up
        if (timeRemaining.asSeconds() <= 0) {
            tapBoard();
            round++;
            clock.restart();
        }

        window.display();
    }
}



//destructors
Board::~Board() {
    //    std::vector <Bug*> cells[99];
    for (int i = 0; i < 100; i++) {
        //using an iterator to delete the bugs
        for (std::vector<Bug *>::iterator it = cells[i].begin(); it != cells[i].end(); ++it) {
            delete *it;
            cout << "deleting bug" << endl;
        }
    }
}