#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "my_vector_stack.h"
#define None -2147483647
using std::cin;
using std::cout;
using std::endl;

bool is_number(char val) {
    if (val >= 48 && val <= 57 && val != '(' && val!=')') {
        return true;
    }
    return false;
}

bool check_for_children(std::string str,int &start, bool is_two_children) {
    int num_children = 0;
    int& i = start;
    if (!is_two_children) return false;
    while (i < str.length()) {
        if (str[i] == '(') { // обработка первых скобок 
            i++;
            while (is_number(str[i])) {
                i++;
            }
            if (str[i] == '(') { // means subtree after 1st child of root, go deeper 
                is_two_children = check_for_children(str, i, is_two_children);
                if (!is_two_children) return false; // if subtree contains more then 2 children
                num_children++;
                i++;
            }
            else if (str[i] == ')') { // means list (NOT subtree) 
                num_children++;
                i++;
            }
        }
        if (str[i] == '(') {
            i++;
            while (is_number(str[i])) {
                i++;
            }
            if (str[i] == '(') { // means subtree after 2nd child of root, go deeper 
                is_two_children = check_for_children(str, i, is_two_children);
                if (!is_two_children) return false; // if subtree contains more then 2 children
                num_children++;
                i++;
            }
            else if (str[i] == ')') { // means list (NOT subtree) 
                num_children++;
                i++;
            }
        }
        if (str[i] == ')') {
            return true;
        }
        else if ((str[i] == '(' && num_children == 2)) {
            return false;
        }
    }
    return true;
}

bool string_is_right(std::string str) {
    int l_br = 0;
    int r_br = 0;
    for (int i = 0; i <str.length();) {
        if (!is_number(str[i]) && str[i] != ' ' && str[i] != '(' && str[i] != ')') {
            cout << " Invalid syntax " << endl;
            break;
            return false;
        }
        if (str[i] == '(') {
            l_br++;
        }
        if (str[i] == ')') {
            r_br++;
        }
        if ( (str[i] == ' ') && (is_number(str[i - 1])) && (is_number(str[i + 1])) && i>0 ) {
            cout << "Invalid syntax: 'number' + 'space' + 'number'  " << endl;
            return false;
        }
        if (is_number(str[i]) && str[i - 1] == ')' && str[i + 1] == '(' && i > 0) {
            return false;
        }
        i++;  
    }
    if (l_br != r_br) {
        cout << "Wrong amount of brackets" << endl;
        return false;
    }
    return true;
}


template <typename T>
struct tree_node {
private:

public:
    T data;
    tree_node* left = nullptr;
    tree_node* right = nullptr;
    tree_node* parent = nullptr;
    tree_node(T data, tree_node* parent) {
        this->data = data;
        left = nullptr;
        right = nullptr;
        this->parent = parent;
    }
    tree_node(tree_node* parent) {
        this->parent = parent;
    }
    ~tree_node() {
        delete left;
        delete right;
        delete parent;
    }
    T search(tree_node* rout, T data) {
        if ((rout != nullptr) && (rout->data == data)) {
            return data;
        }
        else if ((rout != nullptr) && data < rout->data) {
            return search(rout->left, data);
        }
        else if ((rout != nullptr) && data > rout->data) {
            return search(rout->right, data);
        }
    }
    bool is_exist(tree_node* rout, T data) {
        if (search(rout, data) == data) {
            return true;
        }
        else {
            return false;
        }
    }
    
    void breadth_first_search(tree_node<int>* tree) {
        my_vector <tree_node<int>*> queue;
        queue.push_back(tree);
        while (queue.get_size() != 0) {
            tree_node<int>* tmp = queue.pop_front();
            cout << tmp->data << " ";
            if (tmp->left != nullptr) {
                queue.push_back(tmp->left);
            }
            if (tmp->right != nullptr) {
                queue.push_back(tmp->right);
            }
        }
    }
    void in_order_Traversal(tree_node<int>* tree) {
        if (tree != nullptr) {
            in_order_Traversal(tree->left);
            cout << tree->data << " ";
            in_order_Traversal(tree->right);
        }
    }
    void pre_order_Traversal(tree_node<int>* tree) {
        if (tree != nullptr) {
            cout << tree->data << " ";
            in_order_Traversal(tree->left);
            in_order_Traversal(tree->right);
        }
    }
    void post_order_Traversal(tree_node<int>* tree) {
        if (tree != nullptr) {
            in_order_Traversal(tree->left);
            in_order_Traversal(tree->right);
            cout << tree->data << " ";
        }
    }

