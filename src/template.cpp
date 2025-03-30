#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include "sentimentAnalyzer/SentimentAnalyzer.h"


struct Question {
    std::string id, user, text;
};

struct Answer {
    std::string answerID, questionID, user, text, sentiment;
};

std::vector<Question> questions;
std::vector<Answer> answers;
std::map<std::string, int> votes;
std::map<std::string, std::set<std::string>> userVotes;
std::map<std::string, std::set<std::string>> keywordIndex; // Changed from 'index' to 'keywordIndex'

void saveIndex() {
    std::ofstream file("data/index.txt");
    for (const auto& [word, ids] : keywordIndex) {
        file << word;
        for (const auto& id : ids) {
            file << " " << id;
        }
        file << "\n";
    }
}

void loadIndex() {
    std::ifstream file("data/index.txt");
    std::string line, word, id;
    keywordIndex.clear();
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> word;
        while (iss >> id) {
            keywordIndex[word].insert(id);
        }
    }
}

void loadQuestions() {
    std::ifstream file("data/questions.txt");
    std::string id, user, text, line;
    questions.clear();
    keywordIndex.clear(); // Clear the index when reloading
    
    while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> id >> user;
        std::getline(iss, text);
        questions.push_back({id, user, text});
        
        // Index the question text
        loadIndex();
    }
}

void loadAnswers() {
    std::ifstream file("data/answers.txt");
    std::string answerID, questionID, user, text, line;
    answers.clear();

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        if (!(iss >> answerID >> questionID >> user)) {
            std::cerr << "Error: Corrupt line in answers.txt: " << line << "\n";
            continue;
        }

        // Read the rest of the line which contains text and sentiment
        std::getline(iss, text);
        
        // Extract sentiment if it exists (format: text [sentiment])
        std::string sentiment = "Neutral"; // Default
        size_t sentimentStart = text.rfind(" [");
        if (sentimentStart != std::string::npos && text.back() == ']') {
            sentiment = text.substr(sentimentStart + 2, text.size() - sentimentStart - 3);
            text = text.substr(0, sentimentStart);
        }
        
        answers.push_back({answerID, questionID, user, text, sentiment});
    }
}

void loadVotes() {
    std::ifstream file("data/votes.txt");
    std::string answerID, user;
    int vote;
    votes.clear();
    userVotes.clear();
    while (file >> answerID >> user >> vote) {
        votes[answerID] += vote;
        userVotes[answerID].insert(user);
    }
}

void saveQuestion(const std::string &question, const std::string &username) {
    loadQuestions();
    int nextID = questions.empty() ? 1 : std::stoi(questions.back().id) + 1;
    std::ofstream file("data/questions.txt", std::ios::app);
    if (file.is_open()) {
        file << nextID << " " << username << " " << question << "\n";
        file.close();
        questions.push_back({std::to_string(nextID), username, question});
        
        std::istringstream words(question);
        std::string word;
        while (words >> word) {
            keywordIndex[word].insert(std::to_string(nextID));
        }
        
        saveIndex(); 
        
        std::cout << "Question posted successfully with ID: " << nextID << "\n";
    }
}

void saveQuestions() {
    std::ofstream file("data/questions.txt");
    for (const auto& q : questions) {
        file << q.id << " " << q.user << " " << q.text << "\n";
    }
}

void saveAnswers() {
    std::ofstream file("data/answers.txt");
    for (const auto& a : answers) {
        file << a.answerID << " " << a.questionID << " " << a.user << " " << a.text;
        if (!a.sentiment.empty()) {
            file << " [" << a.sentiment << "]";
        }
        file << "\n";
    }
}

void askQuestion(const std::string &username) {
    std::string question;
    std::cin.ignore();
    std::cout << "Enter your question: ";
    std::getline(std::cin, question);
    saveQuestion(question, username);
}

