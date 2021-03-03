from Domain.constants import *
from Domain.drone import *
from Domain.drone_map import *
from Domain.environment import *


class Service:
    def __init__(self):
        self._environment = Environment()
        self._environment.randomMap()

        x = randint(0, 19)
        y = randint(0, 19)
        self._drone = Drone(x, y)

        self._drone_map = DroneMap()

        self._visited = set()
        self._visited.add((x, y))
        self._back_log = [(x, y)]


    def save_environment(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self._environment, f)
            f.close()

    def load_environment(self, numfile):
        with open(numfile, "rb") as f:
            self._environment = pickle.load(f)
            f.close()

    def environment_image(self):
        return self._environment.image()

    def detected_map_image(self):
        return self._drone_map.image(self._drone.x, self._drone.y)

    def mark_detected_walls(self):
        self._drone_map.mark_detected_walls(self._environment, self._drone.x, self._drone.y)

    def get_unvisited_neighbours(self):
        unvisited_neighbours = []

        for neighbour in self._drone.get_drone_neighbours(self._drone_map):
            if neighbour not in self._visited:
                unvisited_neighbours.append(neighbour)

        return unvisited_neighbours

    def is_search_finished(self):
        return self._drone.is_search_finished()

    def move_dfs(self):
        #self._drone.x, self._drone.y = self._drone.move_dfs(self._drone_map)
        unvisited_neighbours = self.get_unvisited_neighbours()
        print(self._drone.x, self._drone.y)
        if len(unvisited_neighbours) == 0:
            if len(self._back_log) == 0:
                self._drone.x = None
                self._drone.y = None
            else:
                (self._drone.x, self._drone.y) = self._back_log.pop()
            return

        self._back_log.append((self._drone.x, self._drone.y))
        popped_neighbour = unvisited_neighbours.pop()
        (self._drone.x, self._drone.y) = popped_neighbour
        self._visited.add(popped_neighbour)
