#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

//Узел дерева
struct Node {
    int data;
    //левый\правый подузел
    Node* left;
    Node* right;
    //высота дерева
    int height;
    Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
};


//Бинарное дерево
class BinarySearchTree {
private:
    Node* root;//дерево
    
    //Вставка  
    void insert(Node* node, int data) { //node узел,data число для вставки
        //через сравнения числа со значением текущего узла находим место для вставки
        if (data < node->data) {
            if (node->left == nullptr) {
                node->left = new Node(data);
            }
            else {
                insert(node->left, data);
            }
        }
        else if (data > node->data) {
            if (node->right == nullptr) {
                node->right = new Node(data);
            }
            else {
                insert(node->right, data);
            }
        }
    }
 
    //Поиск
    bool search(Node* node, int data) {
        //через сравнения числа со значением текущего узла делаем поиск числа в дереве
        if (node == nullptr) {
            return false;
        }
        else if (data < node->data) {
            return search(node->left, data);
        }
        else if (data > node->data) {
            return search(node->right, data);
        }
        else {
            return true;
        }
    }
    //Удаление
    void remove(Node* node, int data) {
        if (node == nullptr) {
            return;
        }
        else if (data < node->data) {
            remove(node->left, data);
        }
        else if (data > node->data) {
            remove(node->right, data);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                node = nullptr;
            }
            else if (node->left != nullptr && node->right != nullptr) {
                node->data = minNode(node->right)->data;
                remove(node->right, node->data);
            }
            else {
                node = (node->left != nullptr) ? node->left : node->right;
            }
        }
    }
    
    //минимальный узел по левой стороне
    Node* minNode(Node* node) {
        return (node->left != nullptr) ? minNode(node->left) : node;
    }
    // удаления всех узлов в бинарном дереве, начиная с заданного узла
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}
    
    //Вставка
    void insert(int data) {
        if (root == nullptr) {
            root = new Node(data);
        }
        else {
            insert(root, data);
        }
    }
    
    //Поиск
    bool search(int data) {
        return search(root, data);
    }

   
    //Удаление
    void remove(int data) {
        remove(root, data);
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }
};

class AVLTree {
private:
    Node* root;
    // Возвращение высоты
    int height(Node* node) {
        return node ? node->height : 0;
    }
    
    //Правка высоты
    void fixHeight(Node* node) {
        int hl = height(node->left);
        int hr = height(node->right);
        node->height = (hl > hr ? hl : hr) + 1;
    }
   
    //Правый и левый повороты
    Node* rotateRight(Node* node)
    {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        fixHeight(node);
        fixHeight(left);
        return left;
    }    
    Node* rotateLeft(Node* node)
    {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        fixHeight(node);
        fixHeight(right);
        return right;
    }
    
