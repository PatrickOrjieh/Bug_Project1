//
// Created by orjie on 28/03/2023.
//

#include "Utils.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <sstream>
#include <iomanip>

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

    //from https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
    //and https://stackoverflow.com/questions/16357999/current-date-and-time-as-string
    //and https://en.cppreference.com/w/cpp/chrono/c/time
    std::string getCurrentDateTime() {
        // Get the current time
        std::time_t now = std::time(nullptr);
        // Convert it to a struct tm
        std::tm time_info = *std::localtime(&now);
        // Create a string stream for formatting the output
        std::ostringstream oss;
        // Format the output as "YYYY-MM-DD HH:MM:SS"
        oss << std::put_time(&time_info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}

