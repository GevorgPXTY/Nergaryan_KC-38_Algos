#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
#include <chrono>

struct Pair
{
    int src, dest;

    Pair(int src, int dest) :
        src(src),
        dest(dest)
    {}
};

class Graph {
public:
    std::vector<int> vertex;
    std::vector<Pair> pairs;
    bool directed;


    Graph(bool directed) : directed(directed) {}
    //печать матрицы смежности, используя список вершин и пары ребер
    void printMatrixAdj() {
        std::cout << std::setw(5) << " ";
        for (int vert : vertex)
            std::cout << std::setw(5) << "x" + std::to_string(vert);
        std::cout << std::endl;
        for (int vert : vertex) {
            std::cout << std::setw(5) << "x" + std::to_string(vert);
            for (int next_vert : vertex) {
                bool check = false;
                for (Pair pair : pairs)
                    if (pair.src == vert && pair.dest == next_vert) {
                        std::cout << std::setw(5) << 1;
                        check = true;
                        break;
                    }

                if (!check)
                    std::cout << std::setw(5) << 0;
            }
            std::cout << std::endl;
        }
    }
    //печать матрицы инцидентности
    void printMatrixInc() {
        std::cout << std::setw(5) << " ";
        int index = 0;
        for (Pair pair : pairs)
            std::cout << std::setw(5) << "e" + std::to_string(index++);
        std::cout << std::endl;

        for (int vert : vertex) {
            std::cout << std::setw(5) << "x" + std::to_string(vert);
            for (Pair pair : pairs)
                if (!directed)
                    (vert == pair.src || vert == pair.dest) ? std::cout << std::setw(5) << 1 : std::cout << std::setw(5) << 0;
                else if (vert == pair.src)
                    std::cout << std::setw(5) << 1;
                else if (vert == pair.dest)
                    std::cout << std::setw(5) << -1;
                else
                    std::cout << std::setw(5) << 0;
            std::cout << std::endl;
        }
    }
    //печатает список смежности для данного графа
    void printListAdj() {
        for (int vert : vertex) {
            std::cout << std::setw(5) << "x" + std::to_string(vert) << std::setw(5) << "->";
            for (Pair pair : pairs)
                if (pair.src == vert)
                    std::cout << std::setw(5) << "x" + std::to_string(pair.dest);
            std::cout << std::endl;
        }
    }
    //выводит список пар вершин графа
    void printPairs() {
        for (Pair pair : pairs)
            std::cout << std::setw(3) << "x" + std::to_string(pair.src) << std::setw(4) << " -> " << std::setw(3) << "x" + std::to_string(pair.dest) << std::endl;
    }
};

struct Vertex
{
private:
    //максимальное число связей, которые может иметь данная вершина
    int max_in_out;
    int max_out;
public:
    //текущее число связей, которые имеет данная вершина. `num_in_out` обозначает общее число входящих и исходящих связей, а `num_out` - число исходящих связей
    int num_in_out;
    int num_out;
    //вектор, хранящий индексы вершин, с которыми имеются связи
    std::vector<int> bounds_with_vert;

    //Конструктор для создания новой вершины. В качестве аргументов принимает индекс вершины, максимальное число входящих и исходящих связей.
    Vertex() {};

    Vertex(int index, int max_in_out, int max_out) {
        bounds_with_vert.push_back(index);
        this->max_in_out = max_in_out;
        this->max_out = max_out;

        num_in_out = 0;
        num_out = 0;
    }
    //Метод для проверки, можно ли добавить еще одну связь к данной вершине. 
    //Если это возможно, то метод возвращает случайную вершину графа, с которой еще нет связи. В противном случае метод возвращает -1
    int checkForAdd(int num_vert) {
        int next_vert = -1;
        if (max_in_out > num_in_out && max_out > num_out && bounds_with_vert.size() != num_vert) {
            next_vert = 0 + rand() % (num_vert);
            while (std::find(bounds_with_vert.begin(), bounds_with_vert.end(), next_vert) != bounds_with_vert.end())
                next_vert = 0 + rand() % (num_vert);
        }
        return next_vert;
    }
    //Метод для добавления новой связи к данной вершине. 
    //Принимает индекс вершины, с которой требуется добавить связь, и указатель на вершину, с которой происходит соединение.
    void addNewPair(int index, Vertex* vert_with) {
        num_in_out++;
        num_out++;
        bounds_with_vert.push_back(index);
        vert_with->num_in_out++;
    }
};


/*
Метод генерирует случайный неориентированный/ориентированный граф с заданным числом вершин и ребер.
Метод также определяет максимальное число выходящих ребер у каждой вершины.
Количество входящих ребер для каждой вершины генерируется случайно в диапазоне от 0 до max_in_out.
Граф создается на основе списка ребер.
*/
void generationGraph(Graph* graph, int max_vert, int max_pairs, int max_out, bool directed, int max_in_out, int min_vert = 2, int min_pairs = 0) {
    int num_vert = min_vert + rand() % (max_vert - min_vert + 1);
    for (int i = 0; i < num_vert; i++)
        graph->vertex.push_back(i);

    if (min_pairs = 0)
        min_pairs = num_vert;

    int num_pairs = min_pairs + rand() % (max_pairs - min_pairs + 1);

    if (num_pairs > num_vert * (num_vert - 1) / 2)
        num_pairs = num_vert * (num_vert - 1) / 2;
    std::map<int, Vertex> vertexies;
    int checker_for_pairs = 0;
    for (int vert : graph->vertex)
        vertexies[vert] = Vertex(vert, max_in_out, max_out);


    int current_num_pairs = 0;
    while (current_num_pairs < num_pairs) {
        int vertex = 0 + rand() % (num_vert + 1);
        int ind_next = vertexies[vertex].checkForAdd(num_vert);
        if (ind_next != -1) {
            current_num_pairs++;
            graph->pairs.push_back(Pair(vertex, ind_next));
            vertexies[vertex].addNewPair(ind_next, &vertexies[ind_next]);
            if (!directed) {
                vertexies[ind_next].bounds_with_vert.push_back(vertex);
                vertexies[ind_next].num_out++;
                graph->pairs.push_back(Pair(ind_next, vertex));
            }
        }
    }
}

