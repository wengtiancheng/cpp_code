cmake_minimum_required(VERSION 3.29)
project(week3)

set(CMAKE_CXX_STANDARD 14)

include_directories(3)
include_directories(tmp)

add_executable(week3
    3/Calculator.cpp
    3/Calculator.h
    3/Main.cpp
    3/TreeNode.h
    tmp/Main.cpp
    tmp/MessageQueueManager.cpp
    tmp/MessageQueueManager.h
    1.cpp
    2.cpp
    4.cpp
    5.cpp
    tmp.cpp
        3/plant.cpp)
