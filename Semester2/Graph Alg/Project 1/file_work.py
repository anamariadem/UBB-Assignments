from graph_repr import *
from random import *
from copy import deepcopy

class FileGraphs():
    def __init__(self, filename):
        self._graph = DoubleDictGraph(0)
        self.__fileName = filename
        self._entities = []
        self.__readFile()

    def __readFile(self):
        self._entities = []
        with open(self.__fileName, "r") as file:
            first_line = file.readline().strip()
            first_line = first_line.split(" ")
            vertices = int(first_line[0])
            self._entities.append(vertices)
            edges = int(first_line[1])
            for edge in range(edges):
                line = file.readline().strip()
                line = line.split(" ")
                self._entities.append((int(line[0]), int(line[1]), int(line[2])))

    def __writeAllToFile(self):
        with open(self.__fileName, "w") as file:
            file.write(str(self._entities[0]) + " " +str(len(self._entities)-1) + '\n')
            for i in range(1, len(self._entities)):
                coord = self._entities[i]
                file.write(str(coord[0]) + " " + str(coord[1]) + " " + str(coord[2]) + "\n")

    def create_graph(self):
        self._graph = DoubleDictGraph(self._entities[0])
        for i in range(1, len(self._entities)):
            coord = self._entities[i]
            self._graph.add_edge(coord[0], coord[1], coord[2])
        #print(self._graph.get_dictOut())
        #graph.printAll()

    def update_entities(self):
        dictionary_of_costs = self._graph.get_dictCost()
        number_of_vertices = self._graph.get_number_of_vertices()
        self._entities = []
        self._entities.append(number_of_vertices)
        for key in dictionary_of_costs:
            self._entities.append((key[0], key[1], dictionary_of_costs[key]))

    def add_edge(self, start, end, cost):
        self._graph.add_edge(start, end, cost)
        self.update_entities()
        self.__writeAllToFile()

    def remove_edge(self, start, end):
        self._graph.remove_edge(start, end)
        self.update_entities()
        self.__writeAllToFile()

    def add_vertex(self, id):
        self._graph.add_vertex(id)
        self.update_entities()
        self.__writeAllToFile()

    def remove_vertex(self, id):
        self._graph.remove_vertex(id)
        self.update_entities()
        self.__writeAllToFile()

    def retrieve_cost(self, start, end):
        self._graph.retrieve_cost(start, end)
        self.update_entities()
        self.__writeAllToFile()

    def modify_cost(self, start, end, new_cost):
        self._graph.modify_cost(start, end, new_cost)
        self.update_entities()
        self.__writeAllToFile()

    def getAll(self):
        return self._entities

    def get_graph(self):
        return deepcopy(self._graph)

    def get_dictOut(self):
        return self._graph.get_dictOut()

    def get_dictIn(self):
        return self._graph.get_dictIn()

    def get_dictCost(self):
        return self._graph.get_dictCost()

    def get_number_of_vertices(self):
        return self._graph.get_number_of_vertices()

    def get_number_of_edges(self):
        return self._graph.get_number_of_edges()

    def get_in_degree(self, vertex):
        return self._graph.get_in_degree(vertex)

    def get_out_degree(self, vertex):
        return self._graph.get_out_degree(vertex)

    def parse_outbound_edges(self, vertex):
        return self._graph.parse_outbound_edges(vertex)

    def parse_inbound_edges(self, vertex):
        return self._graph.parse_inbound_edges(vertex)


def add_edge_in_random_graph(number_of_vertices, graph):
    start = randint(0, number_of_vertices-1)
    end = randint(0, number_of_vertices-1)
    cost = randint(1, 100)
    if(graph.isEdge(start, end) == False):
        graph.add_edge(start, end, cost)

def create_random_graph():
    number_of_vertices = randint(1, 10)
    number_of_edges = randint(4, 40)

    random_graph = DoubleDictGraph(number_of_vertices)
    for i in range(number_of_edges):
        add_edge_in_random_graph(number_of_vertices, random_graph)

    return random_graph

