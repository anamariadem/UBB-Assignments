from repository import *
import pickle

class PickleRepository(Repository):
    def __init__(self, filename):
        Repository.__init__(self)
        self._filename = filename

    def __readAllFromBinaryFile(self):
        self._data = []
        try:
            with open(self._filename, "rb") as file:
                self._data = pickle.load(file)
        except EOFError:
            return
        #file.close()

    def __writeAllToBinaryFile(self):
        with open(self._filename, "wb") as file:
            pickle.dump(self._data, file)
        file.close()

    def add(self, entity):
        self.__readAllFromBinaryFile()
        Repository.add(self, entity)
        self.__writeAllToBinaryFile()

    def modify_name(self, id, newName):
        self.__readAllFromBinaryFile()
        Repository.modify_name(self, id, newName)
        self.__writeAllToBinaryFile()

    def remove(self, id):
        self.__readAllFromBinaryFile()
        Repository.remove(self, id)
        self.__writeAllToBinaryFile()

class GradePickleRepository(GradeRepository):
    def __init__(self, filename):
        GradeRepository.__init__(self)
        self._filename = filename

    def __readAllFromBinaryFile(self):
        self._grades = []
        try:
            with open(self._filename, "rb") as file:
                self._grades = pickle.load(file)
        except EOFError:
            return

    def __writeAllToBinaryFile(self):
        with open(self._filename, "wb") as file:
            pickle.dump(self._grades, file)
        file.close()

    def add(self, grade, students, disciplines):
        self.__readAllFromBinaryFile()
        GradeRepository.add(self, grade, students, disciplines)
        self.__writeAllToBinaryFile()

    def removeG(self, type, id):
        self.__readAllFromBinaryFile()
        list = GradeRepository.removeG(self, type, id)
        self.__writeAllToBinaryFile()
        return list

    def remove_one(self, grade):
        self.__readAllFromBinaryFile()
        GradeRepository.remove_one(self, grade)
        self.__writeAllToBinaryFile()

    def addGrades(self,grades):
        self.__readAllFromBinaryFile()
        GradeRepository.addGrades(self, grades)
        self.__writeAllToBinaryFile()
