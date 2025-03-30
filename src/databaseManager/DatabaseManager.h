
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include "../question/Question.h"
#include "../user/User.h"  // Ensure correct relative path
#include "../utility/Utility.h"
#include <vector>
#include <fstream>

class DatabaseManager {
public:
    void saveUser(const User& user);
    std::vector<User> loadUsers();
    void saveQuestion(const Question& question);
    std::vector<Question> loadQuestions();
    void removeQuestionFromIndex(const std::string& questionID);
};

#endif