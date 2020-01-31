from gamePlay import *

class UI:
    def __init__(self, gameplay):
        self._gamePlay = gameplay
        self._endGame = False

    def playerMove(self):
        try:
            x = int(input("Give 1st coord: "))
            y = int(input("Give 2nd coord: "))
            symbol = input("Give symbol: ")
            if symbol == "X":
                self._gamePlay.playerMove(x, y, 1)
            elif symbol == "O":
                self._gamePlay.playerMove(x, y, 2)
            else:
                raise IndexError("Invalid symbol")
        except Exception as ve:
            raise IndexError(ve)

    def start(self):
        print("Welcome to Order and Chaos")
        print(self._gamePlay.getBoard())
        self._gamePlay.moveRandom()
        print(self._gamePlay.getBoard())
        turn = "player"
        while self._endGame == False:
            if turn == "computer":
                self._gamePlay.computerMove()
                if self._gamePlay.isWonPlayer() == True:
                    print("Congrats! You won!")
                    self._endGame = True
                elif self._gamePlay.isWonAI() == True:
                    print("You lost :( Order won!")
                    self._endGame = True
                turn = "player"
                print(self._gamePlay.getBoard())
            elif turn == "player":
                try:
                    self.playerMove()
                    if self._gamePlay.isWonPlayer() == True:
                        print("Congrats! You won!")
                        self._endGame = True
                    elif self._gamePlay.isWonAI() == True:
                        print("You lost :( Order won!")
                        self._endGame = True
                    turn = "computer"
                    print(self._gamePlay.getBoard())
                except IndexError as ve:
                    turn = "player"
                    print(ve)
