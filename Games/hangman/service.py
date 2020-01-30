from repository import *

class Service:
    def __init__(self, repo):
        self._repo = repo

    def addS(self, sentenceString):
        sentence = Sentence(sentenceString)
        self._repo.addS(sentence)

    def getAll(self):
        return self._repo.getAll()

class PlayerController:
    def __init__(self, sentence):
        self._sentence = sentence
        self._hangman = "hangman"
        self._hangmanToDisplay = ""
        self._guesses = []
        self._noWrongGuesses = 0

    @property
    def Sentence(self):
        return self._sentence
    @Sentence.setter
    def Sentence(self, value):
        self._sentence = value
    @property
    def FullSentence(self):
        return self._sentence.FullSentence

    @FullSentence.setter
    def FullSentence(self, sentence):
        self._sentence.FullSentence = sentence
    @property
    def SentenceToDisplay(self):
        return self._sentence.SentenceToDisplay
    @property
    def Hangman(self):
        return self._hangman
    @property
    def HangmanToDisplay(self):
        return self._hangmanToDisplay
    @property
    def Guesses(self):
        return self._guesses

    def initializeSentence(self):
        firstChar = self._sentence.FullSentence[0]
        lastChar = self._sentence.FullSentence[-1]
        self._guesses.append(firstChar)
        self._guesses.append(lastChar)

        for ch in self._sentence.FullSentence:
            if ch in [firstChar, lastChar, " "]:
                self._sentence.SentenceToDisplay += ch
            else:
                self._sentence.SentenceToDisplay += "_"

    def fillSentence(self, letter):
        for i in range(len(self._sentence.FullSentence)):
            if self._sentence.FullSentence[i] == letter:
                self._sentence.SentenceToDisplay = self._sentence.SentenceToDisplay[:i] + letter + self._sentence.SentenceToDisplay[i+1:]

    def fillHangman(self):
        self._hangmanToDisplay += self._hangman[self._noWrongGuesses]
        self._noWrongGuesses += 1

    def guess(self, letter):
        if len(letter) != 1:
            raise ValueError("Guess must be a letter! (lenght 1)")
        if letter < 'a' or letter > 'z':
            raise ValueError("Guess must be a letter!")
        if letter in self._guesses:
            raise ValueError("You've already tried to guess this letter")

        if letter in self._sentence.FullSentence:
            self.fillSentence(letter)
        else:
            self.fillHangman()
        self._guesses.append(letter)


class GamePlay:
    def __init__(self, repo, playerController):
        self._repo = repo
        self._playerController = playerController

    @property
    def FullSentence(self):
        return self._playerController.FullSentence

    @property
    def SentenceToDisplay(self):
        return self._playerController.SentenceToDisplay

    @property
    def HangmanToDisplay(self):
        return self._playerController.HangmanToDisplay

    @property
    def Guesses(self):
        return self._playerController.Guesses

    def guess(self, letter):
        self._playerController.guess(letter)

    def playerWon(self):
        if self._playerController.FullSentence == self._playerController.SentenceToDisplay:
            return True
        return False

    def playerLost(self):
        if self._playerController.Hangman == self._playerController.HangmanToDisplay:
            return True
        return False

    def chooseSentence(self):
        list = self._repo.getAll()
        choice = random.choice(list)
        self._playerController.Sentence = choice
