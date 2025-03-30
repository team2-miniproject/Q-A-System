#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
private:
    std::string userID, name, passwordHash;
    int rating;

public:
    User(std::string id, std::string n, std::string hash);

    std::string getID() const { return userID; }
    std::string getName() const { return name; }
    std::string getPasswordHash() const { return passwordHash; }
    int getRating() const { return rating; }  // ✅ Added this function

    bool authenticate(std::string hash);
    void updateRating(int change);
    void display();
};

#endif 
