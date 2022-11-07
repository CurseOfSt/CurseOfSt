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
    node<T>*head;
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
        if (index <0||index >size) cout << "Index out of range" << endl;
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
    void erase(int index, T data) {
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
        capacity = 8;
        array_vec = new T[8];
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
            for (int i = size; i>index; i--) {
                array_vec[i] = array_vec[i - 1];
            }
            array_vec[index] = data;
            size++;
        }
    }
    T reference(int index) {
        if (index > size) {
            cout<<" You index out of range!" << endl;
        }
        else {
            return array_vec[index];
        }
    }
    T& operator[](int index) {
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
    T pop(){
        T temp = array_stack[0];
        T* tmp = array_stack;
        array_stack = new T[size];
        for (int i = 1; i < size; i++) {
            array_stack[i-1] = tmp[i];
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

bool is_operand(char val) {
    char operands[7] = { '+','-','*','/','^','s','c'};
    for (int i = 0; i < 7; i++) {
        if ((int)operands[i] == (int)val) return true;
    }
    return false;
}
int type_operand(char val) {
    char operands[9] = {'+','-','*','/','^','s','c','(',')'};
    for (int i = 0; i < 9; i++) {
        if (operands[i] == val) {
            if (i == 0 || i == 1) return 1;
            if (i == 2 || i == 3) return 2;
            if (i == 4) return 3;
            if (i == 5 || i == 6) return 4;
            else return 0;
        }
    }
    return -1;
}
bool is_number(char val) {
    if ((int)val >= 48 && (int)val <= 57) return true; 
    return false;  
}
bool is_brackets(char val) {
    if (val == '(' || val == ')') return true;
    return false;
}
bool buffer_str_is_right(string str) {
    int prev_ind_oper = -9999;
    int prev_ind_num = -9999;
    for (int i = 0; i < str.size(); i++) {
        if (is_number(str[i])){
            if ( (i>0)&& ((prev_ind_num == (i - 1)) || ( (prev_ind_num == (i - 2)) && ((str[i - 1] == '(') || (str[i - 1] == ')')) ))  ) {
                cout << "Error,wrong combination of numbers" << endl;
                return false;
            }
            prev_ind_num = i;
        }
        if (is_operand(str[i])) {
            if (str[i] == 's') {
                if (str[i + 1] == 'i' && str[i + 2] == 'n'){
                    i += 2;
                }
                else {
                    cout << "Error,wrong operator 'sin' " << endl;
                    return false;
                }
            } 
            if (str[i] == 'c') {
                if (str[i + 1] == 'o' && str[i + 2] == 's') {
                    i += 2;
                }
                else {
                    cout << "Error,wrong operator 'cos' " << endl;
                    return false;
                }
            }
            else if ((i > 0) && (prev_ind_oper == (i - 1))) {
                cout << "Error,wrong combination of operators" << endl;
                return false;
            }
            prev_ind_oper = i;
        }
    }
    return true;
}
int main() {
    my_vector<char>output_array;
    stack<char> operands_stack;
    string buffer;
    getline(cin, buffer);
    if (buffer_str_is_right(buffer)) {
        for (int i = 0; i < buffer.size(); i++) {
            char element = buffer[i];
            if (element != ' ') {
                if (is_number(element)) {
                    output_array.push_back(element);
                }
                else if (is_operand(element)) {
                    if (output_array.get_size() == 0 && element != 's' && element != 'c'){
                        cout << "Error,expression can't start with operator" << endl;
                        return 0;
                    }
                    else {
                        if (operands_stack.is_empty()) {
                            operands_stack.push(element);
                        }
                        else {
                            int prev_priority = type_operand(operands_stack.peak());
                            switch (element) {
                            case '+':
                            case '-':
                                if (1 <= prev_priority) {
                                    int prev_pr = prev_priority;
                                    while (1 <= prev_pr) {
                                        output_array.push_back(operands_stack.pop());
                                        if (operands_stack.is_empty() == 0) {
                                            prev_pr = type_operand(operands_stack.peak());
                                        }
                                        else prev_pr = 0;
                                    }
                                    operands_stack.push(element);
                                }
                                else {
                                    operands_stack.push(element);
                                }
                                break;
                            case '*':
                            case '/':
                                if (2 <= prev_priority) {
                                    int prev_pr = prev_priority;
                                    while (2 <= prev_pr) {
                                        output_array.push_back(operands_stack.pop());
                                        if (operands_stack.is_empty() == 0) {
                                            prev_pr = type_operand(operands_stack.peak());
                                        }
                                        else prev_pr = 0;
                                    }
                                    operands_stack.push(element);
                                }
                                else {
                                    operands_stack.push(element);
                                }
                                break;
                            case '^':
                                if (3 <= prev_priority) {
                                    int prev_pr = prev_priority;
                                    while (3 <= prev_pr) {
                                        output_array.push_back(operands_stack.pop());
                                        if (operands_stack.is_empty() == 0) {
                                            prev_pr = type_operand(operands_stack.peak());
                                        }
                                        else prev_pr = 0;
                                    }
                                    operands_stack.push(element);
                                }
                                else {
                                    operands_stack.push(element);
                                }
                                break;
                            case 's':
                                i += 2;
                                if (4 <= prev_priority) {
                                    int prev_pr = prev_priority;
                                    while (4 <= prev_pr) {
                                        output_array.push_back(operands_stack.pop());
                                        if (operands_stack.is_empty() == 0) {
                                            prev_pr = type_operand(operands_stack.peak());
                                        }
                                        else prev_pr = 0;
                                    }
                                    operands_stack.push(element);
                                }
                                else {
                                    operands_stack.push(element);
                                }
                                break;
                            case 'c':
                                i += 2;
                                if (4 <= prev_priority) {
                                    int prev_pr = prev_priority;
                                    while (4 <= prev_pr) {
                                        output_array.push_back(operands_stack.pop());
                                        if (operands_stack.is_empty() == 0) {
                                            prev_pr = type_operand(operands_stack.peak());
                                        }
                                        else prev_pr = 0;
                                    }
                                    operands_stack.push(element);
                                }
                                else {
                                    operands_stack.push(element);
                                }
                                break;
                            }
                        }
                    }
                }
                else if (is_brackets(element)) {
                    if (element == '(') {
                        operands_stack.push(element);
                    }
                    else if (element == ')') {
                        while (operands_stack.peak() != '(') {
                            if (operands_stack.is_empty()) {
                                system("cls");
                                cout << "Error,wrong amount of Right brackets " << endl;
                                return 0;
                            }
                            output_array.push_back(operands_stack.pop());
                        }
                        if (operands_stack.peak() == '(') {
                            operands_stack.pop();
                            if (operands_stack.peak() == 's' || operands_stack.peak() == 'c') {
                                output_array.push_back(operands_stack.pop());
                            }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < output_array.get_size(); j++) {
            if (output_array[j] == 's') {
                cout << "sin" << " ";
            }
            if (output_array[j] == 'c') {
                cout << "cos" << " ";
            }
            else if(output_array[j] != 's' && output_array[j] != 'c'){
                cout << output_array[j] << " ";
            }
        }
        while (operands_stack.is_empty() == 0) {
            cout << operands_stack.pop() << " ";
            if (operands_stack.peak() == '(') {
                system("cls");
                cout << "Error,wrong amount of Left brackets " << endl;
                return 0;
            }
        }
    }
}