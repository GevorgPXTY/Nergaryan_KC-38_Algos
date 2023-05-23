import random
import networkx as nx
from collections import deque
import timeit
import matplotlib.pyplot as plt
import scipy


# Класс для создания различных графов
class GraphGen:
    # Конструктор класса
    def __init__(self, min_nodes, max_nodes, min_edges, max_edges, max_edges_per_node, min_edges_per_node,
                 is_directed=False, max_incoming_edges=None, max_outgoing_edges=None):
        self.min_nodes = min_nodes
        self.max_nodes = max_nodes
        self.min_edges = min_edges
        self.max_edges = max_edges
        self.max_edges_per_node = max_edges_per_node
        self.is_directed = is_directed
        self.max_incoming_edges = max_incoming_edges
        self.max_outgoing_edges = max_outgoing_edges
        self.min_edges_per_node = min_edges_per_node

    # Метод на получение матрицы смежности графа selected_graph
    def adjacency_matrix(self, selected_graph):
        return nx.adjacency_matrix(selected_graph).todense()

    # Метод на генерацию графа (рандомного)
    def generate_graph(self):
        # генерируем случайное число узлов
        n = random.randint(self.min_nodes, self.max_nodes)
        # генерируем случайное число ребер
        m = random.randint(self.min_edges, min(self.max_edges, n * (n - 1) // 2))
        # создаем граф, в зависимости от параметра будет он ориентированный или нет
        new_graph = nx.Graph() if not self.is_directed else nx.DiGraph()
        # создаем список узлов
        nodes = list(range(n))
        # добавляем узлы в граф
        new_graph.add_nodes_from(nodes)
        edges = []
        max_degrees = [0] * n
        # проходим по всем узлам в графе
        for i in range(n):
            # случайное количество ребер, которые будут присоединены к узлу i
            k = random.randint(self.min_edges_per_node, min(self.max_edges_per_node, n - 1))
            # если граф не ориентированный, учитываем уже имеющиеся ребра
            if not self.is_directed:
                k = min(k, n - 1 - len(new_graph.adj[i]))
            # выбираем случайные узлы для присоединения ребер к узлу i
            j_candidates = set(nodes) - set(new_graph.adj[i]) - set([i])
            j_candidates = random.sample(list(j_candidates), min(len(j_candidates), k))
            # проходим по всем узлам j, которые были выбраны для присоединения ребер к узлу
            for j in j_candidates:
                # если узел j еще не достиг максимального количества входящих и исходящих ребер
                if (self.max_incoming_edges is None or new_graph.in_degree(j) < self.max_incoming_edges) and (
                        self.max_outgoing_edges is None or new_graph.out_degree(i) < self.max_outgoing_edges):
                    # добавляем ребро (i, j, weight)
                    edges.append((i, j, random.randint(1, 20)))
                    # увеличиваем степени вершин i и j
                    max_degrees[i] += 1
                    max_degrees[j] += 1
        # перемешиваем список ребер и добавляем первые m ребер в граф
        random.shuffle(edges)
        new_graph.add_weighted_edges_from(edges[:m])
        # находим максимальные входящую и исходящую степень вершин (только для ориентированных графов)
        max_in_degrees = max_out_degrees = 0
        for i in range(n):
            if self.is_directed:
                max_in_degrees = max(max_in_degrees, new_graph.in_degree(i))
                max_out_degrees = max(max_out_degrees, new_graph.out_degree(i))
            else:
                max_degrees[i] = new_graph.degree(i)

        return new_graph, {
            'максимальное количество узлов в графе': n,
            'минимальное количество ребер в графе': self.min_edges,
            'максимальное количество ребер в графе': self.max_edges,
            'максимальное количество ребер к каждому узлу': self.max_edges_per_node,
            'Направленый граф': self.is_directed,
            # максимальное количество входящих ребер, которые могут быть присоединены к каждому узлу (только для ориентированных графов).
            'максимальное количество входящих ребер, присоединяемых к узлам': self.max_incoming_edges,
            # максимальное количество исходящих ребер, которые могут быть присоединены к каждому узлу (только для ориентированных графов).
            'максимальное количество исходящих ребер, присоединяемых к узлам': self.max_outgoing_edges,
            'максимальная степень вершины в графе': max(max_degrees),
            'максимальная входящая степень вершины': max_in_degrees,
            'максимальная исходящая степень вершины': max_out_degrees,
            'минимальная степень вершины в графе': min(max_degrees),

        }

    # Метод на генерацию случайных графов в размере num_graphs
    # каждый последующий граф  с возрастающим количеством вершин и ребер
    def generate_graphs(self, num_graphs):
        graphs = []
        for i in range(num_graphs):
            graph, metadata = self.generate_graph()
            graphs.append((graph, metadata))
        return graphs


# Функция на вывод информации графика (вывод матрицы смежности,
# вывод минимального остового дерева методом Прима и замер времени)
def primAlg(graphs_list, graph_gen, graphs_times):
    for i, (graph, metadata) in enumerate(graphs_list):
        start = random.choice(list(graph.nodes()))  # выбираем рандомно начальную вершину
        end = random.choice(list(graph.nodes()))  # выбираем рандомно конечную вершину
        print('========================================================================')
        print(f"Граф {i + 1}:")
        print("------------------------------------------------")
        print("Матрица смежности:")
        print(graph_gen.adjacency_matrix(graph))
        print("--------------------------------------------------")
        print("Алгоритм Прима (минимальное остовое дерево):")
        prim_start = timeit.default_timer()

        # Алгоритм Прима
        #
        # Инициализируйте алгоритм, выбрав исходную вершину
        # Найдите ребро с минимальным весом, подключенное к исходному узлу и другому узлу, и добавьте его в дерево
        # Продолжайте повторять этот процесс, пока мы не найдем минимальное связующее дерево

        # Передаем матрицу смежности в переменную
        matr = graph_gen.adjacency_matrix(graph)
        selected_node = [0] * len(matr)
        no_edge = 0
        selected_node[0] = True
        print("Edge : Weight\n")
        # Пока длина остового дерева не равна размеру графа, выполняем цикл
        while (no_edge < len(matr) - 1):
            a = 0
            b = 0
            minimum = 999
            for m in range(len(matr)):
                if selected_node[m]:
                    for n in range(len(matr)):
                        if ((not selected_node[n]) and matr[m][n]):
                            # Если вершина не была выбрана, добавляем ее
                            # и меняем минимальное значение
                            if minimum > matr[m][n]:
                                minimum = matr[m][n]
                                a = m
                                b = n
            print(str(a) + "-" + str(b) + ":" + str(matr[a][b]))
            selected_node[b] = True
            no_edge += 1

        prim_end = timeit.default_timer()
        prim_time = prim_end - prim_start
        graphs_times.append(prim_time)
        print('ВРЕМЯ ВЫПОЛНЕНИЯ АЛГОРИТМА: ', prim_time)
        print("--------------------------------------------------")
        print("Доп данные по графу:")
        print(metadata)
        print("================================================================\n")


# Функция на нахождение среднего значения
def findAvg(list_of_times):
    summ = 0
    for elem in list_of_times:
        summ += elem
    return summ / len(list_of_times)


# Списки для записи времени (для построения графика)
min_prim_times = []
max_prim_times = []
avg_prim_times = []

# Создаем генераторы для графов из [10,20,50,100] вершин
generator_10nodes = GraphGen(min_nodes=10, max_nodes=10, min_edges=40, max_edges=45, max_edges_per_node=9,
                             min_edges_per_node=3)
generator_20nodes = GraphGen(min_nodes=20, max_nodes=20, min_edges=185, max_edges=190, max_edges_per_node=9,
                             min_edges_per_node=4)
generator_50nodes = GraphGen(min_nodes=50, max_nodes=50, min_edges=1220, max_edges=1225, max_edges_per_node=20,
                             min_edges_per_node=10)
generator_100nodes = GraphGen(min_nodes=100, max_nodes=100, min_edges=4930, max_edges=4950, max_edges_per_node=30,
                              min_edges_per_node=20)

# Генерируем 5 рандомных графов c разным кол-вом вершин
graphs_10 = generator_10nodes.generate_graphs(5)
graphs_20 = generator_20nodes.generate_graphs(5)
graphs_50 = generator_50nodes.generate_graphs(5)
graphs_100 = generator_100nodes.generate_graphs(5)

# Списки для хранения времени  с графов (алгоритма Прима)
prim_times_10 = []
prim_times_20 = []
prim_times_50 = []
prim_times_100 = []

# Производим работу алгоритма Прима с выводом данных
primAlg(graphs_10, generator_10nodes, prim_times_10)
primAlg(graphs_20, generator_20nodes, prim_times_20)
primAlg(graphs_50, generator_50nodes, prim_times_50)
primAlg(graphs_100, generator_100nodes, prim_times_100)

# Добавляем значения лучших, худших и средних значений по времени для графов
min_prim_times.extend([min(prim_times_10), min(prim_times_20), min(prim_times_50), min(prim_times_100)])
max_prim_times.extend([max(prim_times_10), max(prim_times_20), max(prim_times_50), max(prim_times_100)])
avg_prim_times.extend([findAvg(prim_times_10), findAvg(prim_times_20), findAvg(prim_times_50), findAvg(prim_times_100)])

# Построение графика для сравнения алгоритма прима для графов с разным кол-вом вершин
plt.title('График на сравнение резльтатов нахождния остового дерева (Прима)')
plt.plot([10, 20, 50, 100], min_prim_times, label="График лучшего времени")
plt.plot([10, 20, 50, 100], max_prim_times, label="График худшего времени")
plt.plot([10, 20, 50, 100], avg_prim_times, label="График среднего времени")
plt.xlabel("Кол-во узлов")
plt.ylabel("Время, сек.")
plt.legend()
plt.show()
