import time
import matplotlib.pyplot as plt
import timeit
# Читаем начальную и две конечные точки из входных данных

input_str = input().split()
start = input_str[0]
finish1 = input_str[1]
finish2 = input_str[2] if len(input_str) == 3 else None

# Создаем пустой граф
graph = {}

# Читаем данные о вершинах и ребрах и добавляем их в граф

while True:
   try:
       elements = input().split()
       # Если данные закончились, выходим из цикла
       if not elements:
           break

       # Читаем данные о вершине и ребре
       start_vertex, end_vertex, length = elements

       # Добавляем вершину и ребро в граф
       if start_vertex not in graph:
           graph[start_vertex] = [(end_vertex, float(length))]
       else:
           graph[start_vertex].append((end_vertex, float(length)))

   except EOFError:
       break


# Функция для получения соседних вершин
def g_neighbors(neighbors_list, v):
   # Если вершина не существует в графе, возвращаем None
   return neighbors_list.get(v)


# Функция для получения эвристической функции
def heuristic_func(vertex, finish):
   # В данном случае, эвристика - разница между конечной вершиной и текущей вершиной по ASCII кодам
   return ord(finish) - ord(vertex)


# Функция A* для поиска кратчайшего пути в графе до любого из двух финишей
def A_star_algorithm1(adjac_lis, start, finish1, finish2=None):
   # Открытый и закрытый списки вершин
   open_list = set([start])
   closed_list = set()

   # Текущее расстояние до каждой вершины
   cur_distance = {start: 0}

   # Соседи каждой вершины на пути до старта
   adj_nodes = {start: start}

   while len(open_list) > 0:
       n = None
       # Ищем вершину с наименьшей стоимостью
       for adj_node in open_list:
           # Если ранее вершина не была инициализирована или новый путь короче, выбираем её
           if n is None or (cur_distance[adj_node] + heuristic_func(adj_node, finish1) < cur_distance[
               n] + heuristic_func(n, finish1)):
               n = adj_node
               print("Рассмтриваемая вершина:",n,"Вес Ребра: ", cur_distance[n], "Стоимость по ASKII :", heuristic_func(n,finish1))
               print("Сost Vertex: ", cur_distance[n]+heuristic_func(n,finish1) )
               print("open_list: ", open_list)
               print("closed_list: ", closed_list)

       # Если не найдено, что было бы странным, выбрасываем ошибку
       if n is None:
           raise Exception("Path doesn't exist")

       # Если мы достигли первого финиша, восстанавливаем путь и возвращаем его
       if n == finish1:
           best_path_list = []
           while adj_nodes[n] != n:
               best_path_list.append(n)
               n = adj_nodes[n]

           best_path_list.append(start)
           best_path_list = best_path_list[::-1]
           return ''.join(best_path_list)

       # Если мы достигли второго финиша, восстанавли
       if finish2 is not None and n == finish2:
           best_path_list = []
           while adj_nodes[n] != n:
               best_path_list.append(n)
               n = adj_nodes[n]

           best_path_list.append(start)
           best_path_list = best_path_list[::-1]
           return ''.join(best_path_list)

           # Получаем соседей текущей вершины
       neighbours = g_neighbors(adjac_lis, n)

       # Если вершина не имеет соседей, удаляем её из открытого списка и добавляем в закрытый
       if not neighbours:
           open_list.remove(n)
           closed_list.add(n)
           continue

       # Обновляем текущее расстояние и соседей, если находим лучший путь
       for (neighbour, weight) in neighbours:
           if neighbour not in open_list and neighbour not in closed_list:
               # Если сосед не находится ни в открытом, ни в закрытом списке, добавляем его в открытый список
               open_list.add(neighbour)
               adj_nodes[neighbour] = n
               cur_distance[neighbour] = cur_distance[n] + weight
           else:
               # Если сосед уже находится в открытом или закрытом списке, проверяем, можно ли улучшить путь до него
               if cur_distance[neighbour] > cur_distance[n] + weight:
                   # Если новый путь короче, обновляем текущее расстояние и соседей
                   cur_distance[neighbour] = cur_distance[n] + weight
                   adj_nodes[neighbour] = n

                   if neighbour in closed_list:
                       # Если сосед находился в закрытом списке, удаляем его из него и добавляем в открытый список
                       closed_list.remove(neighbour)
                       open_list.add(neighbour)
               elif neighbour == finish1 or neighbour == finish2:
                   # Если сосед является одним из двух финишей, проверяем, можно ли улучшить путь до него
                   if cur_distance[neighbour] > cur_distance[n] + weight:
                       # Если новый путь короче, обновляем текущее расстояние и соседей
                       cur_distance[neighbour] = cur_distance[n] + weight
                       adj_nodes[neighbour] = n

                   if neighbour in closed_list:
                       # Если сосед находился в закрытом списке, удаляем его из него и добавляем в открытый список
                       closed_list.remove(neighbour)
                       open_list.add(neighbour)
                   elif neighbour in open_list:
                       # Если сосед уже находится в открытом списке, обновляем его текущее расстояние и соседей
                       adj_nodes[neighbour] = n
                       cur_distance[neighbour] = cur_distance[n] + weight

       # Удаляем текущую вершину из открытого списка и добавляем в закрытый список
       open_list.remove(n)
       closed_list.add(n)
       print("open_list: ", open_list)
       print("closed_list: ", closed_list)

   # Если не найдено пути, возвращаем None
   return None