    /*tree_node get_previous_(tree_node* rout) {
        if (rout->left != nullptr) {
            return rout->left;
        }
    }
    tree_node get_max(tree_node* rout) {
        if (rout->right == nullptr) {
            return rout;
        }
        return get_max(rout->right);
    }
    tree_node get_min(tree_node* rout) {
        if (rout->left == nullptr) {
            return rout->left;
        }
        return get_min(rout->left);
    }*/
    /*tree_node add(tree_node* rout, tree_node* new_rout) {
        while (rout != nullptr) {
            if (rout->data > new_rout->data) {
                if (rout->left != nullptr) {
                    rout = rout->left;
                }
                else {
                    new_rout->parent = rout;
                    rout->left = new_rout;
                    break;
                }
            }
            else if (rout->data < new_rout->data) {
                if (rout->right != nullptr) {
                    rout = rout->right;
                }
                else {
                    new_rout->parent = rout;
                    rout->right = new_rout;
                    break;
                }
            }
        }
    }*/
    /*tree_node add(tree_node* rout, T data) {
        if (rout == nullptr) {
            return tree_node(data);
        }
        else if (data< rout->data) {
            rout->left = add(rout->left,data);
        }
        else if (rout->data > data) {
            rout->right = add(rout->right, data);
        }
        return rout;
    }*/
    /*tree_node delete(tree_node* root, T data) {
        if (rout == nullptr) {
            return root;
        }
        if (data < root.data) {
            root.left = delete(root.left, data);
        }
        else if (data > root.data) {
            root.right = delete(root.right, data);
        }
        else if (root.left != nullptr && root.right != nullptr) {

        }
    }*/
};

int find_index(std::string str, int start_i, int end_i) {
    if (start_i > end_i) return -1;
    stack<char> s_s;
    for (int i = start_i; i <= end_i; i++) {
        if (str[i] == '(') {
            s_s.push(str[i]);
        }
        else if (str[i] == ')') {
            if (s_s.peak() == '(') {
                s_s.pop();
                if (s_s.is_empty()) return i;
            }

        }
    }
    return -1;
}

tree_node<int>* tree_from_str(std::string str, int start_i, int end_i, tree_node<int>* parent) {

    if (start_i > end_i) return NULL;

    int num = 0;
    bool flag = false;
    if (str[start_i] == '-') {
        flag = true;
    }
    while ((start_i <= end_i && str[start_i] >= '0' && str[end_i] <= '9' || str[start_i] == '-')) {
        num *= 10;
        if (str[start_i] != '-') {
            num += (str[start_i] - '0');
        }
        start_i++;
    }
    if (flag) num = -num;

    tree_node<int>* root = new tree_node<int>(num, parent);
    int index = -1;

    if (start_i <= end_i && str[start_i] == '(') {
        index = find_index(str, start_i, end_i);
    }
    if (index != -1) {
        root->left = tree_from_str(str, start_i + 1, index - 1, root);

        root->right = tree_from_str(str, index + 2, end_i - 1, root);
    }
    return root;
}

//int StrToInt(my_vector<char>&s){
//    //cout << " 5" << endl;
//    int temp = 0; // число
//    int i = 0;
//    int sign = 0; // знак числа 0- положительное, 1 — отрицательное
//    if (s[i] == '-' && s.get_size()!=0)
//    {
//        sign = 1;
//        i++;
//    }
//    while (s[i] >= 0x30 && s[i] <= 0x39)
//    {
//        temp = temp + (s[i] & 0x0F);
//        temp = temp * 10;
//        i++;
//    }
//    temp = temp / 10;
//    if (sign == 1)
//        temp = -temp;
//    return temp;
//}

template <typename T>
struct rb_node {
    T data;
    rb_node* left;
    rb_node* right;
    rb_node* parent;
    bool is_red;
};
class red_black_tree {
    rb_node<int>* root;
    rb_node<int>* NIL;

    void create_NIL(rb_node<int>* node, rb_node<int>* parent) {
        node->data = None;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
        node->is_red = false;
    }

    rb_node<int>* search_node(rb_node<int>* node, int data) {
        if ((node == NIL) || (node->data == data)) {
            return node;
        }
        if (data < node->data) {
            return search_node(node->left, data);
        }
        return search_node(node->right, data);
    }

    int search_data(rb_node<int>* root, int data) {
        if ((root != NIL) && (root->data == data)) {
            return data;
        }
        else if ((root != NIL) && (data < root->data)) {
            return search_data(root->left, data);
        }
        else if ((root != NIL) && (data > root->data)) {
            return search_data(root->right, data);
        }
    }

