import pygame
import numpy as np
from Domain.constants import *


class DroneMap():
    def __init__(self):
        self.__n = ROWS
        self.__m = COLUMNS
        self.surface = np.zeros((self.__n, self.__m))
        for i in range(self.__n):
            for j in range(self.__m):
                self.surface[i][j] = -1

    def mark_detected_walls(self, e, x, y):
        #   To DO
        # mark on this map the wals that you detect
        if x is None and y is  None:
            return

        walls = e.readUDMSensors(x, y)
        i = x - 1
        if walls[UP] > 0:
            while ((i >= 0) and (i >= x - walls[UP])):
                self.surface[i][y] = 0
                i = i - 1
        if (i >= 0):
            self.surface[i][y] = 1

        i = x + 1
        if walls[DOWN] > 0:
            while ((i < self.__n) and (i <= x + walls[DOWN])):
                self.surface[i][y] = 0
                i = i + 1
        if (i < self.__n):
            self.surface[i][y] = 1

        j = y + 1
        if walls[LEFT] > 0:
            while ((j < self.__m) and (j <= y + walls[LEFT])):
                self.surface[x][j] = 0
                j = j + 1
        if (j < self.__m):
            self.surface[x][j] = 1

        j = y - 1
        if walls[RIGHT] > 0:
            while ((j >= 0) and (j >= y - walls[RIGHT])):
                self.surface[x][j] = 0
                j = j - 1
        if (j >= 0):
            self.surface[x][j] = 1

        return None

    def image(self, x, y):

        imagine = pygame.Surface((420, 420))
        brick = pygame.Surface((20, 20))
        empty = pygame.Surface((20, 20))
        empty.fill(WHITE)
        brick.fill(BLACK)
        imagine.fill(GRAYBLUE)

        for i in range(self.__n):
            for j in range(self.__m):
                if (self.surface[i][j] == 1):
                    imagine.blit(brick, (j * 20, i * 20))
                elif (self.surface[i][j] == 0):
                    imagine.blit(empty, (j * 20, i * 20))

        drona = pygame.image.load("Images/drona.png")
        imagine.blit(drona, (y * 20, x * 20))
        return imagine
