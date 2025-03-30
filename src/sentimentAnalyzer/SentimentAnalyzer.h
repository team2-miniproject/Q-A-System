#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <string>

class SentimentAnalyzer {
public:
    static std::string analyzeSentiment(const std::string& text);
};

#endif