    bool is_exist(rb_node<int>* node, int data) {
        if (search_data(root, data) == data) {
            return true;
        }
        else {
            return false;
        }
    }

    void breadth_first_search(rb_node<int>* node) {
        my_vector <rb_node<int>*> queue;
        queue.push_back(node);
        while (queue.get_size() != 0) {
            rb_node<int>* tmp = queue.pop_front();
            cout << tmp->data << " ";
            if (tmp->left != NIL) {
                queue.push_back(tmp->left);
            }
            if (tmp->right != NIL) {
                queue.push_back(tmp->right);
            }
        }
    }

    void in_order_Traversal(rb_node<int>* node) {
        if (node != NIL) {
            in_order_Traversal(node->left);
            cout << node->data << " ";
            in_order_Traversal(node->right);
        }
    }

    void preorder_iterative(rb_node<int>* node) {
        if (node == NIL)return;
        stack<rb_node<int>*> stack;
        stack.push(node);
        while (stack.get_size() != 0) {
            rb_node<int>* tmp = stack.pop();
            cout << tmp->data << " ";
            if (tmp->right != NIL) {
                stack.push(tmp->right);
            }
            if (tmp->left != NIL) {
                stack.push(tmp->left);
            } 
        }
    }

    void pre_order_Traversal(rb_node<int>* node) {
        if (node != NIL) {
            cout << node->data << " ";
            in_order_Traversal(node->left);
            in_order_Traversal(node->right);
        }
    }

    void post_order_Traversal(rb_node<int>* node) {
        if (node != NIL) {
            in_order_Traversal(node->left);
            in_order_Traversal(node->right);
            cout << node->data << " ";
        }
    }

    rb_node<int>* get_max(rb_node<int>* node) {
        if (node->right == NIL) {
            return node;
        }
        return get_max(node->right);
    }

    rb_node<int>* get_min(rb_node<int>* node) {
        if (node->left == NIL) {
            return node;
        }
        return get_min(node->left);
    }

    void transplant(rb_node<int>* parent, rb_node<int>* child) {
        if (parent == root) {
            root = child;
        }
        else if (parent == parent->parent->left) {
            parent->parent->left = child;
        }
        else {
            parent->parent->right = child;
        }
        child->parent = parent->parent;
    }

