#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
template<typename T>
class my_list {
    int size;
    template <typename T>
    class node {
    public:
        node* next;
        T data;
        node(T data, node* pnext = nullptr) {
            this->data = data;
            this->next = pnext;
        }
    };
    node<T>* head;
    void pop_front() {
        node<T>* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }
    void clear() {
        while (size != 0) {
            pop_front();
        }
    }
public:
    my_list() {
        size = 0;
        head = nullptr;
    }
    ~my_list() {
        clear();
    }
    void push_back(T data) {
        if (head == nullptr) {
            head = new node<T>(data);
        }
        else {
            node<T>* tmp = this->head;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = new node<T>(data);
        }
        size++;
    }
    void push_front(T data) {
        head = new node<T>(data, head);
        size++;
    }
    int get_size() {
        return size;
    }
    T& get_reference(int index) {
        if (index > size) {
            cout << "Index out of range" << endl;
        }
        else {
            int count = 0;
            node<T>* tmp = this->head;
            while (count != index) {
                tmp = tmp->next;
                count++;
            }
            return tmp->data;
        }
    }
    T& operator[](int index) {
        if (index > size) {
            cout << "Index out of range" << endl;
        }
        else return get_reference(index);
    }
    void insert(int index, T data) {
        if (index == 0) push_front();
        if (index == size) push_back();
        if (index <0 || index >size) cout << "Index out of range" << endl;
        else if (index > 0 && index < size) {
            node<T>* tmp = this->head;
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
            }
            node<T>* new_node = new node<T>(tmp->next, data);
            tmp->next = new_node;
            size++;
        }
    }
    void erase(int index) {
        if (index == 0) pop_front();
        if (index <0 || index >size) cout << "Index out of range" << endl;
        else {
            node<T>* tmp = head;
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
            }
            node<T>* del_element = tmp->next;
            tmp->next = del_element->next;
            delete del_element;
            size--;
        }
    }
};

template<typename T>
class my_vector {
    int size=0;
    int capacity=0;
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
        /*delete[] array_vec;*/
        clear();
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
    T pop_back() {
        if (size > 0) {
            T temp = array_vec[size - 1];
            T* tmp = array_vec;
            array_vec = new T[capacity];
            for (int i = 0; i < size - 1; i++) {
                array_vec[i] = tmp[i];
            }
            size -= 1;
            /*delete[]tmp;*/
            return temp;
        }
        else cout << "ERROR" << endl;
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
    void resize(int newsize) {
        T* tmp = array_vec;
        size = newsize;
        capacity = size * 2;
        array_vec = new T[capacity];
        delete[]tmp;
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