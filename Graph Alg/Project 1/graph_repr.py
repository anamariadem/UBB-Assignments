'''
vertices = noduri
vertex = nod
'''

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
        return len(self._dictOut)

    def get_number_of_edges(self):
        return len(self._dictCost)

    def parseV(self):
        '''
        returns an interable containing all the vertices
        '''
        return self._dictOut.keys()

    def isEdge(self, start, end):
        if end in self._dictOut[start]:
            return True
        return False

    def get_in_degree(self, vertex):
        return len(self._dictIn[vertex])

    def get_out_degree(self, vertex):
        return len(self._dictOut[vertex])

    def parse_outbound_edges(self, vertex):
        l = []
        outbound_edges = self._dictOut[vertex]
        for edge in outbound_edges:
            l.append(edge)
        return l

    def parse_inbound_edges(self, vertex):
        l = []
        inbound_edges = self._dictIn[vertex]
        for edge in inbound_edges:
            l.append(edge)
        return l

    def add_edge(self, start, end, cost):
        if self.isEdge(start, end) == True:
         raise ValueError("Edge already exists!")
        self._dictOut[start].append(end)
        self._dictIn[end].append(start)
        self._dictCost[(start, end)] = cost

    def remove_edge(self, start, end):
        if self.isEdge(start, end) == False:
            raise ValueError("Edge does not exist!")
        self._dictOut[start].remove(end)
        self._dictIn[end].remove(start)
        self._dictCost.pop((start, end))

    def add_vertex(self, id):
        self._dictOut[id] = []
        self._dictIn[id] = []

    def remove_vertex(self, id):
        if id not in self._dictOut.keys():
            raise ValueError("Vertex does not exist!")

        successors = self._dictOut[id]
        for s in successors:
            self._dictIn[s].remove(id)
            self._dictCost.pop((id, s))

        predecessors = self._dictIn[id]
        for p in predecessors:
            self._dictOut[p].remove(id)

        self._dictOut.pop(id)
        self._dictIn.pop(id)

    def modify_cost(self, start, end, newcost):
        if (start, end) not in self._dictCost.keys():
            raise ValueError("Edge does not exist!")
        self._dictCost[(start, end)] = newcost

    def get_dictIn(self):
        return self._dictIn

    def get_dictOut(self):
        return self._dictOut

    def get_dictCost(self):
        return self._dictCost

    def printAll(self):
        print(self._dictOut)
        print(self._dictIn)
        print(self._dictCost)


