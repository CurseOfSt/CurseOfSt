#include <iostream>
#include<string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
template<typename T>
class my_vector {
    int size;
    int capacity;
    T* array_vec;
    void add_capacity() {
        capacity*=2;
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
        capacity = 1;
        array_vec = new T[1];
    }
    my_vector(int amount) {
        size = amount;
        capacity = amount;
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
            for (int i = index + 1; i < size + 1; i++) {
                array_vec[i] = array_vec[i - 1];
            }
            size++;
        }
    }
    int reference(int index) {
        if (index > size) {
            cout<<" You index out of range!" << endl;
        }
        else {
            return array_vec[index];
        }
    }
    int& operator[](int index) {
        return array_vec[index];
    }
    void erase(int index, T data) {
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
    int find(int data) {
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
    //bool contains(){}
};
template<typename T>
class stek {
    int size;
    int amount_elements;
    T* array_stek;
public:
    void stek() {
        size = 0;
        array_stek = new T[1];
    }
    void stek(int razmer) {
        size = razmer;
        array_stek = new T[size];
        amount_elements = 0;
    }
    T peak() {
        return array_stek[0];
    }
    T pop(){
        amount_elements -= 1;
        T temp = array_stek[0];
        T* tmp = array_stek;
        array_stek = new T[size];
        for (int i = 1; i < size; i++) {
            array_stek[i-1] = tmp[i];
        }
        delete[]tmp; 
        return temp;
    }
    void push(T data) {
        amount_elements += 1;
        T* tmp = array_stek;
        array_stek = new T[size];
        for (int i = 1; i < size; i++) {
            array_stek[i] = tmp[i - 1];
        }
        delete[]tmp;
        array_stek[0] = data;
    }
    bool is_empty() {
        if (amount_elements > 0) return false;
        else return true;
    }
};
int main(){
    my_vector<char>output;
    stek<char> operands;
    string buffer;
    getline(cin, buffer);
    
    for (int i = 0; i < buffer.size();i++) {
        if (buffer[i] != ' ') {
            
        }
    }
    cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
