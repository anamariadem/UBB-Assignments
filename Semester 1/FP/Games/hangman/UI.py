from service import *

class UI:
    def __init__(self, service, gamePlay):
        self._service = service
        self._gamePlay = gamePlay
        self._endGame = False

    def printMainMenu(self):
        print("1. Add a new sentence")
        print("2. Start game")
        print("0. Exit")

    def gameMenu(self):
        print("1. Guess a letter")
        print("2. See your guesses")
        print("3. Cheat")
        print("0. Exit")

    def endMessage(self):
        if self._gamePlay.playerWon():
            return "Congrats! You won! :))"
        return "You lost :(("

    def guess(self):
        print(self._gamePlay.SentenceToDisplay)
        letter = input("Guess a letter: ")
        try:
            self._gamePlay.guess(letter)
            print(self._gamePlay.SentenceToDisplay)
            print(self._gamePlay.HangmanToDisplay)
            if self._gamePlay.playerWon() or self._gamePlay.playerLost():
                self._endGame = True
                print(self.endMessage())
        except ValueError as ve:
            print(ve)
            print("Try again")
            self.guess()

    def seeGuesses(self):
        print(self._gamePlay.Guesses)

    def cheat(self):
        print(self._gamePlay.FullSentence)

    def addS(self):
        sentence = input("Give sentence: \n")
        try:
            self._service.addS(sentence)
        except ValueError as ve:
            print(ve)
            print("Try again")
            self.addS()

    def printS(self):
        list = self._service.getAll()
        for l in list:
            print(l)

    def playGame(self):
        while not self._endGame:
            self.gameMenu()
            choice = int(input(">"))
            if choice == 1:
                self.guess()
            elif choice == 2:
                self.seeGuesses()
            elif choice == 3:
                self.cheat()
            elif choice == 0:
                return
            else:
                print("Invalid command!")

    def startApp(self):
        while True:
            self.printMainMenu()
            self.printS()
            choice = int(input(">"))
            if choice == 1:
                self.addS()
                #self.startApp()
            elif choice == 2:
                self.playGame()
            elif choice == 0:
                return
            else:
                print("Invalid choice")