print(A_star_algorithm1(graph,start,finish1,finish2))

import random

def generate_random_graph(n, m):
   # Создаем пустой граф
   graph = {}

   # Добавляем n вершин в граф
   for i in range(n):
       graph[str(i)] = []

   # Добавляем m рандомных ребер в граф
   for i in range(m):
       # Случайно выбираем две разные вершины
       start_vertex = str(random.randint(0, n-1))
       end_vertex = str(random.randint(0, n-1))
       while end_vertex == start_vertex or end_vertex in [x[0] for x in graph[start_vertex]]:
           end_vertex = str(random.randint(0, n-1))

       # Добавляем ребро в граф
       graph[start_vertex].append((end_vertex, float(random.randint(1, 10))))

   return graph


# graph1 = generate_random_graph(10000,10000)
#
# path1 = A_star_algorithm1(graph1,'a','z',finish2 = None)
# print(path1)
#
#
# def run_algorithm(algorithm, graph1, start, finish1, finish2):
#    start_time = timeit.default_timer()
#    algorithm(graph1, start, finish1, finish2)
#    return timeit.default_timer() - start_time
#
# n_values = [10, 50, 100, 500, 1000]
# times_a_star = []
#
# for n in n_values:
#    input_str = f'a z\n' + '\n'.join([f'{chr(i)} {chr(i+1)} 1.0' for i in range(97, 97+n-1)])
#    graph = graph1
#    for line in input_str.split('\n'):
#        elements = line.split()
#        if len(elements) == 3:
#            start_vertex, end_vertex, length = elements
#            if start_vertex not in graph:
#                graph[start_vertex] = [(end_vertex, float(length))]
#            else:
#                graph[start_vertex].append((end_vertex, float(length)))
#    times_a_star.append(run_algorithm(A_star_algorithm1, graph, 'a', 'z', None))
#
# plt.plot(n_values, times_a_star, label='A* algorithm')
# plt.xlabel('Number of nodes')
# plt.ylabel('Execution time, sec')
# plt.title('Execution time vs Number of nodes')
# plt.legend()
# plt.show()
#
# # График зависимости времени выполнения алгоритмов A* и Dijkstra от числа ребер в графе
# m_values = [10, 50, 100, 500, 1000]
# times_a_star = []
#
# for m in m_values:
#    input_str = f'a z\n' + '\n'.join([f'{chr(i)} {chr(i+1)} {1.0/m}' for i in range(97, 97+m-1)])
#    graph = generate_random_graph
#    for line in input_str.split('\n'):
#        elements = line.split()
#        if len(elements) == 3:
#            start_vertex, end_vertex, length = elements
#            if start_vertex not in graph:
#                graph[start_vertex] = [(end_vertex, float(length))]
#            else:
#                graph[start_vertex].append((end_vertex, float(length)))
#    times_a_star.append(run_algorithm(A_star_algorithm1, graph, 'a', 'z', None))
# plt.plot(m_values, times_a_star, label='A* algorithm')
# plt.xlabel('Number of edges')
# plt.ylabel('Execution time, sec')
# plt.title('Execution time vs Number of edges')
# plt.legend()
# plt.show()
#
#
#
# def measure_time(graph, start, finish1, finish2=None):
#
#    print(f"Graph size: {len(graph)} vertices")
#    start_time = time.time()
#    A_star_algorithm1(graph, start, finish1, finish2)
#    end_time = time.time()
#    print(f"A* Algorithm 1: {end_time - start_time:.6f} seconds")
