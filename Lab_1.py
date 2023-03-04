import random
import time
import matplotlib.pyplot as plt

plt.style.use('dark_background')

k = 20  # кол-во прогонов
l = 7  # заканчиваем на 64000 (степени 2)
n = 1000
vector1000 = []  # пустые массивы для записи времени интерации
vector2000 = []  # будущие значения у
vector4000 = []
vector8000 = []
vector16000 = []
vector32000 = []
vector64000 = []
f = open('time.txt', 'w+')  # создаем/открываем пустой файл
f.close()
# массива из случайных чисел от -1.0 до 1.0 k-раз для каждого n
for l in range(l):
    f = open('time.txt', 'a')  # записываем в файл с каким n работаем
    c = "   Count " + str(n) + "\n"
    f.write(c)
    f.close()
    for i in range(k):
        vector = []
        for i in range(n):
            vector.append(random.uniform(-1, 1))  # массив от -1 до 1
        start = time.time()  # начало таймера
        for i in range(n - 1):  # метод пузырька
            for j in range(n - i - 1):
                if vector[j] > vector[j + 1]:
                    vector[j], vector[j + 1] = vector[j + 1], vector[j]
        end = time.time()  # конец таймера
        finaltime = (end - start) * 10 ** 3
        # в зависимости от n на текущей итерации заносим значения времени в соотв.массив
        if n == 1000:
            vector1000.append(finaltime)
        elif n == 2000:
            vector2000.append(finaltime)
        elif n == 4000:
            vector4000.append(finaltime)
        elif n == 8000:
            vector8000.append(finaltime)
        elif n == 16000:
            vector16000.append(finaltime)
        elif n == 32000:
            vector32000.append(finaltime)
        elif n == 64000:
            vector64000.append(finaltime)
        finaltime = str(finaltime) + "\n"
        f = open('time.txt', 'a')  # время текущей итерации
        f.write(finaltime)
        f.close()
    n *= 2
# создаём общее окно для графиков и отдельное поле для каждого из 9 графиков
figure = plt.figure()
graf1 = figure.add_subplot(3, 3, 1)
graf2 = figure.add_subplot(3, 3, 2)
graf3 = figure.add_subplot(3, 3, 3)
graf4 = figure.add_subplot(3, 3, 4)
graf5 = figure.add_subplot(3, 3, 5)
graf6 = figure.add_subplot(3, 3, 6)
graf7 = figure.add_subplot(3, 3, 7)
graf8 = figure.add_subplot(3, 3, 8)  # для 128к, но оно нам не надо
graf9 = figure.add_subplot(3, 3, 9)

# время для n=1000 на первый график
avg_time1k = 0
min_time1k = min(vector1000)
max_time1k = max(vector1000)
for i in range(len(vector1000)):
    avg_time1k += vector1000[i]
avg_time1k /= len(vector1000)
m = len(vector1000)
x = [1000] * m
graf1.set_xlim(999, 1001)
graf1.set_ylim(min_time1k - 0.5, max_time1k + 0.5)
for i in range(len(vector1000)):
    graf1.plot(x[i], vector1000[i], marker=".", color="red")

# время для n=2000 на второй график
avg_time2k = 0
min_time2k = min(vector2000)
max_time2k = max(vector2000)
for i in range(len(vector2000)):
    avg_time2k += vector2000[i]
avg_time2k /= len(vector2000)
m = len(vector2000)
x = [2000] * m
graf2.set_xlim(1999, 2001)
graf2.set_ylim(min_time2k - 1, max_time2k + 1)
for i in range(len(vector2000)):
    graf2.plot(x[i], vector2000[i], marker=".", color="red")

# время для n=4000 на третий график
avg_time4k = 0
min_time4k = min(vector4000)
max_time4k = max(vector4000)
for i in range(len(vector4000)):
    avg_time4k += vector4000[i]
avg_time4k /= len(vector4000)
m = len(vector4000)
x = [4000] * m
graf3.set_xlim(3999, 4001)
graf3.set_ylim(min_time4k - 1.5, max_time4k + 1.5)
for i in range(len(vector4000)):
    graf3.plot(x[i], vector4000[i], marker=".", color="red")

# время для n=8000 на четвертый график
vector8000 = vector8000
avg_time8k = 0
min_time8k = min(vector8000)
max_time8k = max(vector8000)
for i in range(len(vector8000)):
    avg_time8k += vector8000[i]
avg_time8k /= len(vector8000)
m = len(vector8000)
x = [8000] * m
graf4.set_xlim(7999, 8001)
graf4.set_ylim(min_time8k - 2, max_time8k + 2)
for i in range(len(vector8000)):
    graf4.plot(x[i], vector8000[i], marker=".", color="red")

# время для n=16000 на пятый график
avg_time16k = 0
min_time16k = min(vector16000)
max_time16k = max(vector16000)
for i in range(len(vector16000)):
    avg_time16k += vector16000[i]
avg_time16k /= len(vector16000)
m = len(vector16000)
x = [16000] * m
graf5.set_xlim(15999, 16001)
graf5.set_ylim(min_time16k - 2, max_time16k + 2)
for i in range(len(vector16000)):
    graf5.plot(x[i], vector16000[i], marker=".", color="red")

# время для n=32000 на шестой график
avg_time32k = 0
min_time32k = min(vector32000)
max_time32k = max(vector32000)
for i in range(len(vector32000)):
    avg_time32k += vector32000[i]
avg_time32k /= len(vector32000)
m = len(vector32000)
x = [32000] * m
graf6.set_xlim(31999, 32001)
graf6.set_ylim(min_time32k - 2, max_time32k + 2)
for i in range(len(vector32000)):
    graf6.plot(x[i], vector32000[i], marker=".", color="red")

# время для n=64000 на седьмой график
avg_time64k = 0
min_time64k = min(vector64000)
max_time64k = max(vector64000)
for i in range(len(vector64000)):
    avg_time64k += vector64000[i]
avg_time64k /= len(vector64000)
m = len(vector64000)
x = [64000] * m
graf7.set_xlim(63999, 64001)
graf7.set_ylim(min_time64k - 2, max_time64k + 2)
for i in range(len(vector64000)):
    graf7.plot(x[i], vector64000[i], marker=".", color="red")

# выводим график лучшего времени-n на девятый график
graphbest = [min_time1k, min_time2k, min_time4k, min_time8k, min_time16k, min_time32k, min_time64k]
ybestgraph = [1000, 2000, 4000, 8000, 16000, 32000, 64000]
graf9.plot(graphbest, ybestgraph, color="green", marker='o')

# выводим график худшего времени-n на девятый график
graphworst = [max_time1k, max_time2k, max_time4k, max_time8k, max_time16k, max_time32k, max_time64k]
yworstgraph = [1000, 2000, 4000, 8000, 16000, 32000, 64000]
graf9.plot(graphworst, yworstgraph, color="red", marker='o')

# выводим график среднего времени-n на девятый график
graphavg = [avg_time1k, avg_time2k, avg_time4k, avg_time8k, avg_time16k, avg_time32k, avg_time64k]
yavggraph = [1000, 2000, 4000, 8000, 16000, 32000, 64000]
graf9.plot(graphavg, yavggraph, color="yellow", marker='o')
plt.show()