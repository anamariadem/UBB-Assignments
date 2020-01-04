from main import *
from gui import *
def startGame():
    while True:
        choice = int(input("Console / GUI (0/1): "))
        if choice not in [0,1]:
            print("print invalid command")
            break
        if choice == 0:
            game = Game()
            ai = AI()
            cp = ComputerPlyer(ai)
            ui = UI(game, cp)
            ui.start()
        elif choice == 1:
            game = Game()
            ai = AI()
            cp = ComputerPlyer(ai)
            gui = GUI(game, cp)
            gui.start()

startGame()
