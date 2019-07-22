import os
from numpy import *
import random

def main():
    file = openF('graph.txt')
    #graph = loadGraph(file)

    graph = randomGraph(2)

    tour = TSP(graph)
    print("graph = ")
    print(graph)

    print("TSP tour = ")
    print(tour)
	
    tour = Zgadn(graph)
    print("Zhadn tour = ")
    print(tour)

    file.close()


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
            if(val == 'inf'):
                m_line = append(m_line, [float("infinity")])
            else:
                m_line = append(m_line, [float(val)])

        matrix = addLineInMatrix(matrix, m_line)

    return matrix

def addLineInMatrix(matrix, line):
    if matrix != [[]]:
        matrix = append(matrix, [line],0)
    else:
        matrix = [line]
    return matrix

def TSP(graph, start = 0, used_ver = []):
    used_ver.append(start)
    tour = [start]
    min_length = float('infinity')
    min_sub_tour = []
    for i in range(len(graph)):
        if(isValid(graph, tour, i, used_ver)):
            sub_tour = TSP(graph, i, used_ver)
            sub_tour_length = tourLength(tour + sub_tour, graph)
            if(sub_tour_length < min_length):
                min_sub_tour = sub_tour
                min_length = sub_tour_length

    if(len(used_ver)==len(graph[0])):
        print("length of " + str(used_ver) + " is " + str(tourLength(used_ver, graph)))
    used_ver.pop()
    return tour + min_sub_tour

def Zgadn(graph,start = 0, user_ver = []):
    user_ver.append(start)
    temp_index = 0
    count = len(grath)
    tour = [start]
    min_length = float('infinity')
    visited_toun = []
    min_sub_tour = []
    visited_toun[0] = false
    tour.last() 
    for i in range(count):
        visited_toun[i]=false
    for i in range(count):
        min_length = float('infinity')
        for j in range(count):
            if(not(visited_toun[j]) and (grath[start][j] < min_length)):
                min_length = grath[start][j]
                temp_index = j
        user_ver.append(temp_index)
        visited_toun[temp_index] = true
    return user_ver

def isValid(graph,i,j,usedVer):
    if(i==j):
        return False
    if(j in usedVer):
        return False
    return True

def tourLength(tour, graph):
    if(len(tour)<2):
        return 0
    length = 0
    for i in range(0,len(tour)-1):
        _from = tour[i]
        _to = tour[i+1]
        length += graph[_from][_to]
    return length

def randomGraph(n):
    matrix = array([[]])
    for i in range(n):
        m_line = array([])
        for j in range(n):
            if (i == j):
                m_line = append(m_line, [float("infinity")])
            else:
                m_line = append(m_line, [float(random.uniform(1,20))])

        matrix = addLineInMatrix(matrix, m_line)

    return matrix

main()
