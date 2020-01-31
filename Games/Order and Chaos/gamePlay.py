from board import *
import random
class GamePlay:
    def __init__(self, board):
        self._board = board

    def playerMove(self, x, y, symbol):
        self._board.place(x,y,symbol)

    def moveRandom(self):
         coord = self._board.chooseRandom()
         l = [1,2]
         symbol = random.choice(l)
         self._board.place(coord[0], coord[1], symbol)

    def computerMove(self):
        coord = self._board.isWinMoveAv(1)
        if coord!= None:
            self._board.place(coord[0], coord[1], 1)
            return
        coord = self._board.isWinMoveAv(2)
        if coord != None:
            self._board.place(coord[0], coord[1], 2)
            return

        symbol = self._board.getMostSeenSymbol()
        square = self._board.chooseSquare(symbol)
        self._board.place(square[0], square[1], symbol)

    def getBoard(self):
        return self._board

    def isWonPlayer(self):
        return self._board.isWonPlayer()

    def isWonAI(self):
        if self._board.winning_move(1) == True or self._board.winning_move(2) == True:
            return True
        return False

'''
b = Board()
gp = GamePlay(b)
print(gp.getBoard())
gp.playerMove(1,1,1)
print(gp.getBoard())
gp.playerMove(0,0,1)
print(gp.getBoard())
gp.computerMove()
print(gp.getBoard())
gp.playerMove(3,3,2)
print(gp.getBoard())
gp.computerMove()
print(gp.getBoard())
gp.playerMove(3,2,2)
print(gp.getBoard())
gp.computerMove()
print(gp.getBoard())'''