void voteAnswer(const std::string &answerID, const std::string &username) {
    if (userVotes[answerID].count(username) > 0) {
        return;
    }

    std::cout << "Do you want to vote on this Answer? (y/n): ";
    char votechoice;
    std::cin >> votechoice;
    if (votechoice == 'y' || votechoice == 'Y') {
        int vote;
        while (true) {
            std::cout << "Vote on Answer ID " << answerID << " (1 for Upvote, -1 for Downvote): ";
            std::cin >> vote;
            if (vote == 1 || vote == -1) break;
            std::cout << "Invalid input. Please enter 1 (Upvote) or -1 (Downvote).\n";
        }

        std::ofstream file("data/votes.txt", std::ios::app);
        if (file.is_open()) {
            file << answerID << " " << username << " " << vote << "\n";
            file.close();
            votes[answerID] += vote;
            userVotes[answerID].insert(username);
            std::cout << "Vote recorded successfully!\n";
        }
    } else if (votechoice == 'n' || votechoice == 'N') {
        std::cout << "ok...\n";
        return;
    }
}

void answerQuestion(const std::string &username) {
    loadQuestions();
    loadAnswers();
    loadVotes();

    char answerChoice;

    if (questions.empty()) {
        std::cout << "No questions available.\n";
        return;
    }

    std::cout << "\nAvailable Questions:\n";
    for (const auto &q : questions) {
        std::cout << q.id << ". " << q.text << " (Asked by: " << q.user << ")\n";
    }

    std::string qID;
    std::cout << "Enter the Question ID to view answers or answer it: ";
    std::cin >> qID;
    std::cin.ignore();

    bool found = false;
    for (const auto &q : questions) {
        if (q.id == qID) {
            found = true;
            std::cout << "\nAnswers for Question: " << q.text << "\n";
            bool hasAnswers = false;
            for (const auto &a : answers) {
                if (a.questionID == qID) {
                    int voteCount = votes[a.answerID];
                    std::cout << " by " << a.user << " [" << voteCount << " votes, " << a.sentiment << " sentiment]: " << a.text;
                    
                    if (userVotes[a.answerID].count(username) > 0) {
                        std::cout << " (You voted: " << (votes[a.answerID] > 0 ? "1" : "-1") << ")";
                    } else {
                        std::cout << "\n";
                        voteAnswer(a.answerID, username);
                    }
                    std::cout << "\n";
                    hasAnswers = true;
                }
            }
            if (!hasAnswers) std::cout << "No answers yet.\n";
            
            std::cout << "\nDo you want to answer this question? (y/n): ";
            std::cin >> answerChoice;
            std::cin.ignore();

            if (answerChoice == 'n' || answerChoice == 'N') {
                std::cout << "Returning to menu...\n";
                return;
            } else if (answerChoice != 'y' && answerChoice != 'Y') {
                std::cout << "Invalid choice. try again\n";
                return;
            }

            std::string answer;
            std::cout << "\nEnter your answer: ";
            std::getline(std::cin, answer);

            int nextAID;
            try {
                nextAID = answers.empty() ? 1 : std::stoi(answers.back().answerID) + 1;
            } catch (const std::exception &e) {
                std::cerr << "Error: Invalid Answer ID format in answers.txt\n";
                nextAID = 1;
            }

            // Perform sentiment analysis
            std::string sentiment = SentimentAnalyzer::analyzeSentiment(answer);
            
            std::ofstream file("data/answers.txt", std::ios::app);
            if (file.is_open()) {
                file << nextAID << " " << qID << " " << username << " " << answer << " [" << sentiment << "]\n";
                file.close();
                answers.push_back({std::to_string(nextAID), qID, username, answer, sentiment});
                std::cout << "Answer posted successfully with Answer ID: " << nextAID 
                          << " (Sentiment: " << sentiment << ")\n";
            }
            break;
        }
    }

    if (!found) std::cout << "Invalid Question ID. Try again.\n";
}
void deleteQuestion(const std::string& username) {
    loadQuestions();
    loadAnswers();
    
    std::cout << "\nAvailable Questions:\n";
    for (const auto &q : questions) {
        std::cout << q.id << ". " << q.text << " (Asked by: " << q.user << ")\n";
    }

    std::string qID;
    std::cout << "Enter Question ID to delete: ";
    std::cin >> qID;
    
    auto it = std::remove_if(questions.begin(), questions.end(), [&](const Question& q) {
        return q.id == qID && q.user == username;
    });
    
    if (it != questions.end()) {
        // Before deleting, remove this question ID from the keyword index
        for (auto& [keyword, questionIds] : keywordIndex) {
            questionIds.erase(qID);
        }
        
        // Remove any keywords that now have empty sets
        std::vector<std::string> emptyKeywords;
        for (const auto& [keyword, questionIds] : keywordIndex) {
            if (questionIds.empty()) {
                emptyKeywords.push_back(keyword);
            }
        }
        
        for (const auto& keyword : emptyKeywords) {
            keywordIndex.erase(keyword);
        }
        
        // Save the updated index
        saveIndex();
        
        // Remove the question
        questions.erase(it);
        
        // Remove associated answers
        answers.erase(std::remove_if(answers.begin(), answers.end(), [&](const Answer& a) {
            return a.questionID == qID;
        }), answers.end());
        
        // Save questions and answers
        saveQuestions();
        saveAnswers();
        
        std::cout << "Question deleted successfully.\n";
    } else {
        std::cout << "You can only delete your own questions.\n";
    }
}

