from file_work import *

class UI:
    def __init__(self, file_repository):
        self._repository = file_repository

    def print_menu(self):
        print("Welcome to this graph apllication")
        print("1. See the graph you have")
        print("2. Add a new edge")
        print("3. Remove an existing edge")
        print("4. Add a new vertex")
        print("5. Remove an existing vertex")
        print("6. Modify the cost of an edge")
        print("7. Show number of vertices")
        print("8. Show number of edges")
        print("9. Create a random graph")
        print("10. Show the out degree of a vertex")
        print("11. Show the in degree of a vertex")
        print("12. Parse outbound edges of a vertex")
        print("13. Parse inbound edges of a vertex")
        print("0. Exit")

    def see_graph_you_have(self):
        dictionary_of_costs = self._repository.get_dictCost()
        number_of_vertices = self._repository.get_number_of_vertices()
        number_of_edges = self._repository.get_number_of_edges()
        print("We have " + str(number_of_vertices) + " vertices and " + str(number_of_edges) + " edges")
        for key in dictionary_of_costs:
            print("Edge starting from " + str(key[0]) + " ending in " + str(key[1]) + " with the cost " + str(dictionary_of_costs[key]))

        dictionary_out = self._repository.get_dictOut()
        dictionary_in = self._repository.get_dictIn()
        for key in dictionary_out:
            if len(dictionary_out[key]) == 0 and len(dictionary_in[key]) == 0:
                print("Empty node " + str(key))

    def add_edge(self):
        try:
            start = int(input("Give starting point: "))
            end = int(input("Give end point: "))
            cost = int(input("Give cost: "))
            self._repository.add_edge(start, end, cost)
        except ValueError as ve:
            print(ve)

    def remove_edge(self):
        try:
            start = int(input("Give starting point: "))
            end = int(input("Give end point: "))
            self._repository.remove_edge(start, end)
        except ValueError as ve:
            print(ve)

    def add_vertex(self):
        try:
            id = int(input("Give vertex number: "))
            self._repository.add_vertex(id)
        except Exception as e:
            print(e)

    def remove_vertex(self):
        try:
            id = int(input("Give vertex number: "))
            self._repository.remove_vertex(id)
        except ValueError as ve:
            print(ve)

    def modify_cost(self):
        try:
            start = int(input("Give starting point: "))
            end = int(input("Give end point: "))
            new_cost = int(input("Give cost: "))
            self._repository.modify_cost(start, end, new_cost)
        except ValueError as ve:
            print(ve)

    def show_number_of_vertices(self):
        print(str(self._repository.get_number_of_vertices()) + " vertices")

    def show_number_of_edges(self):
        print(str(self._repository.get_number_of_edges()) + " edges")

    def see_random_graph(self):
        random_graph = create_random_graph()
        dictionary_of_costs = random_graph.get_dictCost()
        number_of_vertices = random_graph.get_number_of_vertices()
        number_of_edges = random_graph.get_number_of_edges()
        print("We have " + str(number_of_vertices) + " vertices and " + str(number_of_edges) + " edges")
        for key in dictionary_of_costs:
            print("Edge starting from " + str(key[0]) + " ending in " + str(key[1]) + " with the cost " + str(
                dictionary_of_costs[key]))

        dictionary_out = random_graph.get_dictOut()
        for key in dictionary_out:
            if len(dictionary_out[key]) == 0:
                print("Empty node " + str(key))

    def show_out_degree(self):
        vertex = int(input("Give vertex: "))
        out_degree = self._repository.get_out_degree(vertex)
        print("In degree of vertex " + str(vertex) + " is " + str(out_degree))

    def show_in_degree(self):
        vertex = int(input("Give vertex: "))
        in_degree = self._repository.get_in_degree(vertex)
        print("In degree of vertex " + str(vertex) + " is " + str(in_degree))

    def parse_outbound_edges(self):
        vertex = int(input("Give vertex: "))
        outbound_edges = self._repository.parse_outbound_edges(vertex)
        for edge in outbound_edges:
            print("edge from " + str(vertex) + " to " + str(edge))

    def parse_inbound_edges(self):
        vertex = int(input("Give vertex: "))
        inbound_edges = self._repository.parse_inbound_edges(vertex)
        for edge in inbound_edges:
            print("edge from " + str(vertex) + " to " + str(edge))

    def start(self):
        while True:
            self.print_menu()
            command = input(">")
            if command == '2':
                self.add_edge()
            elif command == '1':
                self.see_graph_you_have()
            elif command == '0':
                return
            elif command == '3':
                self.remove_edge()
            elif command == '4':
                self.add_vertex()
            elif command == '5':
                self.remove_vertex()
            elif command == '6':
                self.modify_cost()
            elif command =='7':
                self.show_number_of_vertices()
            elif command == '8':
                self.show_number_of_edges()
            elif command == '9':
                self.see_random_graph()
            elif command == '10':
                self.show_out_degree()
            elif command == '11':
                self.show_in_degree()
            elif command == '12':
                self.parse_outbound_edges()
            elif command =='13':
                self.parse_inbound_edges()