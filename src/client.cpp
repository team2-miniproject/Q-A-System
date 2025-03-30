#include "template.cpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

bool authenticateUser(std::string command) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    send(sock, command.c_str(), command.size(), 0);
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    close(sock);

    std::string response(buffer);
    std::cout << response << std::endl;
    return response == "Login successful" || response == "Registration successful";
}

int main() {
    std::string username, password;
    int choice;
    bool loggedIn = false;

    while (!loggedIn) {
        std::cout << "1. Register\n2. Login\nChoice: ";
        std::cin >> choice;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        std::string command = (choice == 1 ? "REGISTER " : "LOGIN ") + username + " " + password;
        loggedIn = authenticateUser(command);
    }

    displayMenu(username);
    return 0;
}
