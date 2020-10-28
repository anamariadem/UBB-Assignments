import texttable
import random

class SteppedOnMineException(Exception):
    pass

class Field:
    '''
    represents one square of the minefield
    has coordinates, and a state value (mine or no-mine)
    '''
    def __init__(self, x, y, state):
        self._x = x
        self._y = y
        self._state = state
        self._revealed = False

    def reveal(self):
        self._revealed = True

class Board:
    def __init__(self, width, height, mines):
        # ++validation
        self._w = width
        self._h = height
        self._mines = mines
        # Initialize the board
        self._data = []
        for i in range(height):
            self._data.append([0] * self._w)
        # have a second matrix that contains the revealed ones
        self._reveal = []
        for i in range(height):
            self._reveal.append([9] * self._w)
        self._layMines()
        self._computeNeighbours()

    def move(self, x, y):
        if x < 0 or y < 0 or x >= self._h or y >= self._w:
            raise ValueError("Step in the minefield!")
        if self._data[x][y] == -1:
            raise SteppedOnMineException()
        if self._data[x][y]!=0:
            self._reveal[x][y] = self._data[x][y]
            return
        #no mine neighbours
        stack = []
        stack.append((x,y))
        while len(stack) > 0:
            f = stack.pop()
            self._reveal[f[0]][f[1]] = self._data[f[0]][f[1]]
            for n in self._neighbours(f[0],f[1]):
                self._reveal[n[0]][n[1]] = self._data[n[0]][n[1]]
                if self._reveal[n[0]][n[1]] == 9 and self._data[n[0]][n[1]] == 0:
                    stack.append(n)


    def _computeNeighbours(self):
        for x in range(self._h):
            for y in range(self._w):
                if self._data[x][y] == -1:
                    continue
                mines = 0
                for ng in self._neighbours(x, y):
                    if self._data[ng[0]][ng[1]] == -1:
                        mines += 1
                self._data[x][y] = mines

    def _layMines(self):
        indices = list(range(0, self._h * self._w))
        for i in range(self._mines):
            val = random.choice(indices)
            indices.remove(val)
            self._data[val // self._w][val % self._w] = -1

    def _neighbours(self,x,y):
        w = self._w
        h = self._h
        res = []
        res.append((x-1, y-1))
        res.append((x - 1, y))
        res.append((x - 1, y + 1))
        res.append((x, y-1))
        res.append((x, y + 1))
        res.append((x + 1, y - 1))
        res.append((x + 1, y))
        res.append((x + 1, y + 1))

        poz = 0
        while poz < len(res):
            sq = res[poz]
            if sq[0]<0 or sq[0]>=h or sq[1]<0 or sq[1]>=w:
                res.remove(sq)
            else:
                poz += 1
        return res

    def __str__(self):
        t = texttable.Texttable()
        for i in range(self._h):
            t.add_row(self._data[i])
        print(t.draw())

        t = texttable.Texttable()
        for i in range(self._h):
            t.add_row(self._reveal[i])
        return t.draw()

b = Board(6,4,2)
b.move(0,0)
print(b)