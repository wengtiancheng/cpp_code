cmake_minimum_required(VERSION 3.29)
project(week4)

set(CMAKE_CXX_STANDARD 17)

include_directories(trie)

add_executable(week4
    trie/Main.cpp
    trie/SimpleGTest.h
    trie/trie.cpp
    trie/trie.h
    trie/trie_store.cpp
    trie/trie_store.h)
