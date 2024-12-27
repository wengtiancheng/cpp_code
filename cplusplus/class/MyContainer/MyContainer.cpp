//
// Created by wtc on 2024/12/19.
//
#include "MyContainer.h"
#include<cstring>

int MyContainer::_count = 0;

MyContainer::MyContainer(int size) : _size(size) {
    // TODO: finish me
    _data = new int[size];
    _count++;
}

MyContainer::~MyContainer() {
    // TODO: finish me
    delete[] _data;
    _count--;
}

MyContainer::MyContainer(const MyContainer &Other) : _size(Other._size) {
    // TODO: finish me
    _data = new int[_size];
    memcpy(_data, Other._data, _size *sizeof(int));
    _count++;
}

MyContainer& MyContainer::operator=(const MyContainer &Other) {
    // TODO: finish me
    if(this == &Other) {
        return *this;
    }
    _size = Other._size;
    int* newData = new int [Other._size];
    memcpy(newData, Other._data, _size * sizeof(int));
    _data = newData;
    _count++;
}

int MyContainer::size() const {
    return _size;
}

int* MyContainer::data() const {
    return _data;
}

int MyContainer::count() {
    return _count;
}