//
// Created by orjie on 28/03/2023.
//

#include "Utils.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace utils {
    int readInt(const std::string& message) {
        int input;
        while (true) {
            std::cout << message;
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::runtime_error("Error: failed to read input");
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

    std::string readString(const std::string& message) {
        std::cout << message;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "Error: failed to read input\n";
            exit(1);
        }
        return line;
    }
}

