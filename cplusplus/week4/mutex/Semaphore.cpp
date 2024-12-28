#include "Semaphore.h"

Semaphore::Semaphore(int count) : count(count) {}

void Semaphore::P() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return count > 0; });
    --count;
}

void Semaphore::V() {
    std::unique_lock<std::mutex> lock(mtx);
    ++count;
    cv.notify_one();
}