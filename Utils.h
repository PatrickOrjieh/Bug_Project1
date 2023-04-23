//
// Created by orjie on 28/03/2023.
//

#ifndef BUG_PROJECT_UTILS_H
#define BUG_PROJECT_UTILS_H

#include <string>

//i mader this class to store all the functions that i need to use in the project
//basically, it is a class that contains all helper functions

namespace utils {
    // Reads an integer from the user.
    int readInt(const std::string& message);
    // Reads a string from the user.
    std::string readString(const std::string& message);
    //get currentDatetIME
    std::string getCurrentDateTime();
}


#endif //BUG_PROJECT_UTILS_H
