#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "answer/Answer.h"

#define PORT 8080
#define MAX_CLIENTS 5

std::unordered_map<std::string, std::string> users;

void processAnswer(int answerID, int userID, int questionID, std::string questionContent, std::string userAnswer) {
    Answer answer(answerID, userID, questionID, questionContent, userAnswer);

    // Simulating upvotes & downvotes for testing
    answer.upvote();
    answer.downvote();

    answer.display();
}

void saveUser(const std::string &username, const std::string &password) {
    if (users.find(username) != users.end()) {
        return; // Prevent duplicate users
    }
    std::ofstream file("data/users.txt", std::ios::app);
    if (file.is_open()) {
        file << username << " " << password << "\n";
        file.close();
    }
    users[username] = password;
}

void loadUsers() {
    std::ifstream file("data/users.txt");
    std::string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
}

void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);
    std::istringstream iss(buffer);
    std::string command, username, password;
    iss >> command >> username >> password;

    std::string response;
    if (command == "REGISTER") {
        if (users.find(username) != users.end()) {
            response = "User already exists";
        } else {
            saveUser(username, password);
            response = "Registration successful";
        }
    } else if (command == "LOGIN") {
        if (users.find(username) != users.end() && users[username] == password) {
            response = "Login successful";
        } else {
            response = "Invalid credentials";
        }
    }
    send(clientSocket, response.c_str(), response.size(), 0);
    close(clientSocket);
}


int main() {
    loadUsers();
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    std::vector<std::thread> threads;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, MAX_CLIENTS);
    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        threads.emplace_back(handleClient, new_socket);
    }
    for (auto &t : threads) t.join();
    close(server_fd);
    return 0;
}
