'''
vertices = noduri
vertex = nod
'''

from copy import deepcopy

class DoubleDictGraph:
    def __init__(self, n):
        '''
        creates a graph with n vertices and no edges
        '''
        self._dictOut = {}      # successors
        self._dictIn = {}       # predecessors
        self._dictCost = {}

        for i in range(n):
            self._dictOut[i] = []
            self._dictIn[i] = []

    def get_number_of_vertices(self):
        '''
        the number of vertices is the length of self._dictOut dictionary
        '''
        return len(self._dictOut)

    def get_number_of_edges(self):
        '''
        the number of edges is the length of self._dictCost dictionary
        '''
        return len(self._dictCost)

    def parseV(self):
        '''
        returns an interable containing all the vertices
        '''
        return self._dictOut.keys()

    def isEdge(self, start, end):
        '''
        checks if there is an edge between start and end
        :param start: the given starting point
        :param end: the given end point
        :return: True -> if the edge exists
                False -> if the edge does not exist
        '''
        if end in self._dictOut[start]:
            return True
        return False

    def get_in_degree(self, vertex):
        '''
        the in degree of a given vertex is the length of the list corresponding to that vertex in self._dictIn
        dictionary
        '''
        if(vertex < self.get_number_of_vertices()):
            return len(self._dictIn[vertex])
        else:
            raise ValueError("Invalid vertex!")

    def get_out_degree(self, vertex):
        '''
        the out degree of a given vertex is the length of the list corresponding to that vertex in self._dictOut
        dictionary
        '''
        if (vertex < self.get_number_of_vertices()):
            return len(self._dictOut[vertex])
        raise ValueError("Invalid vertex!")

    def parse_outbound_edges(self, vertex):
        '''
        returns an iterable containing all the outbound edges of that vertex
        '''
        l = []
        outbound_edges = self._dictOut[vertex]
        for edge in outbound_edges:
            l.append(edge)
        return l

    def parse_inbound_edges(self, vertex):
        '''
        returns an iterable containing all the outbound edges of that vertex
        '''
        l = []
        inbound_edges = self._dictIn[vertex]
        for edge in inbound_edges:
            l.append(edge)
        return l

    def add_edge(self, start, end, cost):
        '''
        adds a new edge to the graph if the edge does not already exist
        :param start: the starting point
        :param end: the end point
        :param cost: the given cost
        '''
        if self.isEdge(start, end) == True:
         raise ValueError("Edge already exists!")
        self._dictOut[start].append(end)
        self._dictIn[end].append(start)
        self._dictCost[(start, end)] = cost

    def remove_edge(self, start, end):
        '''
        removes an edge from the graph if the edge exists
        :param start: the start point
        :param end: the end point
        '''
        if self.isEdge(start, end) == False:
            raise ValueError("Edge does not exist!")
        self._dictOut[start].remove(end)
        self._dictIn[end].remove(start)
        self._dictCost.pop((start, end))

    def add_vertex(self, id):
        '''
        adds a new vertex with given id by initializing a new list in both dictionaries
        '''
        self._dictOut[id] = []
        self._dictIn[id] = []

    def add_vertex_no_id(self):
        number_of_vertices = self.get_number_of_vertices()
        self._dictOut[number_of_vertices] = []
        self._dictIn[number_of_vertices] = []


    def remove_vertex_update_remaining_vertices(self, id):
        if id not in self._dictOut.keys():
            raise ValueError("Vertex does not exist!")

        successors = self._dictOut[id]
        for s in successors:
            self._dictIn[s].remove(id)
            self._dictCost.pop((id, s))

        predecessors = self._dictIn[id]
        for p in predecessors:
            self._dictOut[p].remove(id)
            self._dictCost.pop((p, id))

        self._dictOut.pop(id)
        self._dictIn.pop(id)

        # dictionary[new_key] = dictionary.pop(old_key)

        new_dict_out = {}
        for key in self._dictOut:
            newKey = key
            if key > id:
                newKey = key -1

            newSuccessors = []
            for successor in self._dictOut[key]:
                if successor > id:
                    successor -= 1
                newSuccessors.append(successor)

            new_dict_out[newKey] = newSuccessors
        self._dictOut = new_dict_out

        new_dict_in = {}
        for key in self._dictIn:
            newKey = key
            if key > id:
                newKey = key - 1

            newPredecessors = []
            for predecessor in self._dictIn[key]:
                if predecessor > id:
                    predecessor -= 1
                newPredecessors.append(predecessor)

            new_dict_in[newKey] = newPredecessors
        self._dictIn = new_dict_in

        new_dict_cost = {}
        for key in self._dictCost:
            if key[0] > id and key [1] < id:
                newKey = (key[0] -1, key[1])
            elif key[0] < id and key [1] > id:
                newKey = (key[0], key[1] -1)
            elif key[0] > id and key [1] > id:
                newKey = (key[0] -1, key[1] - 1)
            else:
                newKey = (key[0], key[1])

            new_dict_cost[newKey] = self._dictCost[key]
        self._dictCost = new_dict_cost



    def remove_vertex(self, id):
        '''
        removes a vertex with given id if the vertex exists
        '''
        if id not in self._dictOut.keys():
            raise ValueError("Vertex does not exist!")
        successors = self._dictOut[id]
        for s in successors:
            self._dictIn[s].remove(id)
            self._dictCost.pop((id, s))

        predecessors = self._dictIn[id]
        for p in predecessors:
            self._dictOut[p].remove(id)
            self._dictCost.pop((p, id))

        self._dictOut.pop(id)
        self._dictIn.pop(id)


    def retrieve_cost(self, start, end):
        '''
        retrieves the cost of an edge, if it exists
        '''
        if (start, end) not in self._dictCost.keys():
            raise ValueError("Edge does not exist!")
        self._dictCost.pop((start, end))

    def modify_cost(self, start, end, newcost):
        '''
        modifies the cost of a given edge if the edge exists
        :param start: the start point
        :param end: the end point
        :param newcost: the new cost for the edge
        :return:
        '''
        if (start, end) not in self._dictCost.keys():
            raise ValueError("Edge does not exist!")
        self._dictCost[(start, end)] = newcost

    def get_dictIn(self):
        return self._dictIn

    def get_dictOut(self):
        return self._dictOut

    def get_dictCost(self):
        return self._dictCost

    def get_graph(self):
        return deepcopy(self)

    def printAll(self):
        print(self._dictOut)
        print(self._dictIn)
        print(self._dictCost)


'''
g = DoubleDictGraph(4)
g.add_edge(0,1,7)
g.add_edge(0,2,3)
g.add_edge(1,0,10)
g.add_edge(1,3,1)
g.add_edge(2,1,8)
g.add_edge(3,1,4)
g.add_edge(3,2,5)

g.printAll()
print("******************************")
g.remove_vertex_update_remaining_vertices(0)
g.printAll()'''
