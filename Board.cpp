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
#include "SuperBug.h"
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
#include <SFML/Audio.hpp>


using namespace std;

//default constructor
Board::Board() {
}

//method to initialise the board with the bugs from the file
bool Board::initialiseBoard(const std::string &filename) {
    bool done = false;
    std::ifstream file(filename);
    //The function first checks if the file is open. If the file is not open, an error message is displayed and the function returns false.
    if (!file.is_open()) {
        std::cout << "Error: File not found" << std::endl;
        return false;
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
    //The function returns true if the board is initialised successfully.
    if(!isBoardEmpty()){
        done = true;
    }
    return done;
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
    Hopper *hopper = new Hopper(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true,
                                hopLength);

    hopper->setType("Hopper");

    //add the first position to the path
    hopper->addPath(std::make_pair(bugX, bugY));
    //using the formula for the cells
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(hopper);
    bugs.push_back(hopper);
}

//method to create a crawler bug
void Board::createCrawlerBug(int bugId, int bugX, int bugY, int direction, int size) {
    Crawler *crawler = new Crawler(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true);
    //add the first position to the path#

    crawler->setType("Crawler");

    crawler->addPath(std::make_pair(bugX, bugY));
    //using the formula for the cells
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(crawler);
    bugs.push_back(crawler);
}

//method to create a bishop bug
void Board::createBishopBug(int bugId, int bugX, int bugY, int direction, int size, int bishopLength) {
    Bishop *bishop = new Bishop(bugId, std::make_pair(bugX, bugY), static_cast<Direction>(direction), size, true,
                                bishopLength);

    bishop->setType("Bishop");

    //add the first position to the path
    bishop->addPath(std::make_pair(bugX, bugY));
    int position = (bugY * BOARD_SIZE) + bugX;
    cells[position].push_back(bishop);
    bugs.push_back(bishop);
}

//check if the bugs are empty
bool Board::isBoardEmpty() const {
    return bugs.empty();
}

//method to display all the bugs, using the displayBug method from the Crawler and Hopper classes
void Board::displayAllBugs() const {
    for(Bug *bug : bugs) {
        bug->displayBug();
    }
}

//method to find a bug by its id and display it if it exists
void Board::findBugById() const {
    int bugId = utils::readInt("Enter bug id: ");
    //i tried looking for teh most efficient way to do this, but i couldn't find anything
    for(Bug *bug : bugs) {
        if(bug->getId() == bugId) {
            bug->displayBug();
            return;
        }
    }
    std::cout << "Bug " << bugId << " not found" << std::endl;
}

/* The tapBoard method is used to move all the bugs on the board. It first checks if there is only one bug alive.
 * If there is only one bug alive, it prints out the bug's ID and position and returns.
 * Otherwise, it iterates through the bugs vector and moves each bug.
 * Afer moving the bug, it removes the bug from the old position in the cells vector and adds it to the new position.
 */
void Board::tapBoard() {
    if(countAliveBugs() == 1) {
        Bug *lastBug = findLastAliveBug();
        std::cout << "Last bug standing is bug " << lastBug->getId() << " at (" << lastBug->getPosition().first << "," << lastBug->getPosition().second << ")" << std::endl;
        return;
    }
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

    /* The fight method is implemented here where the guys in the same cell fight.
     * The biggest bug wins and eats the smaller bugs.
     * The biggest bug's size is increased by the size of the bugs it eats.
     * The eaten bugs are set to dead and their eatenBy attribute is set to the id of the bug that ate them.
     * */
    for (vector<Bug *> cell: cells) {
        if (cell.size() > 1) {
            Bug *biggestBug = nullptr;
            for (Bug *bug: cell) {
                if (bug->isAlive()) {
                    if (biggestBug == nullptr || bug->getSize() > biggestBug->getSize()) {
                        biggestBug = bug;
                    }
                }
            }
            if (biggestBug != nullptr) {
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

void Board::displayLifeHistoryOfAllBugs(std::ostream &out) const {
    for (Bug *bug: bugs) {
        out << bug->getId() << " ";
        out << bug->getType() << " ";
        out << " Path: ";

        for (const std::pair<int, int> &pos : bug->getPath()) {
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

//method to write the life history of all the bugs to a file
//got an idea from some code i found online from stackoverflow parent path https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// google https://en.cppreference.com/w/cpp/filesystem/current_path
//after i got erros from fs::path(argv[0]).parent_path() << '\n';
//i used chat gpt to ask for help becayse i couldn't find anything online to help resolve the problem
void Board::writeLifeHistoryOfAllBugsToFile() const {
    // Get the directory path to put the file
    //instructions said to put the file in a relative path, so i used the parent path
    std::filesystem::path dir_path = std::filesystem::current_path().parent_path();

    // Get the file name for the output file
    std::string file_name = "bugs_life_history_" + utils::getCurrentDateTime() + ".out";
    // Replace invalid characters with '_'  because Windows doesn't allow ':' in file names and i kept getting errors
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
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << "(" << i << "," << j << "): ";
            bool empty = true;
            for (Bug *bug: bugs) {
                if (bug->getPosition() == std::make_pair(i, j) && bug->isAlive()) {
                    empty = false;
                    std::cout << bug->getType() << " " << bug->getId() << " ";
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
    while (numBugs > 1) {
        cout << "Round " << rounds << ":" << endl;
        tapBoard();
        displayAllBugs();
        numBugs = countAliveBugs();
        rounds++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "Bug " << findLastAliveBug()->getId() << " is the survivor." << endl;
    writeLifeHistoryOfAllBugsToFile();
}

//an extra method to count the number of bugs that are alive
int Board::countAliveBugs() const {
    int count = 0;
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            count++;
        }
    }
    return count;
}

//an extra method to find the last alive bug
Bug *Board::findLastAliveBug() const {
    for (Bug *bug: bugs) {
        if (bug->isAlive()) {
            return bug;
        }
    }
    return nullptr;
}

//an extra method to check if a cell is empty in the graphics to make sure bugs don't overlap
bool Board::isCellEmpty(int x, int y) {
    for (Bug *bug: bugs) {
        if (bug->getPosition().first == x && bug->getPosition().second == y && bug->isAlive()) {
            return false;
        }
    }
    return true;
}

//got help from https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php, https://www.youtube.com/watch?v=_RLFI1D99Ow&t=312s&ab_channel=Zenva
void Board::drawBoard() {
    //create a window
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Bug Game");

    sf::RectangleShape squares[10][10];

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

    sf::Texture superBugTexture;
    if (!superBugTexture.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/super.png")) {
        std::cerr << "Failed to load superbug.png" << std::endl;
        return;
    }

    //check if the superbug is already on the board
    bool superBugOnBoard = false;
    for (Bug *bug: bugs) {
        if(bug->getType() == "SuperBug"){
            superBugOnBoard = true;
        }
    }

    // Add the SuperBug to the board
    if(!superBugOnBoard) {
        SuperBug *superBug = new SuperBug(001, make_pair(7, 7), static_cast<Direction>(1), 20, true);
        superBug->setType("SuperBug");
        bugs.push_back(superBug);
    }

    SuperBug *superBug;
    for (Bug *bug: bugs) {
        if(bug->getType() == "SuperBug"){
            superBug = dynamic_cast<SuperBug *>(bug);
        }
    }

    // add a rectangle for menu options
    sf::RectangleShape menu(sf::Vector2f(500, 1000));
    menu.setPosition(1000, 0); // set the x-coordinate to 700
    menu.setFillColor(sf::Color(128, 128, 128, 255)); // set the color to gray

    // create a font for all texts
    sf::Font font;
    if (!font.loadFromFile("C:/Users/orjie/CLionProjects/bug_project/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    // set the timer duration for 3 seconds
    int timerDuration = 3;
    sf::Clock clock;
    sf::Time timeElapsed = clock.getElapsedTime();
    sf::Time timeRemaining = sf::seconds(timerDuration) - timeElapsed;

    //create a pomiter for the selected bug which will be used to display the bug details and also
    //to move the selected bug IF it is the SuperBug
    Bug *selectedBug = nullptr;

    // create a text object to display the bug details in the menu bar
    sf::Text bugDetails;
    bugDetails.setFont(font);
    bugDetails.setCharacterSize(30);
    bugDetails.setPosition(1020, 200); // set the position in the menu bar
    bugDetails.setFillColor(sf::Color::Black);

    bool isGameOver = false;

    while (window.isOpen()) {
        if(!isGameOver) {
            timeElapsed = clock.getElapsedTime();
            timeRemaining = sf::seconds(timerDuration) - timeElapsed;
        }

        // check if time is up
        if (!isGameOver && timeRemaining.asSeconds() <= 0) {
            tapBoard();
            rounds++;
            clock.restart();
        }
        // check if there is only one bug left
        if (countAliveBugs() == 1) {
            // get the last alive bug
            Bug *lastBug = findLastAliveBug();

            isGameOver = true;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
                // handle left mouse button press event which will be used to tap the board
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                tapBoard();
                rounds++;
                clock.restart();
            }

            //to add an event when the user right clicks the board and a bug is in that position it
            //displays the details of that bug in the menu bar  or deselects the bug if it is already selected
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x;
                int y = mousePos.y;
                int xSquare = x / 100;
                int ySquare = y / 100;
                for (Bug *bug: bugs) {
                    if (bug->isAlive()) {
                        if (bug->getPosition().first == xSquare && bug->getPosition().second == ySquare) {
                            if (selectedBug == bug) {
                                selectedBug = nullptr; // deselect the bug
                            } else {
                                selectedBug = bug; // select the bug
                            }
                        }
                    }
                }
            }

            // Move the SuperBug based on user input
            //also added check to make sure that the superbug does not move out of the board
            //and also does not move to a cell that is occupied by another bug
            if (selectedBug == superBug) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if (superBug->getPosition().first > 0) { // check if not at left edge
                        if (isCellEmpty(superBug->getPosition().first - 1, superBug->getPosition().second)) {
                            superBug->move();
                            superBug->setDirection(West);
                        }
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (superBug->getPosition().first < 9) { // check if not at right edge
                        if (isCellEmpty(superBug->getPosition().first + 1, superBug->getPosition().second)) {
                            superBug->move();
                            superBug->setDirection(East);
                        }
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (superBug->getPosition().second > 0) { // check if not at top edge
                        if (isCellEmpty(superBug->getPosition().first, superBug->getPosition().second - 1)) {
                            superBug->move();
                            superBug->setDirection(North);
                        }
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (superBug->getPosition().second < 9) { // check if not at bottom edge
                        if (isCellEmpty(superBug->getPosition().first, superBug->getPosition().second + 1)) {
                            superBug->move();
                            superBug->setDirection(South);
                        }
                    }
                }
            }
        }

        window.clear();

        //draw the board
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                squares[i][j].setSize(sf::Vector2f(100, 100));
                squares[i][j].setPosition(i * 100, j * 100);

                squares[i][j].setFillColor(sf::Color::White);
                squares[i][j].setOutlineColor(sf::Color::Black);
                squares[i][j].setOutlineThickness(3);
                // add this if-statement to check if the current square is the selected one
                if (selectedBug != nullptr && i == selectedBug->getPosition().first &&
                    j == selectedBug->getPosition().second) {
                    if (selectedBug->isAlive()) {
                        squares[i][j].setFillColor(sf::Color::Green);
                    } else {
                        squares[i][j].setFillColor(sf::Color::White);
                    }
                }
                window.draw(squares[i][j]);
            }
        }

// draw the menu bar
        window.draw(menu);

/* The following code is used to draw the bugs on the board.
 * It loops through the bugs vector and draws the bugs that are alive.
 * It also checks the type of the bug and draws the appropriate texture.
 * and also rotates the bug based on its direction
 * and also scales the bug based on its size
 * */
        for (Bug *bug: bugs) {
            sf::Sprite sprite;
            float offsetX = 0;
            float offsetY = 0;
            if (bug->isAlive()) {
                if (bug->getType() == "Crawler") {
                    sprite.setTexture(crawlerTexture);
                    rotate(bug, sprite, offsetX, offsetY);
                    if (bug->getSize() >= 85) {
                        sprite.setScale(0.222, 0.222);
                        offsetX *= 0.222;
                        offsetY *= 0.222;
                    } else {
                        sprite.setScale(0.08 + 0.00118 * bug->getSize(), 0.08 + 0.00118 * bug->getSize());
                        offsetX *= 0.08 + 0.00118 * bug->getSize();
                        offsetY *= 0.08 + 0.00118 * bug->getSize();
                    }
                } else if (bug->getType() == "Hopper") {
                    sprite.setTexture(hopperTexture);
                    rotate(bug, sprite, offsetX, offsetY);
                    if (bug->getSize() >= 213) {
                        sprite.setScale(0.25, 0.25);
                        offsetX *= 0.25;
                        offsetY *= 0.25;
                    } else {
                        sprite.setScale(0.08 + 0.00094 * bug->getSize(), 0.08 + 0.00094 * bug->getSize());
                        offsetX *= 0.08 + 0.00094 * bug->getSize();
                        offsetY *= 0.08 + 0.00094 * bug->getSize();
                    }
                } else if (bug->getType() == "Bishop") {
                    sprite.setTexture(bishopTexture);
                    rotate(bug, sprite, offsetX, offsetY);
                    if (bug->getSize() >= 118) {
                        sprite.setScale(0.4, 0.4);
                        offsetX *= 0.4;
                        offsetY *= 0.4;
                    } else {
                        sprite.setScale(0.12 + 0.00169 * bug->getSize(), 0.12 + 0.00169 * bug->getSize());
                        offsetX *= 0.08 + 0.00094 * bug->getSize();
                        offsetY *= 0.08 + 0.00094 * bug->getSize();
                    }
                } else {
                    sprite.setTexture(superBugTexture);
                    rotate(bug, sprite, offsetX, offsetY);
                    if (bug->getSize() >= 118) {
                        sprite.setScale(0.4, 0.4);
                        offsetX *= 0.4;
                        offsetY *= 0.4;
                    } else {
                        sprite.setScale(0.12 + 0.00169 * bug->getSize(), 0.12 + 0.00169 * bug->getSize());
                        offsetX *= 0.08 + 0.00094 * bug->getSize();
                        offsetY *= 0.08 + 0.00094 * bug->getSize();
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
            }

            sprite.setPosition((bug->getPosition().first * 100) + offsetX, (bug->getPosition().second * 100) + offsetY);
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
        roundsText.setString("Round: " + std::to_string((int) rounds));
        roundsText.setCharacterSize(30);
        roundsText.setPosition(1020, 100); // set the position in the menu bar
        roundsText.setFillColor(sf::Color::Black);
        window.draw(roundsText);


        //at the bottom of the menu bar, draw the @Creator : ORJIEH PATRICK
        sf::Text creatorText;
        creatorText.setFont(font);
        creatorText.setString("@Creator: PATRICK ORJIEH");
        creatorText.setCharacterSize(30);
        creatorText.setPosition(1020, 950); // set the position in the menu bar
        creatorText.setFillColor(sf::Color::Black);
        window.draw(creatorText);

        //add the details of the selected bug to the bug details
        // set the bug details text
        if (selectedBug != nullptr && selectedBug->isAlive()) {
            std::string details = "Type: ";
            details += selectedBug->getType() + "\n";
            details += "ID: " + std::to_string(selectedBug->getId()) + "\n";
            details += "Size: " + std::to_string(selectedBug->getSize()) + "\n";
            details += "Direction: " + std::to_string(selectedBug->getDirection()) + "\n";
            details += "Position: (" + std::to_string(selectedBug->getPosition().first) + ", " +
                       std::to_string(selectedBug->getPosition().second) + ")\n";
            bugDetails.setString(details);
            window.draw(bugDetails);
        } else if (selectedBug != nullptr && !selectedBug->isAlive()) {
            bugDetails.setString("Bug (" + std::to_string(selectedBug->getId()) + ") is dead");
            window.draw(bugDetails);
        } else {
            bugDetails.setString("No bug selected");
            window.draw(bugDetails);
        }

        // draw the bug details in the menu bar
        window.draw(bugDetails);

        if (selectedBug != nullptr && selectedBug->isAlive()) {
            //get the bug type
            sf::Sprite sprite;
            if (selectedBug->getType() == "Crawler") {
                sprite.setTexture(crawlerTexture);
                sprite.setScale(0.7, 0.7);
            } else if (selectedBug->getType() == "Hopper") {
                sprite.setTexture(hopperTexture);
                sprite.setScale(0.7, 0.7);
            } else if (selectedBug->getType() == "Bishop") {
                sprite.setTexture(bishopTexture);
                sprite.setScale(1, 1);
            } else {
                sprite.setTexture(superBugTexture);
                sprite.setScale(1, 1);
            }
            sprite.setPosition(1120, 500);
            window.draw(sprite);
        }

        // add a rectangle for the end screen
        sf::RectangleShape end(sf::Vector2f(1000, 1500));
        end.setPosition(0, 0); // set the x-coordinate to 700
        end.setFillColor(sf::Color(128, 128, 128, 255)); // set the color to gray

        Bug *lastBug = findLastAliveBug();
        //draw the picture of the winner
        sf::Sprite winnerSprite;
        if (lastBug->getType() == "Crawler") {
            winnerSprite.setTexture(crawlerTexture);
        } else if (lastBug->getType() == "Hopper") {
            winnerSprite.setTexture(hopperTexture);
        } else if (lastBug->getType() == "Bishop") {
            winnerSprite.setTexture(bishopTexture);
        }else{
            winnerSprite.setTexture(superBugTexture);
        }

        if(!isGameOver){
            window.display();
        }
        else{
            // display "game over" and the winner's ID
            sf::Text text;
            text.setFont(font);
            text.setString("Game over!");
            text.setCharacterSize(50);
            text.setPosition(200, 200);
            text.setFillColor(sf::Color::Red);

            window.draw(text);
            // wait for 5 seconds
            if(clock.getElapsedTime().asSeconds() > 5) {
                window.clear();
                //draw the end screen
                window.draw(end);

                //set the position of the bug sprite on the board
                winnerSprite.setPosition(100, 100);

                //set the scale of the bug sprite
                winnerSprite.setScale(2, 2);

                //draw the bug sprite on the board
                window.draw(winnerSprite);

                string winner = "Bug " + std::to_string(lastBug->getId()) + " wins!\n";
                winner += "Killed Bugs: ";
                for (Bug *bug: bugs) {
                    if (bug->getPredator() == lastBug->getId()) {
                        winner += std::to_string(bug->getId()) + ", ";
                    }
                }
                winner += "\nSize: " + std::to_string(lastBug->getSize());
                winner += "\nCurrent Position: " + std::to_string(lastBug->getPosition().first) + ", " +
                          std::to_string(lastBug->getPosition().second);

                winner += "\nDirection: " + std::to_string(lastBug->getDirection());

                winner += "\nNumber of Rounds: " + std::to_string(rounds);

                //draw the text
                sf::Text winnerText;
                winnerText.setFont(font);
                winnerText.setString(winner);
                winnerText.setCharacterSize(50);
                winnerText.setPosition(700, 200);

                window.draw(winnerText);
            }
            window.display();
        }
    }
}

/* Rotate the bug sprite based on the direction of the bug
 * */
void Board::rotate(Bug *const &bug, sf::Sprite &sprite, float &offsetX, float &offsetY) const {
    offsetX = sprite.getLocalBounds().width / 2;
    offsetY = sprite.getLocalBounds().height / 2;
    sprite.setOrigin(offsetX, offsetY);
    switch (bug->getDirection()) {
        case North:
            sprite.setRotation(0);
            break;
        case South:
            sprite.setRotation(180);
            break;
        case West:
            sprite.setRotation(270);
            break;
        case East:
            sprite.setRotation(90);
            break;
        case NorthWest:
            sprite.setRotation(315);
            break;
        case NorthEast:
            sprite.setRotation(45);
            break;
        case SouthWest:
            sprite.setRotation(225);
            break;
        case SouthEast:
            sprite.setRotation(135);
            break;
    }
}

//destructors
Board::~Board() {
    for(Bug *bug: bugs){
        delete bug;
    }
}