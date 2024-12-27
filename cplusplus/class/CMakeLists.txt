cmake_minimum_required(VERSION 3.10)

project(CardGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CardGame card/main.cpp
        NUM_APPEAR_ONCE/solution.cpp
        NUM_APPEAR_ONCE/solution.h
        NUM_APPEAR_ONCE/main.cpp)
add_executable(MemContext MemContext/main.cpp)
add_executable(Message
        MessageQueue/main.cpp
        MessageQueue/MessageQueueManager.cpp
        MessageQueue/MessageQueueManager.h)
add_executable(Sort sort/main.cpp)
add_executable(Reverse reverse/main.cpp)
add_executable(Count count/main.cpp)
add_executable(ONCE NUM_APPEAR_ONCE/Solution.cpp NUM_APPEAR_ONCE/Solution.h
        NUM_APPEAR_ONCE/main.cpp)
