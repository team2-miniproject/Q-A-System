/*#ifndef ANSWER_H
#define ANSWER_H

#include <iostream>

class Answer {
private:
    std::string aID, qID, userID, text;
    int upvotes, downvotes, sentimentScore;

public:
    Answer(std::string id, std::string q, std::string u, std::string txt);
    void upvote();
    void downvote();
    void display();
};

#endif*/
#ifndef ANSWER_H
#define ANSWER_H

#include <string>

class Answer {
private:
    int answerID;
    int userID;
    int questionID;
    std::string questionContent;
    std::string content;
    std::string sentiment;
    int upvotes;
    int downvotes;

public:
    Answer(int answerID, int userID, int questionID, std::string questionContent, std::string content);

    void upvote();
    void downvote();

    int getUpvotes() const;
    int getDownvotes() const;
    std::string getSentiment() const;

    void display();
};

#endif

