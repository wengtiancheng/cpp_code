cmake_minimum_required(VERSION 3.29)
project(shaweima)

set(CMAKE_CXX_STANDARD 17)

add_executable(shaweima
    main.cpp)
add_executable(person gpt/person.cpp)
add_executable(OP gpt/operator.cpp)
add_executable(STL gpt/stl.cpp)
