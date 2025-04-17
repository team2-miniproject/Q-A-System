// #include "SearchEngine.h"

// std::vector<Question> SearchEngine::searchQuestions(const std::string& keyword, const std::vector<Question>& allQuestions) {
//     std::vector<Question> results;
//     for (const auto& question : allQuestions) {
//         if (question.getText().find(keyword) != std::string::npos) {
//             results.push_back(question);
//         }
//     }
//     return results;
// }
#include "SearchEngine.h"

std::vector<Question> SearchEngine::searchQuestions(const std::string& keyword, const std::vector<Question>& allQuestions) {
    std::ifstream file("data/index.txt");
    std::vector<std::string> questionIDs;
    std::vector<Question> results;
    std::string word, id;

    if (!file) {
        std::cerr << "Error opening index file!\n";
        return {};
    }

    // Read index file and collect question IDs that match the keyword
    while (file >> word >> id) {
        if (word == keyword) {
            questionIDs.push_back(id);
        }
    }
    file.close();

    // Find the corresponding questions
    for (const auto& question : allQuestions) {
        if (std::find(questionIDs.begin(), questionIDs.end(), std::string(question.getID())) != questionIDs.end()) {

            results.push_back(question);
        }
    }

    return results;
}
