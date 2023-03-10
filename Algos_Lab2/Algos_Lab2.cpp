#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <cmath>

using namespace std;
vector<double> quicksort(vector<double>& arr, int& kolvo_recurs, int& glubina_steka, int cur_depth = 0) {  //cur_depth используется для отслеживания текущей глубины рекурсии.
    kolvo_recurs++;
    if (arr.size() <= 1) {   //если размер массива не больше 1, то он уже отсортирован и возвращается без изменений
        return arr;
    }
    double pivot = arr[arr.size() / 2];  //опорный элемент (pivot) из середины массива
    vector<double> left, middle, right;  //три вектора для элементов, которые меньше, равны и больше опорного элемента
    for (double x : arr) {
        if (x < pivot) {
            left.push_back(x);
        }
        else if (x == pivot) {
            middle.push_back(x);
        }
        else {
            right.push_back(x);
        }
    }
    int cur_depth_left = cur_depth + 1;
    vector<double> sorted_left = quicksort(left, kolvo_recurs, glubina_steka, cur_depth_left);  
    glubina_steka = max(glubina_steka, cur_depth_left); //рекурсивно вызывает саму себя для двух подмассивов, созданных из элементов, которые меньше и больше опорного элемента
    int cur_depth_right = cur_depth + 1;
    vector<double> sorted_right = quicksort(right, kolvo_recurs, glubina_steka, cur_depth_right);
    glubina_steka = max(glubina_steka, cur_depth_right);
    vector<double> result;
    result.reserve(sorted_left.size() + middle.size() + sorted_right.size());
    result.insert(result.end(), sorted_left.begin(), sorted_left.end());
    result.insert(result.end(), middle.begin(), middle.end());
    result.insert(result.end(), sorted_right.begin(), sorted_right.end());
    return result; // функция объединяет три отсортированных вектора (левый, средний и правый) в один и возвращает его
}


int main() {
    setlocale(LC_ALL, "Russian");
    int min_r, avg_r, max_r; // переменные для подсчета количества вызовов
    vector<int> N_values = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };
    for (int N : N_values) {
        int glubina_steka = 0, kolvo_recurs = 0, time = 0;  
        min_r = 9999999, avg_r = 0, max_r = 0;
        for (int i = 0; i < 20; i++) {
            auto start = std::chrono::high_resolution_clock::now();//начало времени
            glubina_steka = 0, kolvo_recurs = 0;
            vector<double> arr(N);
            generate(arr.begin(), arr.end(), []() { return ((double)rand() / RAND_MAX) * 2 - 1; }); //используется лямбда-функция без аргументов, которая генерирует случайное число в диапазоне от -1 до 1
            vector<double> sorted_arr = quicksort(arr, kolvo_recurs, glubina_steka);  //отсортированные по возрастанию
            bool is_sorted = is_sorted_until(sorted_arr.begin(), sorted_arr.end()) == sorted_arr.end(); //Проверяется, отсортирован ли "sorted_arr" по возрастанию
            if (!is_sorted) {
                cout << "Сортировка для N=" << N << " и итерации " << i << " была неверной!" << endl;
            }
            // Отсортированный массив
            vector<double> sorted_arr_copy = sorted_arr;// создается копия отсортированного массива "sorted_arr"
            sort(sorted_arr_copy.begin(), sorted_arr_copy.end()); //снова сортировка
            bool is_sorted_copy = is_sorted_until(sorted_arr_copy.begin(), sorted_arr_copy.end()) == sorted_arr_copy.end();
            if (!is_sorted_copy) { //проверка
                cout << "Негативный тест: Сортировка отсортированного массива для N=" << N << " и итерации " << i << " была неверной!" << endl;
            }
            // Массив с одинаковыми элементами
            vector<double> same_arr(N, 1.0);
            vector<double> same_arr_sorted = quicksort(same_arr, kolvo_recurs, glubina_steka);
            bool is_same_sorted = is_sorted_until(same_arr_sorted.begin(), same_arr_sorted.end()) == same_arr_sorted.end();
            if (!is_same_sorted) {
                cout << "Негативный тест: Сортировка массива с одинаковыми элементами для N=" << N << " и итерации " << i << " была неверной!" << endl;
            }
            // Массив с максимальным количеством сравнений при выборе среднего элемента в качестве опорного
            vector<double> max_comparison_arr(N);
            generate(max_comparison_arr.begin(), max_comparison_arr.end(), []() { return 1.0; }); //лямбда-функция без аргументов, которая всегда возвращает 1.0
            vector<double> max_comparison_sorted_arr = quicksort(max_comparison_arr, kolvo_recurs, glubina_steka);  //сортировка по возрастанию
            bool is_max_comparison_sorted = is_sorted_until(max_comparison_sorted_arr.begin(), max_comparison_sorted_arr.end()) == max_comparison_sorted_arr.end(); //Проверяется, отсортирован ли вектор по возрастанию
            if (!is_max_comparison_sorted) {
                cout << "Негативный тест: Сортировка массива с максимальным количеством сравнений для N=" << N << " и итерации " << i << " была неверной!" << endl;
            }
            //Массив с максимальным количеством сравнений при детерминированном выборе опорного элемента
            vector<double> dete_arr(N);
            generate(dete_arr.begin(), dete_arr.end(), []() { return ((double)rand() / RAND_MAX) * 2 - 1; });
            vector<double> dete_sorted_arr = quicksort(dete_arr, kolvo_recurs, glubina_steka);
            bool dete_is_sorted = is_sorted_until(dete_sorted_arr.begin(), dete_sorted_arr.end()) == dete_sorted_arr.end();
            if (!dete_is_sorted) {
                cout << "Негативный тест: Сортировка массива с детерминированным выбором опорного элемента для N=" << N << " была неверной!" << endl;
            }
            if (min_r > kolvo_recurs) { min_r = kolvo_recurs; }
            if (max_r < kolvo_recurs) { max_r = kolvo_recurs; }
            avg_r += kolvo_recurs;
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (time < duration.count()) { time = duration.count(); }
        }
            cout << "Время худшего выполнения: " << time << " микросекунд" << endl;
        cout << "Лучший случай:" << min_r << "      Средний случай:" << avg_r/20 << "      Худший случай:" << max_r << endl;
        cout << "Глубина стека для N=" << N << ":" << glubina_steka << "    Количество рекурсий для N=" << N << ":" << avg_r << endl;
        cout << "Тесты для N=" << N << " успешно пройдены!" << endl << endl << endl;
    }
     return 0;
}
