#include<iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include"Сartesian_tree.h"
#include"AVL_Tree.h"
#include<vector>

using namespace std;

//Генерируем массив
void generate(int* arr, int N, bool random) {

    cout << "Post 1.вектор" << endl;
    for (int i = 0; i < N; i++) {
        if (random) {
            int ind = 0 + rand() % (N - 1);
            arr[i] = ind;
        }
        else
            arr[i] = i;
    }
}

//Вставка массива в деревья
void createTree(Сartesian_tree myTree, AVL_Tree myAVL, int N, int* arr, int n, int i) {
    ofstream out1("Create.txt", ios::app);

    for (int i = 0; i < N; i++) {
        myTree.insert(arr[i]);
        myAVL.insert(arr[i]);
    }
    if (out1.is_open())
    {
        out1 << n + 1 << ")     " << myTree.find_Depth() << "                      " << myAVL.find_Depth() << endl;
    }
    cout << N << endl;
    if ((i == 7) && (n == 49)) {
        myTree.printAllDepth(n);
        myAVL.printAllDepth(n);
    }
}

//теперь вставка элемента в деревья
void insertInTree(Сartesian_tree myTree, AVL_Tree myAVL, int N, int n) {
    int num;
    ofstream out("Insert.txt", ios::app);
    chrono::high_resolution_clock::time_point start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        num = N + rand() % (N + 1000);
        myTree.insert(num);
    }
    chrono::high_resolution_clock::time_point end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff1 = end1 - start1;

    chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        num = N + rand() % (N + 1000);
        myAVL.insert(num);
    }
    chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff2 = end2 - start2;

    if (out.is_open())
    {
        out << n + 1 << ")     " << sec_diff1.count() << "                      " << sec_diff2.count() << endl;
    }
}


//Поиск элемента
void findElements(Сartesian_tree myTree, AVL_Tree myAVL, int N, int n) {
    int num;
    ofstream out2("Search.txt", ios::app);
    chrono::high_resolution_clock::time_point start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        num = 0 + rand() % (N - 1);
        myTree.search(num);
    }
    chrono::high_resolution_clock::time_point end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff1 = end1 - start1;

    chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        num = 0 + rand() % (N - 1);
        myAVL.search(num);

    }
    chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff2 = end2 - start2;

    if (out2.is_open())
    {
        out2 << n + 1 << ")     " << sec_diff1.count() << "           " << sec_diff2.count() << endl;
    }
}

//Удаение элемента
void removeTree(Сartesian_tree myTree, AVL_Tree myAVL, int* arr, int N, int n) {

    ofstream out3("Remove.txt", ios::app);
    chrono::high_resolution_clock::time_point start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        myTree.remove(arr[N - i]);
    }
    chrono::high_resolution_clock::time_point end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff1 = end1 - start1;

    chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        myAVL.remove(arr[N - i]);
    }
    chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> sec_diff2 = end2 - start2;
    if (out3.is_open()) //  открываем файл для записи
    {
        out3 << n + 1 << ")      " << sec_diff1.count() << "              " << sec_diff2.count() << endl;
    }
}

//Тесты
void tests(int test, bool random) {
    //открываем поток записи в наш файл (с возможностью дописать)
    ofstream out1("Create.txt", ios::app);
    ofstream out("Insert.txt", ios::app);
    ofstream out2("Search.txt", ios::app);
    ofstream out3("Remove.txt", ios::app);
    ofstream out4("Depth.txt", ios::app);
    ofstream out5("DepthAVL.txt", ios::app);

    for (int i = 0; i < test; i++) {
        if (out.is_open() && out2.is_open() && out3.is_open() && out1.is_open() && out4.is_open() && out5.is_open()) //открываем файл для записи
        {
            out << "\n" << "Test: " << i << endl;
            out1 << "\n" << "Test: " << i << endl;
            out2 << "\n" << "Test: " << i << endl;
            out3 << "\n" << "Test: " << i << endl;
            out4 << "\n" << "Test: " << i << endl;
            out5 << "\n" << "Test: " << i << endl;
        }
        if (out1.is_open())
        {
            out1 << "\nDepth: \n     Сartesian                                  AVL" << endl;
        }
        if (out.is_open())
        {
            out << "\nInsert: \n     Сartesian                                  AVL" << endl;
        }
        if (out2.is_open())
        {
            out2 << "\nSearch: \n     Сartesian                      AVL" << endl;
        }
        if (out3.is_open())
        {
            out3 << "\n Remove : \n     Сartesian                   AVL " << endl;
        }
        if (out4.is_open())
        {
            out4 << "\nDepth: \n  " << endl;
        }
        if (out5.is_open())
        {
            out5 << "\nDepthAVL: \n " << endl;
        }
        int N = pow(2, 10 + i);
        for (int n = 0; n < 50; n++) {
            cout << "Post 1" << endl;
            int* arr = new int[N];
            Сartesian_tree myTree;
            AVL_Tree myAVL;
            cout << "Post 1.6" << endl;
            generate(arr, N, random);
            cout << "Post 2.0" << endl;
            createTree(myTree, myAVL, N, arr, n, i);
            cout << "Post 2" << endl;
            insertInTree(myTree, myAVL, N, n);
            cout << "Post 3" << endl;
            findElements(myTree, myAVL, N, n);
            cout << "Post 4" << endl;
            removeTree(myTree, myAVL, arr, N, n);
            cout << "Post 5" << endl;

            delete(arr);
        }

    }
}
int main()
{

    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    tests(8, true);

    cout << "Успех" << endl;
}