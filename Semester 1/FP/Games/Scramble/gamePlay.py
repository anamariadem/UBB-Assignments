from repo import *

class GamePlay:
    def __init__(self, repo):
        self._repo = repo

    def swap(self, sentence, wordCoord1, letterCoord1, wordCoord2, letterCord2):
        sentence.History = sentence.Display
        copy = sentence.Display
        list = copy.split(" ")
        result = ""
        ch1 = list[wordCoord1][letterCoord1]
        ch2 = list[wordCoord2][letterCord2]
        for i in range(len(list)):
            if i == wordCoord1 and i == wordCoord2:
                if letterCoord1 < letterCord2:
                    result += list[wordCoord1][0:letterCoord1] + ch2 + list[wordCoord1][letterCoord1 + 1: letterCord2] + ch1 + list[wordCoord1][letterCord2 + 1:]
                else:
                    result += list[wordCoord1][0:letterCord2] + ch1 + list[wordCoord1][letterCord2 + 1: letterCoord1] + ch2 + list[wordCoord1][letterCoord1 + 1:]
            elif i == wordCoord1:
                result += list[wordCoord1][0:letterCoord1] + ch2 + list[wordCoord1][letterCoord1 + 1:]
            elif i == wordCoord2:
                result += list[wordCoord2][0:letterCord2] + ch1 + list[wordCoord2][letterCord2 + 1:]
            else:
                result += list[i]
            result += " "
        sentence.Display = result
        sentence.Score -= 1

    def undo(self, sentence):
        if sentence.History == "":
            raise ValueError("Undo not allowed!")
        sentence.Display = sentence.History

    def computeScore(self, sentence):
        self._repo.compute_score(sentence)

    def scrambleSentence(self, sentence):
        self._repo.scrambleSentence(sentence)

    def selectRandom(self):
        return self._repo.selectRandom()

    def isDefeated(self, sentence):
        if sentence.Score == 0:
            return True
        return False

    def isWon(self, sentence):
        if str(sentence.Sentence.strip()) == str(sentence.Display.strip()):
            return True
        return False

    def endGame(self, sentence):
        if self.isWon(sentence) == True or self.isDefeated(sentence) == True:
            return True
        return False
