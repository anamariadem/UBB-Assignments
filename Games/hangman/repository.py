from domain import *
import random
class Repo:
    def __init__(self):
        self._entities = []

    def validateSentence(self, entity):
        sentence = entity.FullSentence
        words = sentence.split(" ")
        if len(words) == 0:
            raise ValueError("Sentence must have at least a word!")
        for w in words:
            if len(w) < 3:
                raise ValueError("Each word must have at least 3 letters!")

        for obj in self._entities:
            if obj.FullSentence == entity.FullSentence:
                raise ValueError("No duplicate sentences!")

    def addS(self, entity):
        self.validateSentence(entity)
        self._entities.append(entity)

    def getAll(self):
        return self._entities

    def giveRandom(self):
        return random.choice(self._entities)

class FileRepo(Repo):
    def __init__(self, filename, readEntity, writeEntity):
        Repo.__init__(self)
        self._filename = filename
        self._readEntity = readEntity
        self._writeEntity = writeEntity

    def __readAllFromFile(self):
        self._entities = []
        with open(self._filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self._readEntity(line)
                    self._entities.append(entity)

    def __writeAllToFile(self):
        with open(self._filename, "w") as file:
            for entity in self._entities:
                file.write(self._writeEntity(entity) + '\n')

    def validateSentence(self, entity):
        Repo.validateSentence(self, entity)

    def addS(self, entity):
        self.__readAllFromFile()
        Repo.addS(self, entity)
        self.__writeAllToFile()

    def getAll(self):
        self.__readAllFromFile()
        return Repo.getAll(self)

    def giveRandom(self):
        return Repo.giveRandom(self)