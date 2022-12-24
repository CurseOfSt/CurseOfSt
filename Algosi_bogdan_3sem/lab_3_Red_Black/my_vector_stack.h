#pragma once
#include<iostream>
using std::cout;
using std::endl;

template<typename T>
class my_vector {
    int size;
    int capacity;
    T* array_vec = nullptr;
    void add_capacity() {
        capacity *= 2;
        T* tmp = array_vec;
        array_vec = new T[capacity];
        for (int i = 0; i < size; i++) {
            array_vec[i] = tmp[i];
        }
        delete[]tmp;
    }
public:
    my_vector() {
        size = 0;
        capacity = 8;
        array_vec = new T[8];
    }
    my_vector(int amount) {
        size = amount;
        capacity = amount * 8;
        array_vec = new T[amount];
    }
    ~my_vector() {
        delete[] array_vec;
    }
    int get_size() {
        return size;
    }
    void push_back(T data) {
        if (size == capacity) {
            add_capacity();
            array_vec[size] = data;
            size++;
        }
        else {
            array_vec[size] = data;
            size++;
        }
    }
    void insert(int index, T data) {
        if (index > size) {
            cout << "Eror!!! You can't insert in dimension 'n' dimension 'n+k'!" << endl;
        }
        if (index == size) {
            push_back(data);
        }
        else {
            if (size == capacity) {
                add_capacity();
            }
            for (int i = size; i > index; i--) {
                array_vec[i] = array_vec[i - 1];
            }
            array_vec[index] = data;
            size++;
        }
    }
    T& reference(int index) {
        if (index > size) {
            cout << " You index out of range!" << endl;
        }
        else {
            return array_vec[index];
        }
    }
    T& operator[](int index) {
        return array_vec[index];
    }
    T pop_front() {
        if (size > 0) {
            T temp = array_vec[0];
            T* tmp = array_vec;
            array_vec = new T[capacity];
            for (int i = 0; i < size; i++) {
                array_vec[i] = tmp[i + 1];
            }
            size -= 1;
            delete[]tmp;
            return temp;
        }
    }
    void clear() {
        /*for (int i = 0; i < size; i++) {
            pop_back();
        }*/
        while (size > 0) {
            erase(0);
        }
    }
    void erase(int index) {
        if (index >= size) {
            cout << " You index out of range!" << endl;
        }
        else {
            size -= 1;
            T* tmp = array_vec;
            array_vec = new T[capacity];
            for (int i = 0; i < index; i++) {
                array_vec[i] = tmp[i];
            }
            for (int i = index; i < size; i++) {
                array_vec[i] = tmp[i + 1];
            }
            delete[]tmp;
        }
    }
    int find(T data) {
        bool is_here = false;
        for (int i = 0; i < size; i++) {
            if (array_vec[i] == data) {
                is_here = true;
                return i;
                break;
            }
            if (!is_here) return -1;
        }
    }
};

template<typename T>
class stack {
    int size;
    T* array_stack;
public:
    stack() {
        size = 0;
        array_stack = new T[1];
    }
    stack(int razmer) {
        size = razmer;
        array_stack = new T[size];
    }
    ~stack() {
        delete[]array_stack;
    }
    bool is_empty() {
        if (size > 0) return false;
        else return true;
    }
    int get_size() {
        return size;
    }
    T peak() {
        return array_stack[0];
    }
    T pop() {
        T temp = array_stack[0];
        T* tmp = array_stack;
        array_stack = new T[size];
        for (int i = 1; i < size; i++) {
            array_stack[i - 1] = tmp[i];
        }
        size -= 1;
        delete[]tmp;
        return temp;
    }
    void push(T data) {
        size += 1;
        T* tmp = array_stack;
        array_stack = new T[size];
        for (int i = 1; i < size; i++) {
            array_stack[i] = tmp[i - 1];
        }
        delete[]tmp;
        array_stack[0] = data;
    }
};