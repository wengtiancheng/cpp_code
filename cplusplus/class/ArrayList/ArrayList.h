#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <optional>
#include <cstring>
#include <iostream>

// TODO: 在这里编写你的ArrayList类

template <typename T>
class ArrayList {
public:

    ArrayList(){
        capacity = 10;
        size = 0;
        data = new T[capacity];
    }

    ~ArrayList() {
        delete[] data;
    }
    void add(const T& x) {
        if(size < capacity) {
            data[size] = x;
            size++;
        }else if(size == capacity) {
            this.resize();
            data[size] = x;
            size++;
        }

    }

    void remove(const T& x) {
        int res = -1;
        for(int i = 0; i < size; i++) {
            if(data[i] == x) {
                res = i;
                break;
            }
        }
        if(res != -1) {
            for(int i = res; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
            size--;
        }

    }

    std::optional<T>get(int x) {
        if(x < 0 || x >= size) {
            return std:: nullopt;
        }
        return data[x];

    }

    int getSize() {
        return size;

    }

    int getCapacity() {
        return capacity;

    }

private:
    int capacity;
    int size;
    T* data;

    void resize() {
        int newCapacity = capacity + (capacity / 2);
        T* new_data = new T[newCapacity];
        std::memcpy(new_data, data, sizeof(T) * capacity);
        delete data;
        data = new_data;
        capacity = newCapacity;
    }
};

#endif // ARRAYLIST_H