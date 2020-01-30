from repo import *
from gamePlay import GamePlay

class UI:
    def __init__(self, gameplay):
        self._gamePlay = gameplay
        self._endGame = False

    def readCommand(self):
        command = input(">")
        idx = command.find(" ")
        if idx == -1:
            if command == "undo" or command == "exit":
                return (command, None, None, None)
            else:
                raise ValueError("Invalid command")
        else:
            cmd = command[:idx]
            if cmd!= "swap":
                raise ValueError("Invalid command")
            command = command[idx + 1:]
            list = command.split(" ")
            for l in list:
                l = l.strip()
            if len(list)!=5:
                raise ValueError("Invalid nr of params")
            return (cmd, int(list[0]), int(list[1]), int(list[3]), int(list[4]))

    def swap(self, sentence, wordCoord1, letterCoord1, wordCoord2, letterCord2):
        self._gamePlay.swap(sentence, wordCoord1, letterCoord1, wordCoord2, letterCord2)
        print(sentence.Display.strip() + " score is: " + str(sentence.Score))

    def undo(self, sentence):
        try:
            self._gamePlay.undo(sentence)
            print(sentence.Display.strip() + " score is: " + str(sentence.Score))
        except ValueError as ve:
            print(ve)

    def validateParams(self, sentence, wordCoord1, letterCoord1, wordCoord2, letterCord2):
        list = sentence.Sentence.split(" ")
        if wordCoord1 >= len(list) or wordCoord2 >= len(list):
            raise ValueError("Invalid word indexes")
        if letterCoord1 >= len(list[wordCoord1]) or letterCord2 >= len(list[wordCoord2]):
            raise ValueError("Invalid letter indexes")

    def start(self):
        print("Welcome to Sramble!")
        sentence = self._gamePlay.selectRandom()
        #print(sentence)
        self._gamePlay.computeScore(sentence)
        self._gamePlay.scrambleSentence(sentence)
        if sentence.Sentence.strip() == sentence.Display.strip():
            self._gamePlay.scrambleSentence(sentence)
        print(sentence.Display)
        while self._endGame == False:
            try:
                tuple = self.readCommand()
                command = tuple[0]
                if command == "swap":
                    self.validateParams(sentence, tuple[1], tuple[2], tuple[3], tuple[4])
                    self.swap(sentence, tuple[1], tuple[2], tuple[3], tuple[4])
                    if self._gamePlay.endGame(sentence) == True:
                        self._endGame = True
                        if self._gamePlay.isWon(sentence) == True:
                            print("Congrats!! You won! :)")
                        if self._gamePlay.isDefeated(sentence) == True:
                            print("You were defeated! :(")
                elif command == "undo":
                    self.undo(sentence)
                elif command == "exit":
                    return
            except ValueError as ve:
                print(ve)
                continue
