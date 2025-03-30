#include "SentimentAnalyzer.h"
#include <vector>
#include <algorithm>
#include <cctype>

namespace {
    const std::vector<std::string> positiveWords = {
        // Basic positive
        "good", "great", "excellent", "love", "amazing",
        "awesome", "helpful", "perfect", "happy", "nice",
        // Expanded positive
        "wonderful", "fantastic", "superb", "delightful", "joyful",
        "brilliant", "outstanding", "pleasant", "satisfying", "marvelous",
        // Strong positive
        "terrific", "splendid", "fortunate", "lucky", "cheerful",
        "optimistic", "peaceful", "grateful", "content", "enthusiastic",
        // Achievement-related
        "success", "win", "achievement", "progress", "improvement",
        // Emotional states
        "joy", "excitement", "pride", "hope", "confidence"
    };
    
    const std::vector<std::string> negativeWords = {
        // Basic negative
        "bad", "terrible", "worst", "hate", "awful",
        "poor", "useless", "horrible", "dislike", "angry",
        // Expanded negative
        "disgusting", "miserable", "dreadful", "depressing", "annoying",
        "frustrating", "disappointing", "heartbreaking", "tragic", "cruel",
        // Strong negative
        "nasty", "bitter", "resentful", "gloomy", "hopeless",
        "anxious", "stressed", "irritated", "furious", "devastated",
        // Problem-related
        "failure", "loss", "mistake", "problem", "issue",
        // Emotional states
        "sadness", "fear", "regret", "shame", "despair"
    };

    std::string toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
            [](unsigned char c){ return std::tolower(c); });
        return lowerStr;
    }
}

std::string SentimentAnalyzer::analyzeSentiment(const std::string& text) {
    std::string lowerText = toLower(text);
    int posCount = 0, negCount = 0;

    // Count positive words
    for (const auto& word : positiveWords) {
        size_t pos = 0;
        while ((pos = lowerText.find(word, pos)) != std::string::npos) {
            if ((pos == 0 || !isalpha(lowerText[pos-1])) && 
                (pos + word.length() == lowerText.length() || !isalpha(lowerText[pos + word.length()]))) {
                posCount++;
            }
            pos += word.length();
        }
    }

    // Count negative words
    for (const auto& word : negativeWords) {
        size_t pos = 0;
        while ((pos = lowerText.find(word, pos)) != std::string::npos) {
            if ((pos == 0 || !isalpha(lowerText[pos-1])) && 
                (pos + word.length() == lowerText.length() || !isalpha(lowerText[pos + word.length()]))) {
                negCount++;
            }
            pos += word.length();
        }
    }

    // Determine sentiment
    if (posCount > negCount) return "Positive";
    if (negCount > posCount) return "Negative";
    return "Neutral";
}