    void left_rotate(rb_node<int>* node) {
        rb_node<int>* y = node->right;
        node->right = y->left;
        if (y->left != NIL) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = y;
        }
        else if (node == node->parent->left) {
            node->parent->left = y;
        }
        else {
            node->parent->right = y;
        }
        y->left = node;
        node->parent = y;
        //rb_node<int>* grand_p = node->parent; //отец поворачиваемой вершины
        //rb_node<int>* tmp = node->left; //правый потомок поворачиваемой вершины
        //if (grand_p == root) {
        //    root = node;
        //    grand_p->right = tmp;
        //    tmp->parent = grand_p;
        //    node->left = grand_p;
        //    node->parent = nullptr;
        //    grand_p->parent = node;
        //}
        //else {
        //    grand_p = tmp;
        //    tmp->parent = grand_p;
        //    node->left = grand_p;
        //    node->parent = grand_p->parent;
        //    grand_p->parent = node;
        //}
    }

    void right_rotate(rb_node<int>* node) {
        rb_node<int>* y = node->left;
        node->left = y->right;
        if (y->right != NIL) {
            y->right->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = y;
        }
        else if (node == node->parent->right) {
            node->parent->right = y;
        }
        else {
            node->parent->left = y;
        }
        y->right = node;
        node->parent = y;
        //rb_node<int>* grand_p = node->parent; //отец поворачиваемой вершины
        //rb_node<int>* tmp = node->right; //правый потомок поворачиваемой вершины
        //if (grand_p->parent == root) {
        //    root = node;
        //    grand_p->left = tmp; //правый потомок поворачиваемой вершины делаем левым потомком отца
        //    tmp->parent = grand_p;// привязываем в деду
        //    node->right = grand_p;// правым потомком отца делаем деда
        //    node->parent = nullptr; // новым дедом у поворачиваемого отца(корня) становится nullptr
        //    grand_p->parent = node; // привязываем бывшего деда к поворачиваемому отцу
        //}
        //else {
        //    grand_p->left = tmp; //правый потомок поворачиваемой вершины делаем левым потомком отца
        //    tmp->parent = grand_p;// привязываем в деду
        //    node->right = grand_p;// правым потомком отца делаем деда
        //    node->parent = grand_p->parent; // новым дедом у поворачиваемого отца становится отец бывшего деда 
        //    grand_p->parent = node; // привязываем бывшего деда к поворачиваемому отцу
        //}
    }

    void fix_insert(rb_node<int>* node) {
        rb_node<int>* uncle;
        while (node->parent->is_red == 1) {
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;
                // 2.1
                if (uncle->is_red == 1) {
                    uncle->is_red = 0;
                    node->parent->is_red = 0;
                    node->parent->parent->is_red = 1; // уходи наверх и будет проверять для деда
                    node = node->parent->parent;
                }
                // (2.2)
                else {
                    if (node == node->parent->right) {
                        // 2.2.2 - новая вершина - правый потомок
                        node = node->parent;
                        left_rotate(node);
                    }
                    // 2.2.1 - новая вершина - левый потомок
                    node->parent->is_red = 0;
                    node->parent->parent->is_red = 1;
                    right_rotate(node->parent->parent);


                }
            }
            // зеркальная ситуация
            else {
                uncle = node->parent->parent->left;
                if (uncle->is_red == 1) {
                    uncle->is_red = 0;
                    node->parent->is_red = 0;
                    node->parent->parent->is_red = 1; // уходи наверх и будет проверять для деда
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->is_red = 0;
                    node->parent->parent->is_red = 1;
                    left_rotate(node->parent->parent);

                }
            }
            if (node == root) {
                break;
            }
        }
        root->is_red = 0;
    }

    void fix_erase(rb_node<int>* node) {
        rb_node<int>* tmp;
        while (node != root && node->is_red == 0) {
            if (node == node->parent->left) {
                tmp = node->parent->right;

                

                    if (tmp->is_red == 1) {
                        tmp->is_red = 0;
                        node->parent->is_red = 1;
                        left_rotate(node->parent);
                        tmp = node->parent->right;
                    }
                    if (tmp->left->is_red == 0 && tmp->right->is_red == 0) {
                        tmp->is_red = 1;
                        node = node->parent;
                    }
                    else {
                        if (tmp->right->is_red == 0) {
                            tmp->left->is_red = 0;
                            tmp->is_red = 1;
                            right_rotate(tmp);
                            tmp = node->parent->right;
                        }
                        tmp->is_red = node->parent->is_red;
                        node->parent->is_red = 0;
                        tmp->right->is_red = 0;
                        left_rotate(node->parent);
                        node = root;
                    }

                
                
            }
            else {
                tmp = node->parent->right;

                

                    if (tmp->is_red == 1) {
                        tmp->is_red = 0;
                        node->parent->is_red = 1;
                        right_rotate(node->parent);
                        tmp = node->parent->left;
                    }

                    if (tmp->right->is_red == 0 && tmp->left->is_red == 0) {
                        tmp->is_red = 1;
                        node = node->parent;
                    }
                    else {
                        if (tmp->left->is_red == 0) {
                            tmp->right->is_red = 0;
                            tmp->is_red = 1;
                            left_rotate(tmp);
                            tmp = node->parent->left;
                        }
                        tmp->is_red = node->parent->is_red;
                        node->parent->is_red = 0;
                        tmp->left->is_red = 0;
                        right_rotate(node->parent);
                        node = root;
                    }

                

            }
        }
        node->is_red = 0;
    }

    void print_tree(rb_node<int>* root, std::string indent, bool right) {
        if (root != NIL) {
            cout << indent;
            if (right) {
                cout << "R---";
                indent += "     ";
            }
            else {
                cout << "L---";
                indent += "     ";
            }

            std::string color = root->is_red ? "red" : "black";
            cout << root->data << " (" << color << ")" << endl;
            print_tree(root->left, indent, false);
            print_tree(root->right, indent, true);
        }
    }