    //Фактор баланса
    int balanceFactor(Node* node) {
        return height(node->right) - height(node->left);
    }   
    //Балансировка
    Node* balance(Node* node)
    {
        fixHeight(node);
        if (balanceFactor(node) == 2)
        {
            if (balanceFactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2)
        {
            if (balanceFactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }
  

    Node* insert(Node* node, int data) {
        //Находим место для вставки числа
        if (node == nullptr)
            return new Node(data);
        if (data < node->data) {
            node->left = insert(node->left, data);
        }
        else
            node->right = insert(node->right, data);
        //отправляем в функцию балансировки
        return balance(node);
    }
    
    //Поиск по дереву
    bool search(Node* node, int data) {
        //Если меньше текущего узла то отправляемся в его левый узел иначе в правый
        if (node == nullptr) {
            return false;
        }
        else if (data < node->data) {
            return search(node->left, data);
        }
        else if (data > node->data) {
            return search(node->right, data);
        }
        else {
            return true;
        }
    }
    
    //Поиск минимума
    Node* findMin(Node* node)
    {
        return (node->left != nullptr) ? findMin(node->left) : node;
    }
    
    //Удаление минимального элемента
    // По свойству АВЛ-дерева у минимального элемента справа либо подвешен единственный узел, либо там пусто
    Node* removeMin(Node* node)
    {
        if (node->left == nullptr)
            return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }

    // Удаление узла
    Node* remove(Node* node, int data)
    {
        if (node == nullptr)
            return 0;
        if (data < node->data)
            node->left = remove(node->left, data);
        else if (data > node->data)
            node->right = remove(node->right, data);
        else
        {
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if (right == nullptr)
                return left;
            Node* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }

public:
    
    void insert(int data) {
        if (root == nullptr)
            root = new Node(data);
        else
            root = insert(root, data);
    }
  

    bool search(int data) {
        return search(root, data);
    }
    
    void remove(int data) {
        root = remove(root, data);
    }
};



vector<int> generateNums(int nums, bool sorted) {
    vector<int> values;
    for (int num = 0; num < nums; num++)
        values.push_back(1 + rand() % 1000);

    if (sorted)
        sort(values.begin(), values.end());
    return values;
}

void doForBinTree(ofstream& out, vector<int> values) {
    BinarySearchTree* bin_tree = new BinarySearchTree();
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    for (int num : values)
        bin_tree->insert(num);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff = end - start;
    out << sec_diff.count() << " ";

    start = chrono::high_resolution_clock::now();
    for (int k = 0; k < 1000; k++) {
        int num = 1 + rand() % 1000;
        bin_tree->search(num);
    }
    end = chrono::high_resolution_clock::now();
    sec_diff = end - start;
    out << sec_diff.count() << " ";

    start = chrono::high_resolution_clock::now();
    for (int k = 0; k < 1000; k++) {
        int num = 1 + rand() % 1000;
        bin_tree->remove(num);
    }
    end = chrono::high_resolution_clock::now();
    sec_diff = end - start;
    out << sec_diff.count() << endl;
    delete bin_tree;
}

void doForAVLTree(ofstream& out, vector<int> values) {
    AVLTree* avl_tree = new AVLTree();
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    for (int num : values)
        avl_tree->insert(num);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff = end - start;
    out << sec_diff.count() << " ";

    start = chrono::high_resolution_clock::now();
    for (int k = 0; k < 1000; k++) {
        int num = rand() % 1 + rand() % 1000;
        avl_tree->search(num);
    }
    end = chrono::high_resolution_clock::now();
    sec_diff = end - start;
    out << sec_diff.count() << " ";

    start = chrono::high_resolution_clock::now();
    for (int k = 0; k < 1000; k++) {
        int num = rand() % 1 + rand() % 1000;
        avl_tree->remove(num);
    }
    end = chrono::high_resolution_clock::now();
    sec_diff = end - start;
    out << sec_diff.count() << endl;
    delete avl_tree;
}

void doForVector(ofstream& out, vector<int> values) {
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    for (int k = 0; k < 1000; k++) {
        int num = rand() % 1 + rand() % 1000;
        find(values.begin(), values.end(), num);
    }
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff = end - start;
    out << sec_diff.count() << "\n";
}

int main()
{
    srand(time(0));
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    chrono::duration<double> sec_diff;

    ofstream bin_out;
    bin_out.open("BinTree.txt");
    ofstream avl_out;
    avl_out.open("AVLTree.txt");
    ofstream arr_search;
    arr_search.open("Search.txt");

    vector<int> values;
    for (int test = 1; test <= 10; test++) {
        bin_out << "Test " << test << endl;
        avl_out << "Test " << test << endl;
        arr_search << "Test " << test << endl;

        int nums = pow(2, 10 + test);
        bool checker = false;
        for (int i = 0; i < 20; i++) {
            vector<int> values = (i < 10) ? generateNums(nums, false) : generateNums(nums, true);

            if (i > 9 && !checker) {
                checker = true;
                bin_out << "Sorted\n";
                avl_out << "Sorted\n";
                arr_search << "Sorted\n";
            }
            doForBinTree(bin_out, values);
            doForAVLTree(avl_out, values);
            doForVector(arr_search, values);
        }
    }
    bin_out.close();
    avl_out.close();
    arr_search.close();
}
