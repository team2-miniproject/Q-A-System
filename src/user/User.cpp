#include "User.h"

User::User(std::string id, std::string n, std::string hash) : userID(id), name(n), passwordHash(hash), rating(0) {}

bool User::authenticate(std::string hash) {
    return passwordHash == hash;
}

void User::updateRating(int change) {
    rating += change;
}

void User::display() {
    std::cout << "User: " << name << " | Rating: " << rating << std::endl;
}
