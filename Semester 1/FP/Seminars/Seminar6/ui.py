from domain import *

class UI:
    def __init__(self, game):
        self._game = game

    def print_menu(self):
        print("Welcome to bulls and cows!")
        print("1. Start new game")
        print("2. Exit")

    def startGame(self):
        self._game.newGame()
        while self._game._done == 0:
            ok = 0
            no = input("Enter your guess: ")
            try:
                self._game.isRepeatedGuess(no)
            except ValueError as e:
                print(e)
                return
            try:
                self._game.userInput(no)
            except Exception as e:
                print(e)
                ok = 1
            if ok == 0:
                try:
                    self._game.guess(no)
                except Exception as e:
                    print(e)
                    return
                print(str(self._game._bulls) + 'B' + str(self._game._cows) + 'C')
                print('')

    def start(self):
        '''
        read user guess
        self._game det if repeated guess
        self._game det the b and c
        :return:
        '''
        self.print_menu()
        while True:
            choice = input(">")
            if choice == '1':
                self.startGame()
            elif choice == '2':
                break
            else:
                print("Invalid input")
