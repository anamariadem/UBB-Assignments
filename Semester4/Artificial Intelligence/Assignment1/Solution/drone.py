import pygame
from pygame.locals import *

class Drone():
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self._visited = set()
        self._visited.add((x, y))
        self._back_log = [(x, y)]

    def move(self, detected_map):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detected_map.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detected_map.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detected_map.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detected_map.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def get_drone_neighbours(self, detected_map):
        neighbours = []
        if self.x > 0:
            if detected_map.surface[self.x - 1][self.y] == 0:
                neighbours.append((self.x - 1, self.y))

        if self.x < 19:
            if detected_map.surface[self.x + 1][self.y] == 0:
                neighbours.append((self.x + 1, self.y))

        if self.y > 0:
            if detected_map.surface[self.x][self.y - 1] == 0:
                neighbours.append((self.x, self.y - 1))

        if self.y < 19:
            if detected_map.surface[self.x][self.y + 1] == 0:
                neighbours.append((self.x, self.y + 1))

        return neighbours

    def get_unvisited_neighbours(self, detected_map):
        unvisited_neighbours = []

        for neighbour in self.get_drone_neighbours(detected_map):
            if neighbour not in self._visited:
                unvisited_neighbours.append(neighbour)

        return unvisited_neighbours

    def is_search_finished(self):
        return (self.x, self.y) == (None, None)

    def moveDSF(self, detected_map):
        unvisited_neighbours = self.get_unvisited_neighbours(detected_map)

        if len(unvisited_neighbours) == 0:
            if len(self._back_log) == 0:
                self.x = None
                self.y = None
            else:
                (self.x, self.y) = self._back_log.pop()
            return

        self._back_log.append((self.x, self.y))
        popped_neighbour = unvisited_neighbours.pop()
        (self.x, self.y) = popped_neighbour
        self._visited.add(popped_neighbour)


