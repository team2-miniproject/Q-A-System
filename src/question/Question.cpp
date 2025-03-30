// #include "Question.h"

// Question::Question(std::string id, std::string txt, User u) 
//     : questionID(id), text(txt), author(u) {}

// void Question::display() {
//     std::cout << "Q: " << text << " (Posted by: " << author.getName() << ")" << std::endl;
// }


#include "Question.h"

Question::Question(std::string id, std::string txt, User u) 
    : questionID(id), text(txt), author(u) {
    updateIndex();  // Automatically update the index when a question is created
}

void Question::display() {
    std::cout << "Q: " << text << " (Posted by: " << author.getName() << ")" << std::endl;
}

// Tokenize the text into words
std::vector<std::string> Question::tokenizeText() const {
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// Update index file
void Question::updateIndex() {
    std::ofstream file("data/index.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening index file!\n";
        return;
    }

    std::vector<std::string> words = tokenizeText();
    for (const auto& word : words) {
        file << word << " " << questionID << "\n";
    }
    file.close();
}
