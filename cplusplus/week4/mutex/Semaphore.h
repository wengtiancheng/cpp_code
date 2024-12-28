#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// Task 3
#include <condition_variable>
#include <mutex>
class Semaphore {
// TODO: Task3
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int count = 0);
    void P();
    void V();

};


#endif // SEMAPHORE_H  
