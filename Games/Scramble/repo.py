from domain import *
import random

class FileRepo:
    def __init__(self, filename, readEntity):
        self._entities = []
        self._filename = filename
        self._readEntity = readEntity

    def __readAllfromFile(self):
        self._entities = []
        with open(self._filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self._readEntity(line)
                    self._entities.append(entity)

    def getAll(self):
        self.__readAllfromFile()
        return self._entities

    def selectRandom(self):
        list = self.getAll()
        entity = random.choice(list)
        return entity

    def compute_score(self, sentence):
        words = sentence.Sentence.split(" ")
        spaces = len(words) - 1
        score = len(sentence) - spaces
        sentence.Score = score

    def scrambleSentence(self, sentence):
        copy = sentence.Sentence
        characters = []
        i =0
        while i < len(copy)-1:
            if copy[i+1] == " ":
                i += 3
            else:
                characters.append(copy[i])
                i += 1
        scrambled = copy[0]
        characters.remove(copy[0])
        i = 1
        while i < len(sentence) - 1:
            if sentence.Sentence[i+1] == " ":
                ch1 = sentence.Sentence[i]
                ch2 = sentence.Sentence[i+2]
                scrambled += ch1 + " " + ch2
                i+=3
            else:
                ch = random.choice(characters)
                scrambled += ch
                characters.remove(ch)
                i += 1
        scrambled += sentence.Sentence[len(sentence) - 1]
        sentence.Display = scrambled
        #return scrambled
