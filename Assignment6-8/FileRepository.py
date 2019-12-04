from repository import *

class FileRepository(Repository):
    def __init__(self, fileName, readEntity, writeEntity):
        Repository.__init__(self)
        self.__filename = fileName
        self.__readEntity = readEntity
        self.__writeEntity = writeEntity

    def __readAllFromFile(self):
        self._data = []
        with open(self.__filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self.__readEntity(line)
                    self._data.append(entity)
        file.close()

    def __writeAllToFile(self):
        with open(self.__filename, "w") as file:
            for entity in self._data:
                file.write(self.__writeEntity(entity) + "\n")
        file.close()

    def add(self, entity):
        self.__readAllFromFile()
        Repository.add(self, entity)
        self.__writeAllToFile()

    def modify_name(self, id, newName):
        self.__readAllFromFile()
        Repository.modify_name(self, id, newName)
        self.__writeAllToFile()

    def remove(self, id):
        self.__readAllFromFile()
        Repository.remove(self, id)
        self.__writeAllToFile()


class GradeFileRepository(GradeRepository):
    def __init__(self, fileName, readEntity, writeEntity):
        GradeRepository.__init__(self)
        self.__filename = fileName
        self.__readEntity = readEntity
        self.__writeEntity = writeEntity

    '''def __readAllfromFile(self):
        self._grades = []
        with open(self.__filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    params = line.split(",")
                    
                    grade = Grade(*params)
                    self._grades.append(grade)
        file.close()
    
    def __writeAllToFile(self):
        with open(self.__filename, "w") as file:
            for entity in self._grades:
                pass
        file.close()'''


    def __readAllFromFile(self):
        self._grades = []
        with open(self.__filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self.__readEntity(line)
                    self._grades.append(entity)
        file.close()


    def __writeAllToFile(self):
        with open(self.__filename, "w") as file:
            for entity in self._grades:
                file.write(self.__writeEntity(entity) + "\n")
        file.close()

    def add(self, grade, students, disciplines):
        self.__readAllFromFile()
        GradeRepository.add(self, grade, students, disciplines)
        self.__writeAllToFile()

    def removeG(self, type, id):
        self.__readAllFromFile()
        list = GradeRepository.removeG(self, type, id)
        self.__writeAllToFile()
        return list

    def remove_one(self, grade):
        self.__readAllFromFile()
        GradeRepository.remove_one(self, grade)
        self.__writeAllToFile()

    def addGrades(self,grades):
        self.__readAllFromFile()
        GradeRepository.addGrades(self, grades)
        self.__writeAllToFile()






