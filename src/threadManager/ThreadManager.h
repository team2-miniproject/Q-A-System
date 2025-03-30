#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <iostream>
#include <thread>
#include <vector>

class ThreadManager {
private:
    std::vector<std::thread> threads;
public:
    void addThread(std::thread t);
    void waitAll();
};

#endif
