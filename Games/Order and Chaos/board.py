import texttable
import copy
import random
class Board:
    def __init__(self):
        self._board = []
        for i in range(6):
            self._board.append([0]*6)
        self._X = 0
        self._O = 0

    @property
    def Board(self):
        return self._board

    @property
    def X(self):
        return self._X
    @X.setter
    def X(self, value):
        self._X = value

    @property
    def O(self):
        return self._O

    @O.setter
    def O(self, value):
        self._O = value

    def place(self, x, y, symbol):
        if x >= 6 or y >= 6:
            raise IndexError("Invalid coord")
        if self.Board[x][y] !=0 :
            raise IndexError("Square is not empty")
        self.Board[x][y] = symbol
        if symbol == 1:
            self.X += 1
        elif symbol == 2:
            self.O += 1

    def getAllValidLocations(self):
        list = []
        for i in range(6):
            for j in range(6):
                if self.Board[i][j] == 0:
                    list.append((i,j))
        return list

    def chooseRandom(self):
        list = self.getAllValidLocations()
        return random.choice(list)

    def place2(self, board, x, y, symbol):
        board[x][y] = symbol

    def isWinMoveAv(self, symbol):
        if symbol == 1:
            if self.X < 4:
                return None
        if symbol == 0:
            if self.O < 4:
                return None
        list = self.getAllValidLocations()
        #b_copy = self.Board.copy()
        b_copy = copy.deepcopy(self.Board)
        for coord in list:
            self.place2(b_copy, coord[0], coord[1], symbol)
            if self.winning_move2(b_copy, symbol) == True:
                return coord
            b_copy[coord[0]][coord[1]] = 0
        return None

    def neighbours(self, x, y):
        res = []
        res.append((x - 1, y - 1))
        res.append((x - 1, y))
        res.append((x - 1, y + 1))
        res.append((x, y - 1))
        res.append((x, y + 1))
        res.append((x + 1, y - 1))
        res.append((x + 1, y))
        res.append((x + 1, y + 1))

        poz = 0
        while poz < len(res):
            sq = res[poz]
            if sq[0] < 0 or sq[0] >= 6 or sq[1] < 0 or sq[1] >= 6:
                res.remove(sq)
            else:
                poz += 1
        return res

    def chooseSquare(self, symbol):
        max_nr = 0
        coord = None
        for i in range(6):
            for j in range(6):
                if self.Board[i][j] == 0:
                    neigh = self.neighbours(i,j)
                    nr = 0
                    for n in neigh:
                        if self.Board[n[0]][n[1]] == symbol:
                            nr += 1
                    if nr > max_nr:
                        max_nr = nr
                        coord = (i,j)
        return coord


    def isWonPlayer(self):
        if self.O + self.X == 36:
            return True

    def getMostSeenSymbol(self):
        if self.X >= self.O:
            return 1
        return 2

    def winning_move(self, piece):
        # Check horizontal locations for win
        for c in range(2):
            for r in range(6):
                if self.Board[r][c] == piece and self.Board[r][c + 1] == piece and self.Board[r][c + 2] == piece and self.Board[r][
                    c + 3] == piece and self.Board[r][c+4] == piece:
                    return True

        # Check vertical location for win
        for c in range(6):
            for r in range(2):
                if self.Board[r][c] == piece and self.Board[r + 1][c] == piece and self.Board[r + 2][c] == piece and self.Board[r + 3][
                    c] == piece and self.Board[r+4][c] == piece:
                    return True

        # Check positively sloped diagonals
        for c in range(2):
            for r in range(2):
                if self.Board[r][c] == piece and self.Board[r + 1][c + 1] == piece and self.Board[r + 2][c + 2] == piece and self.Board[r + 3][c + 3] == piece and \
                        self.Board[r+4][c+4] == piece:
                    return True

        # Check negatively sloped diagonals
        for c in range(2):
            for r in range(4, 6):
                if self.Board[r][c] == piece and self.Board[r - 1][c + 1] == piece and self.Board[r - 2][c + 2] == piece and \
                        self.Board[r - 3][c + 3] == piece and self.Board[r-4][c+4] == piece:
                    return True
        return False

    def winning_move2(self, board, piece):
        # Check horizontal locations for win
        for c in range(2):
            for r in range(6):
                if board[r][c] == piece and board[r][c + 1] == piece and board[r][c + 2] == piece and board[r][
                    c + 3] == piece and board[r][c+4] == piece:
                    return True

        # Check vertical location for win
        for c in range(6):
            for r in range(2):
                if board[r][c] == piece and board[r + 1][c] == piece and board[r + 2][c] == piece and board[r + 3][
                    c] == piece and board[r+4][c] == piece:
                    return True

        # Check positively sloped diagonals
        for c in range(2):
            for r in range(2):
                if board[r][c] == piece and board[r + 1][c + 1] == piece and board[r + 2][c + 2] == piece and board[r + 3][c + 3] == piece and \
                        board[r+4][c+4] == piece:
                    return True

        # Check negatively sloped diagonals
        for c in range(2):
            for r in range(4, 6):
                if board[r][c] == piece and board[r - 1][c + 1] == piece and board[r - 2][c + 2] == piece and \
                        board[r - 3][c + 3] == piece and board[r-4][c+4] == piece:
                    return True
        return False

    def __str__(self):
        t = texttable.Texttable()
        row = [' ',0,1,2,3,4,5]
        t.add_row(row)
        d = {0: " ", 1: "X", 2: "O"}
        for i in range(6):
            row = [i]
            for j in range(6):
                row.append(d[self._board[i][j]])
            t.add_row(row)
        return t.draw()

'''
b = Board()
b.place(0,0,1)
#b.place(1,1,1)
#b.place(2,2,1)
b.place(3,3,1)
b.place(4,5,2)
print(b.chooseSquare(1))
#print(b.winning_move(1))
#print(b.isWinMoveAv(1))
#print(b.X)
#print(b.getAllValidLocations())
print(b)'''