public:
    red_black_tree() {
        NIL = new rb_node<int>;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->is_red = 0;
        root = NIL;
    }
    red_black_tree(int data) {
        NIL = new rb_node<int>;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->is_red = 0;
        root = new rb_node<int>;
        root->data = data;
        root->parent = nullptr;
        root->left = NIL;
        root->right = NIL;
        root->is_red = 0;
    }
    void insert(int data) {
        rb_node<int>* node = new rb_node<int>;  // когда x дойдет до NIL,то мы cделаем node новой вершиной
        node->data = data;
        node->left = NIL;
        node->right = NIL;
        node->parent = nullptr;
        node->is_red = true;
        rb_node<int>* y = nullptr;// чтобы не "болтался" ; 'y' нужен,чтобы когда мы дойдем x-ом до NIL вершины, y - будет родителем x - > (node);
        rb_node<int>* x = this->root; //переменная для поиска подходящего места для вставки node ( начинаем с корня)
        while (x != NIL) {
            y = x;
            if (node->data < x->data ) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        node->parent = y;
        // если у нас не было даже корня то есть мы даже не зайдем в while,то мы должны создать root (черный)
        if (y == nullptr) {
            node->is_red = 0;
            root = node;
            return;
        }
        else if (node->data >= y->data) {
            y->right = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        if (node->parent->parent == nullptr) //если нет деда,то не возникает проблем с цветом дяди
            return;
        fix_insert(node);
    }
    void erase(int data) {
        rb_node<int>* node = search_node(root, data); // z
        rb_node<int>* tmp = NIL;
        while (node->left->data == data || node->right->data == data) {
            if (node->left->data == data) {
                tmp = node->left;
                node = node->left;
                
            }
            if (node->right->data == data) {
                tmp = node->right;
                node = node->right;
            }
        }
        if (is_exist(node, data)) {
            rb_node<int>* y;
            rb_node<int>* x;
            y = node;
            bool orig_color = y->is_red;
            if (node->left == NIL) {
                x = node->right;// x
                transplant(node, node->right);
            }
            else if ( node->right == NIL) {
                x = node->left; // x
                transplant(node, node->left);
            }
            else {
                y = get_min(node->right);// y
                // искали минимальный в правом поддереве,след-но не будет левого под дерева,берем правый эл-т (x).
                bool orig_color = y->is_red;
                x = y->right; // x
                if (y->parent == node) {
                    x->parent = y;
                }
                else {
                    transplant(y, y->right);  // подвешиваем этот правый эл-т,освобождаем (y)
                    y->right = node->right;  // сыном (y) становится правый сын эл-та для удаления.
                    y->right->parent = y; // делаем (y) отцом для этого эл-та
                }
                transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->is_red = node->is_red;
            }
            delete node;
            if (!orig_color)
                fix_erase(x);
        }
        
    }

    void find(int data) {
        search_data(root, data);
    }
    void print() {
        if (root) {
            print_tree(root, "", 1);
        }
    }

    void in_oder() {
        in_order_Traversal(root);
    }

    void pre_oder_iterative() {
        preorder_iterative(root);
    }

    void pre_oder() {
        pre_order_Traversal(root);
    }

    void post_oder() {
        post_order_Traversal(root);
    }


    void breadth_search() {
        breadth_first_search(root);
    }
};

int main() {
    std::ifstream fin;
    std::string tmp;
    fin.open("Tree_parsing.txt");
    getline(fin, tmp);
    cout <<"File containd this string  -  "<< tmp << endl;
    fin.close();
    std::string str;
    int j = 0;
    if (string_is_right(tmp)) {
        for (int i = 0; i < tmp.length();) {
            if (tmp[i] != ' ') {
                str.push_back(tmp[i]);
                j++;
            }
            i++;
        }
    }
    else return 0;
    bool is_two_children = true;
    int start = 0;
    if (check_for_children(str, start, is_two_children)) {
        cout << "Binary tree was built - " << str;
        cout << endl;
        cout << endl;
        tree_node<int>* root = tree_from_str(str, 1, str.length() - 2, nullptr);
        cout << "in_order  : ";
        root->in_order_Traversal(root);
        cout << endl;
        cout << "pre_order  : ";
        root->pre_order_Traversal(root);
        cout << endl;
        cout << "post_order  : ";
        root->post_order_Traversal(root);
        cout << endl;
        cout << "breadth_first_search  : ";
        root->breadth_first_search(root);
        cout << endl;
        cout << endl;
    }
    else {
        cout << "Tree is not binary !!!"<<endl;
    }
    cout << "---------------------------------- ";
    cout << endl;
    red_black_tree tree;
    tree.insert(8);
    tree.insert(10);
    tree.insert(3);
    tree.insert(2);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);
    tree.insert(15);
    tree.insert(14);
    tree.insert(4);

    /*for (int i = 16; i <= 26; i++) {
        tree.insert(i);
    }
    tree.erase(8);
    tree.erase(15);
    tree.erase(2);
    tree.erase(2);
    tree.erase(3);*/

    tree.print();

    cout << endl;
    cout << "in_order  : ";
    tree.in_oder();
    cout << endl; 
    cout << "pre_order_iterative  : ";
    tree.pre_oder_iterative();
    cout << endl;
    cout << "post_order  : ";
    tree.post_oder();
    cout << endl;
    cout << "breadth_first_search  : ";
    tree.breadth_search ();
    cout << endl;


}