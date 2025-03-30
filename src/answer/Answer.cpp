
#include "Answer.h"
#include "../sentimentAnalyzer/SentimentAnalyzer.h"
#include <iostream>

Answer::Answer(int answerID, int userID, int questionID, std::string questionContent, std::string content) {
    this->answerID = answerID;
    this->userID = userID;
    this->questionID = questionID;
    this->questionContent = questionContent;
    this->content = content;
    this->sentiment = SentimentAnalyzer::analyzeSentiment(content);
    this->upvotes = 0;
    this->downvotes = 0;
}

void Answer::upvote() {
    upvotes++;
}

void Answer::downvote() {
    downvotes++;
}

int Answer::getUpvotes() const {
    return upvotes;
}

int Answer::getDownvotes() const {
    return downvotes;
}

std::string Answer::getSentiment() const {
    return sentiment;
}

void Answer::display() {
    std::cout << "Answer ID: " << answerID << std::endl;
    std::cout << "User ID: " << userID << std::endl;
    std::cout << "Question ID: " << questionID << std::endl;
    std::cout << "Question: " << questionContent << std::endl;
    std::cout << "Answer: " << content << std::endl;
    std::cout << "Sentiment: " << sentiment << std::endl;
    std::cout << "Upvotes: " << upvotes << " | Downvotes: " << downvotes << std::endl;
}

