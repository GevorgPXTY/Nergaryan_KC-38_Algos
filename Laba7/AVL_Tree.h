#pragma once
#include<iostream>

#include <climits>
#include <fstream>

using namespace std;
class AVL_Tree
{
    struct Node
    {
        int data;
        Node* left;
        Node* right;
        int height;
    };

    Node* root;

    void makeEmpty(Node* t)
    {
        if (t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    Node* insert(int x, Node* t)
    {
        if (t == NULL)
        {
            t = new Node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
        {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->data)
        {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    Node* singleRightRotate(Node*& t)
    {
        if (t->left != NULL) {
            Node* u = t->left;
            t->left = u->right;
            u->right = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(u->left), t->height) + 1;
            return u;
        }
        return t;
    }
    Node* singleLeftRotate(Node*& t)
    {
        if (t->right != NULL) {
            Node* u = t->right;
            t->right = u->left;
            u->left = t;
            t->height = max(height(t->left), height(t->right)) + 1;
            u->height = max(height(t->right), t->height) + 1;
            return u;
        }
        return t;
    }

    Node* doubleLeftRotate(Node*& t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    Node* doubleRightRotate(Node*& t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    Node* findMin(Node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    Node* findMax(Node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    Node* remove(int x, Node* t)
    {
        Node* temp;

        if (t == NULL)
            return NULL;

        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);

        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }

        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }
        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        if (height(t->left) - height(t->right) == -2)
        {
            // right right case
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        else if (height(t->right) - height(t->left) == 2)
        {
            // left left case
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(Node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(Node* t)
    {
        if (t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    int maxDepth(Node* t)
    {
        if (t == NULL) return 0;
        return max(maxDepth(t->left), maxDepth(t->right)) + 1;
    }
    void inorder(Node* t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    Node* find(Node* t, int x) {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        else
            return t;
    }
    void printAllDepth(Node* t) {
        ofstream out4("DepthAVL.txt", ios::app);
        if (t == NULL) return;
        if (out4.is_open()) // открываем файл для записи
        {
            out4 << t->data << "        " << t->height + 1 << endl;
        }

        printAllDepth(t->left);
        printAllDepth(t->right);
    }
public:
    AVL_Tree()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }
    int find_Depth() {
        int max_size = 0;
        return maxDepth(root);
    }
    void display()
    {
        inorder(root);
        cout << endl;
    }
    void printAllDepth(int n) {
        ofstream out5("DepthAVL.txt", ios::app);
        if (out5.is_open()) // открываем файл для записи
        {
            out5 << "Цикл №" << n + 1 << endl;
        }
        printAllDepth(root);
    }
    void search(int x) {
        root = find(root, x);
    }
};

