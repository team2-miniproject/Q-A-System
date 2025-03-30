#ifndef QUESTION_H
#define QUESTION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include "../user/User.h"

class Question {
private:
    std::string questionID, text;
    User author; 

    void updateIndex();  // 
public:
    Question(std::string id, std::string txt, User u);
    void display();

    std::string toString() {
        return "UserID: " + author.getID() + ", Name: " + author.getName() + 
               ", Rating: " + std::to_string(author.getRating());
    }
    std::string getText() const { return text; }
    std::string getID() const { return questionID; } //
    User getAuthor() const { return author; } //
    std::vector<std::string> tokenizeText() const; //
};

#endif  // QUESTION_H
