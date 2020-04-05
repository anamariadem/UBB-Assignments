from graph_repr import DoubleDictGraph

def breadth_first_search(graph, starting_vertex):
    queue = list()
    prev = {}
    dist = {}
    visited = set()
    queue.append(starting_vertex)
    visited.add(starting_vertex)
    dist[starting_vertex] = 0

    while len(queue)!=0:
        current_vertex = queue.pop(0)
        for nextVertex in graph.parse_outbound_edges(current_vertex):
            if nextVertex not in visited:
                queue.append(nextVertex)
                visited.add(nextVertex)

                dist[nextVertex] = dist[current_vertex] + 1
                prev[nextVertex] = current_vertex

    return visited, prev, dist

def get_path(graph, starting_vertex, ending_vertex):
    result = breadth_first_search(graph, starting_vertex)
    prev = result[1]
    dist = result[2]
    path = [ending_vertex]
    try:
        length = dist[ending_vertex]
        while length > 0:
            path.append(prev[ending_vertex])
            ending_vertex = prev[ending_vertex]
            length -= 1

        path.reverse()
        return path
    except KeyError:
        raise ValueError("No path between the vertices :(")

def init_graph(g):
    g.add_edge(0, 0, 7)
    g.add_edge(0, 2, 3)
    g.add_edge(1, 0, 10)
    g.add_edge(1, 5, 1)
    g.add_edge(2, 3, 8)
    g.add_edge(2, 4, 5)
    g.add_edge(3, 1, 4)
    g.add_edge(4, 5, 5)

def run():
    graph = DoubleDictGraph(6)
    init_graph(graph)

    starting_vertex = int(input("Give starting vertex: "))
    ending_vertex = int(input("Give ending vertex: "))

    if starting_vertex < 0 or starting_vertex > 5 or ending_vertex < 0 or ending_vertex > 5:
        print("Invalid vertices")
        return

    try:
        path = get_path(graph, starting_vertex, ending_vertex)

        for i in range(len(path)):
            if i == len(path) - 1:
                print(str(path[i]))
            else:
                print(str(path[i]) + " -> ", end="")

    except ValueError as ve:
        print(ve)

run()

