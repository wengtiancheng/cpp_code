#include "Concurrency.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>
using namespace std;

int sum = 0;
// TODO: Task1-1 define a lock of type `std::mutex` here
mutex tx;


void increment() {
  // TODO: Task1-1 increment the variable `sum` by 1
  // You need to think about how to guarantee the atomicity of `sum` self-incrementing 1
  lock_guard<mutex> lock(tx);
  sum++;

}

std::atomic<int> atomic_sum(0);

void init_sum(int value) {
  // TODO: Task1-2 set the value of `atomic_sum` atomically
  // The purpose of defining functions in this way is for teaching purposes
  atomic_sum.store(value);
}

void atomic_increment(int v) {
  // TODO: Task1-2 increment the variable `sum` by v
  atomic_sum.fetch_add(v);
}



// TODO: Task2 Define some global variable and locks for task2. 
// All tests are independent, so you don't need to think about the initialization of these global variables
std::mutex bracket_mtx;   // 互斥锁保护brackets
std::condition_variable cv;  // 条件变量
std::string brackets;     // 存储括号序列
int current_depth = 0;    // 当前嵌套深度

void produce(int k) {
    std::unique_lock<std::mutex> lock(bracket_mtx);
    while (current_depth >= k) {
        // 如果当前嵌套深度超过最大值，等待
        cv.wait(lock);
    }
    brackets += "(";
    ++current_depth;
    cv.notify_all();  // 通知消费者可以消费
}

void consume(int k) {
    std::unique_lock<std::mutex> lock(bracket_mtx);
    while (current_depth == 0) {
        // 如果没有可以消费的左括号，等待
        cv.wait(lock);
    }
    brackets += ")";
    --current_depth;
    cv.notify_all();  // 通知生产者可以生产
}

// === The following functions will only be used in test cases ===

void slow_increment(int times) {
  for (int i = 0; i < times; ++i) {
    increment();
  }
}

void quick_increment(int times, int v) {
  for (int i = 0; i < times; ++i) {
    atomic_increment(v);
  }
}

void producer_thread(int times, int k) {
  for (int i = 0; i < times; ++i) {
    produce(k);
  }
}

void consumer_thread(int times, int k) {
  for (int i = 0; i < times; ++i) {
    consume(k);
  }
}