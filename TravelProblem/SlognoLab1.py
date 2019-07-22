import os
from numpy import *
from timeit import *
import random


def main():
    #file = openF('graph.txt')
    #graph = loadGraph(file)
    graph = randomGraph(10)
    tour = TSP(graph)
    #print("TSP tour = ")
    print()
    print(tour)
    a=tourLength(tour, graph)
    print(a)
    tourZgadn = Zgadn(graph)
    #print("Zhadn tour = ")
    print(tourZgadn)
    b=tourLength(tourZgadn, graph)
    print(b)
    #print("Расхождение:")
    print(b/a)
    #tour = Gran(graph)
    #print("Grand tour = ")
    #print(tour)
    #print(graph)
    #print(tourLength(tour, graph))
    #fib(55)
    #file.close()


def openF(filename):
    dirname = os.path.dirname(__file__)
    filename = os.path.join(dirname, filename)
    file = open(filename, 'r')
    return file


def loadGraph(file):
    matrix = array([[]])
    for line in file:
        m_line = array([])

        for val in line.split():
            if (val == 'inf'):
                m_line = append(m_line, [float("infinity")])
            else:
                m_line = append(m_line, [float(val)])

        matrix = addLineInMatrix(matrix, m_line)

    return matrix


def addLineInMatrix(matrix, line):
    if matrix != [[]]:
        matrix = append(matrix, [line], 0)
    else:
        matrix = [line]
    return matrix


def isValid(graph, i, j, usedVer):
    if (i == j):
        return False
    if (j in usedVer):
        return False
    return True


def TSP(graph, start=0, used_ver=[]):
    used_ver.append(start)
    min_length = float('infinity')
    min_sub_tour = []
    if (len(used_ver) == len(graph)):
        #print("length of " + str(used_ver) + " is " + str(tourLength(used_ver, graph)))
        min_sub_tour = list(used_ver)
    else:
        for i in range(len(graph)):
            if (not(i in used_ver)):
                sub_tour = TSP(graph, i, used_ver)
                sub_tour_length = tourLength(sub_tour, graph)
                if (sub_tour_length < min_length):
                    min_sub_tour = sub_tour
                    min_length = sub_tour_length
    used_ver.pop()
    return min_sub_tour


def Zgadn(graph):
    temp_index = 0
    count = len(graph)
    min = float('infinity')
    minIndex = 0

    for i in range(count):
        for j in range(count):
            if (graph[i][j] < min):
                min = graph[i][j]
                minIndex = i

    visited_town = []
    min_sub_tour = [minIndex]
    for i in range(count):
        visited_town.append(False)
    visited_town[minIndex]=True
    for i in range(count - 1):
        min_length = float('infinity')
        for j in range(count):
            if (not (visited_town[j]) and (minIndex != j) and(graph[minIndex][j] < min_length)):
                min_length = graph[minIndex][j]
                temp_index = j
        minIndex = temp_index
        min_sub_tour.append(temp_index)
        visited_town[temp_index] = True
    
    return min_sub_tour


def reGran(graph):
    if(graph == []):
        return []
    graph = reducuctGraph(graph)
    marks = costsFromGraph(graph)
    m = arrayMax(marks)
    graph[m[1]][m[0]] = float('infinity')
    subGraph = deleteFromGraph(graph, m)
    sub_m_l = reGran(subGraph)
    for i in range(len(sub_m_l)):
        if(sub_m_l[i][0]>=m[0]):
            sub_m_l[i]=(sub_m_l[i][0]+1,sub_m_l[i][1])
        if(sub_m_l[i][1]>=m[1]):
            sub_m_l[i]=(sub_m_l[i][0],sub_m_l[i][1]+1)
    return [m] + sub_m_l


def Gran(graph, start=0, user_ver=[]):
    rebs = reGran(array(graph))
    tour = [rebs[0][1]]
    rebs.remove(rebs[0])
    #print(rebs)
    while len(rebs)!=0:
        for reb in rebs:
            if(reb[0] == tour[len(tour)-1]):
                tour.append(reb[1])
                rebs.remove(reb)
    return tour


def reducuctGraph(graph):
    count = len(graph)
    for row in graph:
        min_item = min(row)
        for i in range(count):
            row[i] -= min_item
    for i in range(count):
        min_item = graph[0][i]
        for j in range(1, count):
            if (graph[j][i] < min_item):
                min_item = graph[j][i]
        for j in range(0, count):
            graph[j][i] -= min_item
    return graph


def deleteFromGraph(graph, mark_coord):
    newGraph = []
    count = len(graph)
    for i in range(count):
        if(i!=mark_coord[0]):
            line = []
            for j in range(count):
                if(j != mark_coord[1]):
                    line.append(graph[i][j])
            newGraph.append(line)
    return newGraph


def costsFromGraph(graph):
    count = len(graph)
    arrWithCosts = array(graph)
    arrayZero(arrWithCosts)
    for i in range(count):
        for j in range(count):
            if (graph[i][j] == 0):
                arrWithCosts[i][j] = minInCol(graph, i, j) + minInRow(graph, i, j)
    return arrWithCosts


def minInCol(graph, row, column):
    min_item =  float('infinity')
    count = len(graph)
    for j in range(0, count):
        if (graph[j][column] < min_item and j!=row):
            min_item = graph[j][column]
    return min_item


def minInRow(graph, row, column):
    min_item =  float('infinity')
    count = len(graph)
    for i in range(0, count):
        if (graph[row][i] < min_item and i != column):
            min_item = graph[row][i]
    return min_item


def arrayZero (array):
    count = len(array)
    for i in range(count):
        for j in range(count):
            array[i][j] = -1


def arrayMax(array):
    count = len(array)
    max_item = -1
    a = 0
    b = 0
    for j in range(count):
        for i in range(count):
            if (array[i][j] > max_item):
                max_item = array[i][j]
                a = i
                b = j
    return (a, b)


def tourLength(tour, graph):
    if (len(tour) < 2):
        return 0
    length = 0
    for i in range(0, len(tour) - 1):
        _from = tour[i]
        _to = tour[i + 1]
        length += graph[_from][_to]
    length += graph[tour[len(tour) - 1]][tour[0]]
    return length


def randomGraph(n):
    matrix = array([[]])
    for i in range(n):
        m_line = array([])
        for j in range(0,n):
            if(j < i):
                m_line = append(m_line, matrix[j][i])
            elif (i == j):
                m_line = append(m_line, [float("infinity")])
            else:
                m_line = append(m_line, [float(random.uniform(1, 20))])
        matrix = addLineInMatrix(matrix, m_line)
    return matrix


def fib(n):
    list=[]
    a=1
    b=1
    list.append(a)
    list.append(b)
    temp = 0
    if(n<=2):
       return 1
    while (b+a < n):
        temp = b
        b = a + b
        list.append(b)
        a = temp
    print(list)
    return list


#for i in range(50):
#    main()

global tgraph
tgraph = randomGraph(10)
t=timeit('TSP(graph)', setup='from __main__ import tgraph; from __main__ import TSP; graph = tgraph', number=1)
print("TSP time = ", t)
t=timeit('Zgadn(graph)', setup='from __main__ import tgraph; from __main__ import Zgadn; graph = tgraph', number=1)
print("Zgadn time = ", t)
#t=timeit('Gran(graph)', setup='from __main__ import tgraph; from __main__ import Gran; graph = tgraph', number=0)
#print("Gran time = ", t)