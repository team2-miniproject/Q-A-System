#include "ThreadManager.h"

void ThreadManager::addThread(std::thread t) {
    threads.push_back(std::move(t));
}

void ThreadManager::waitAll() {
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