void deepFirstSearchBegining(Graph* graph, int from, int final);
void breadthFirstSearch(Graph* graph, int from, int final);

int main()
{
    srand(time(NULL));
    Graph* graph = new Graph(false);
    generationGraph(graph, 15, 30, 10, false, 10, 12, 15);
    graph->printMatrixAdj();
    graph->printMatrixInc();
    graph->printListAdj();
    graph->printPairs();
    breadthFirstSearch(graph, 1, 5);
    deepFirstSearchBegining(graph, 1, 5);
    std::cout << "-----------------------------\n";
    for (int i = 0; i < 10; i++) {
        graph = new Graph(true);
        generationGraph(graph, 10 * (i + 1), 10 * ((i + 1) * 10) / 2, 10 * ((i + 1) * 10) / 2, true, 10 * ((i + 1) * 10) / 2, 10 * (i + 1) - 1, 10 * ((i + 1) * 10) / 4);

        int from = rand() % (graph->vertex.size());
        int to = rand() % (graph->vertex.size());
        while (to == from)
            to = rand() % (graph->vertex.size());
        std::cout << "Deep search\n";
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        deepFirstSearchBegining(graph, from, to);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sec_diff = end - start;
        std::cout << "Time: " << sec_diff.count() << " sec." << std::endl;
        std::cout << "Breadth search\n";
        start = std::chrono::high_resolution_clock::now();
        breadthFirstSearch(graph, from, to);
        end = std::chrono::high_resolution_clock::now();
        sec_diff = end - start;
        std::cout << "Time: " << sec_diff.count() << " sec." << std::endl;
        std::cout << "-----------------------------\n";
    }
}

struct DFSVert
{
    int index;
    bool was_checked;
    std::vector<DFSVert*> pair_vert;

    DFSVert(int index) :index(index), was_checked(false) {}
};

std::string deepFirstSearch(DFSVert* vert, int final, std::string route_before) {
    if (vert->index == final)
        return route_before;

    vert->was_checked = true;
    std::vector<std::string> route;
    bool checker = false;

    for (DFSVert* next_vert : vert->pair_vert) {
        if (!next_vert->was_checked) {
            route.push_back(deepFirstSearch(next_vert, final, route_before + "->" + std::to_string(next_vert->index)));
            checker = true;
        }
    }

    if (!checker) {
        return "-";
    }

    std::string final_str = "-";

    for (std::string item : route) {
        std::string str = item;
        if (str.back() != '-' && (str.length() < final_str.length() || final_str == "-")) {
            final_str = item;
        }
    }
    return final_str;
}

void deepFirstSearchBegining(Graph* graph, int from, int final) {
    std::vector<DFSVert> vertexies;
    for (int vert : graph->vertex)
        vertexies.push_back(DFSVert(vert));
    std::sort(graph->pairs.begin(), graph->pairs.end(), [](Pair left, Pair right) {
        if ((left.src < right.src) || (left.src == right.src && left.dest < right.dest))
            return true;
        return false;
    });
    for (Pair pair : graph->pairs)
        vertexies[pair.src].pair_vert.push_back(&vertexies[pair.dest]);

    std::string route = deepFirstSearch(&vertexies[from], final, std::to_string(from));
    if (route.back() == '-')
        std::cout << "Not Found\n";
    else
        std::cout << "Was found: " << route << std::endl;
}

struct BFSVert
{
    std::string road_before;
    int index;
    bool was_open;
    std::vector<BFSVert*> pair_vert;

    BFSVert(int index) :index(index), was_open(false), road_before("") {}
};

void breadthFirstSearch(Graph* graph, int from, int final) {
    std::vector<BFSVert> vertexies;
    for (int vert : graph->vertex)
        vertexies.push_back(BFSVert(vert));
    for (Pair pair : graph->pairs)
        vertexies[pair.src].pair_vert.push_back(&vertexies[pair.dest]);

    std::queue<BFSVert> queue_road;
    queue_road.push(vertexies[from]);

    while (!queue_road.empty()) {
        if (queue_road.front().index != final) {
            if (!queue_road.front().pair_vert.empty())
                for (BFSVert* vert : queue_road.front().pair_vert) {
                    if (!vert->was_open) {
                        vert->road_before += queue_road.front().road_before + std::to_string(queue_road.front().index) + "->";
                        vert->was_open = true;
                        queue_road.push(*vert);
                    }
                }
            queue_road.pop();
        }
        else {
            std::cout << "Was found: "
                << queue_road.front().road_before << final << std::endl;
            queue_road.pop();
            return;
        }
    }
    std::cout << "Not found\n";
}
