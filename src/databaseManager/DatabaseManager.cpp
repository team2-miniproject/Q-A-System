#include "DatabaseManager.h"

void DatabaseManager::saveUser(const User& user) {
    std::ofstream file("data/users.txt", std::ios::app);
    file << user.getID() << "," << user.getName() << "," << user.getPasswordHash() << "\n";
    file.close();
}

std::vector<User> DatabaseManager::loadUsers() {
    std::vector<User> users;
    std::ifstream file("data/users.txt");
    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> data = Utility::split(line, ',');
        if (data.size() == 3) {
            users.emplace_back(data[0], data[1], data[2]);
        }
    }
    file.close();
    return users;
}

void DatabaseManager::saveQuestion(const Question& question) {
    std::ofstream file("data/questions.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening questions file!\n";
        return;
    }
    file << question.getID() << "|" << question.getText() << "\n";
    file.close();
}

std::vector<Question> DatabaseManager::loadQuestions() {
    std::vector<Question> questions;
    std::ifstream file("data/questions.txt");
    std::string line;

    if (!file) {
        std::cerr << "Error opening questions file!\n";
        return {};
    }

    while (getline(file, line)) {
        size_t pos = line.find("|");
        if (pos != std::string::npos) {
            std::string id = line.substr(0, pos);
            std::string text = line.substr(pos + 1);
            questions.emplace_back(id, text, User("dummy", "Unknown", "pass"));
        }
    }
    file.close();
    return questions;
}

// Remove a question from index
void DatabaseManager::removeQuestionFromIndex(const std::string& questionID) {
    std::ifstream inFile("data/index.txt");
    std::ofstream outFile("data/temp.txt");

    if (!inFile || !outFile) {
        std::cerr << "Error processing index file!\n";
        return;
    }

    std::string word, id;
    while (inFile >> word >> id) {
        if (id != questionID) {
            outFile << word << " " << id << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove("data/index.txt");
    rename("data/temp.txt", "data/index.txt");
}