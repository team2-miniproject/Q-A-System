#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <vector>
#include <map>//
#include <set>//
#include <fstream>//
#include "../question/Question.h"
#include "../user/User.h"

class SearchEngine {
public:
    static std::vector<Question> searchQuestions(const std::string& keyword, const std::vector<Question>& allQuestions);
};

#endif
