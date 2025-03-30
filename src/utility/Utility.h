#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sstream>
#include <vector>

class Utility {
public:
    static std::vector<std::string> split(const std::string& str, char delimiter);
};

#endif