void deleteAnswer(const std::string& username) {
    loadAnswers();
    
    if (answers.empty()) {
        std::cout << "No answers available.\n";
        return;
    }

    std::cout << "\nAvailable Answers:\n";
    for (const auto &a : answers) {
        std::cout << a.answerID << ". " << a.text << " (Answered by: " << a.user << ")\n";
    }

    std::string aID;
    std::cout << "Enter Answer ID to delete: ";
    std::cin >> aID;

    auto it = std::remove_if(answers.begin(), answers.end(), [&](const Answer& a) {
        return a.answerID == aID && a.user == username;
    });
    
    if (it != answers.end()) {
        answers.erase(it, answers.end());
        saveAnswers();
        std::cout << "Answer deleted successfully.\n";
    } else {
        std::cout << "You can only delete your own answers.\n";
    }
}

void deleteContent(const std::string& username) {
    int choice;
    std::cout << "1. Delete Question\n2. Delete Answer\nChoice: ";
    std::cin >> choice;
    
    if (choice == 1) deleteQuestion(username);
    else if (choice == 2) deleteAnswer(username);
    else std::cout << "Invalid choice.\n";
}

void searchQuestions() {
    loadQuestions();
    std::string keyword;
    std::cout << "Enter a word to search in questions: ";
    std::cin >> keyword;
    
    // Convert to lowercase for case-insensitive search
    std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    
    if (keywordIndex.find(keyword) == keywordIndex.end()) {
        std::cout << "No questions found containing the word '" << keyword << "'.\n";
        return;
    }

    std::cout << "Questions containing '" << keyword << "':\n";
    for (const auto& qID : keywordIndex[keyword]) {
        for (const auto& q : questions) {
            if (q.id == qID) {
                std::cout << q.id << ". " << q.text << " (Asked by: " << q.user << ")\n";
                break;
            }
        }
    }
}

void displayMenu(const std::string &username) {
    int choice;
    while (true) {
        std::cout << "\n1. Ask a Question\n2. Answer Questions\n3. Search Questions\n4. Delete Content\n5. Exit\nChoice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: askQuestion(username); break;
            case 2: answerQuestion(username); break;
            case 3: searchQuestions(); break;
            case 4: deleteContent(username); break;
            case 5: std::cout << "Exiting...\n"; return;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
}