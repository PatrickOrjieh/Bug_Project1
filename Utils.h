//
// Created by orjie on 28/03/2023.
//

#ifndef BUG_PROJECT1_UTILS_H
#define BUG_PROJECT1_UTILS_H

#include <string>


namespace utils {
    // Reads an integer from the user.
    int readInt(const std::string& message);
    // Reads a string from the user.
    std::string readString(const std::string& message);
    //get currentDatetIME
    std::string getCurrentDateTime();
}


#endif //BUG_PROJECT1_UTILS_H
