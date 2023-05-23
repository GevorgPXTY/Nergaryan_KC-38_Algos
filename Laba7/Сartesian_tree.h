#include <iostream>
#include <cstdlib>
#include<vector>

#include <climits>
#include <fstream>

using namespace std;

#pragma once
class Сartesian_tree
{
   
    struct Node {
        int key, prior, size = 1;
        //              ^ размер поддерева
        Node* l = 0, * r = 0;
       Node(int _key) { key = _key, prior = rand(); }
    };
    Node* root;
    
    int get_size(Node* t)
    {
        if (t == nullptr) return 0;// Полагаем размер пустого дерева равным нулю.
        return t->size; // Считаем, что размер поддерева поддерживается корректно
    }

  
    void upd(Node* t)
    {
        if (t == nullptr) return;
        t->size = 1 + get_size(t->l) + get_size(t->r);
    }
    
    Node* merge(Node* l, Node* r) {
        if (!l) return r;
        if (!r) return l;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            upd(l);
            return l;
        }
        else {
            r->l = merge(l, r->l);
            upd(r);
            return r;
        }
    }

    typedef pair<Node*, Node*> Pair;

    Pair split(Node* p, int k) {
        if (!p) return { 0, 0 };
        if (get_size(p->l) + 1 <= k) {// + 1 
            Pair q = split(p->r, k - get_size(p->l) - 1);
            //                   ^ правый сын не знает количество вершин слева от него
            p->r = q.first;
            upd(p);
            return { p, q.second };
        }
        else {
            Pair q = split(p->l, k);
            p->l = q.second;
            upd(p);
            return { q.first, p };
        }
    }
  
    /*void  add(Node* v, int k) {
        Pair q = split(root, k);
        root = merge(q.first, merge(v, q.second));
    }*/
    Node* insert(int x, Node* result) {
        Node* t = new Node(x);
        Pair q = split(result, x);
        //return merge(q.first, merge(t, q.second));
        return merge(merge(q.first,t), q.second);
    }
    Node* remove(int x, Node* result) {
        Pair q1 = split(result, x ); //x+1
        Pair q2 = split(q1.first, x);//x-1
        return merge(q2.first, q1.second);
    }
   
    // Получение k-го элемента, по сути, аналогично получению k-й порядковой статистике в
// декартовом дереве по явному ключу
    int find_size(Node* t, int pos)
    {
        int my_idx = get_size(t->l);
        if (pos < my_idx)
        {
            return find_size(t->l, pos);
        }
        else if (pos == my_idx)
        {
            //return t->key;
            return get_size(t);
        }
        else
        {
            return find_size(t->r, pos - my_idx - 1);
        }
    }
    Node* find(Node* t, int x) {
        if (t == NULL) return NULL;
        else if (x < t->key)
            return find(t->l, x);
        else if (x > t->key)
            return find(t->r, x);
        else
            return t;
    }
    int maxDepth(Node* t)
    {
        if (t == NULL) return 0;
        return max(maxDepth(t->l), maxDepth(t->r)) + 1;
    }
    void printAllDepth(Node* t, int size) {
        ofstream out4("Depth.txt", ios::app);
        if (t == NULL) return;
        if (out4.is_open()) // открываем файл для записи
        {
            out4 << t->key << "        " << size + 1 << endl;
        }

         printAllDepth(t->l,size + 1);
         printAllDepth(t->r,size + 1);
    }
    // Печать всего дерева. Просто обходим наше дерево как обычное бинарное дерево поиска,
// вместо того, чтобы каждый раз пользоваться get_value.
    void print_tree(Node* t)
    {
        if (t == nullptr) { return; }
        print_tree(t->l);
        cout << t->key << " ";
        print_tree(t->r);
    }

public:
    Сartesian_tree()
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
        //return maxDepth(root, max_size);
        return maxDepth(root);
    }
    void printAllDepth(int n) {
        ofstream out4("Depth.txt", ios::app);
        if (out4.is_open()) // открываем файл для записи
        {
            out4 <<"Цикл №" << n + 1<< endl;
        }
        printAllDepth(root,0);
    }
    void search(int x) {
        root = find(root, x);
    }
    void display()
    {
        print_tree(root);
        cout << endl;
    }
};

