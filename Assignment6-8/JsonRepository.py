from repository import *
import json
import os

class StudentEncoder(json.JSONEncoder):
    def default(self, s):
        if isinstance(s, Student):
            return (s.StudId, s.StudName)
        else:
            return super().default(s)

class DisciplineEncoder(json.JSONEncoder):
    def default(self, d):
        if isinstance(d, Discipline):
            return (d.DiscId, d.DiscName)
        else:
            return super().default(d)

class GradeEncoder(json.JSONEncoder):
    def default(self, g):
        if isinstance(g, Grade):
            return (g.StudId, g.DiscId, g.GradeValue)
        else:
            return super().default(g)


'''encoder = StudentEncoder()
print(encoder.encode(Student(123,"ana")))
Ana = json.dumps(Student(123,"ana"),cls=StudentEncoder)
Marie = json.dumps(Student(124, "Marie"), cls=StudentEncoder)
list = [Ana, Marie]
with open("studentsRepo.json", "w") as file:
    json.dump(list, file)

file.close()

with open("studentsRepo.json", "r") as file:
    data = json.load(file)
    print(data)'''

class StudentsJsonRepository(Repository):
    def __init__(self, filename):
        Repository.__init__(self)
        self._filename = filename
        self._encoder = StudentEncoder()

    def __readAllFromJsonFile(self):
        self._data = []
        with open(self._filename, "r") as file:
            if os.stat(self._filename).st_size == 0:
                return
            list = json.load(file)
        for s in list:
            s = s[1:len(s)-1]
            idx = s.find(",")
            id = int(s[:idx])
            name = s[idx+3:len(s)-1].strip()
            self._data.append(Student(id, name))

    def __writeAllToJsonFile(self):
        list = []
        for s in self._data:
            list.append(self._encoder.encode(s))
        with open(self._filename, "w") as file:
            json.dump(list, file)

    def add(self, entity):
        self.__readAllFromJsonFile()
        Repository.add(self, entity)
        self.__writeAllToJsonFile()

    def remove(self,id):
        self.__readAllFromJsonFile()
        Repository.remove(self, id)
        self.__writeAllToJsonFile()

    def modify_name(self, id, newName):
        self.__readAllFromJsonFile()
        Repository.modify_name(self, id, newName)
        self.__writeAllToJsonFile()

class DisciplinesJsonRepository(Repository):
    def __init__(self, filename):
        Repository.__init__(self)
        self._filename = filename
        self._encoder = DisciplineEncoder()

    def __readAllFromJsonFile(self):
        self._data = []
        with open(self._filename, "r") as file:
            if os.stat(self._filename).st_size == 0:
                return
            list = json.load(file)
        for s in list:
            s = s[1:len(s)-1]
            idx = s.find(",")
            id = int(s[:idx])
            name = s[idx+3:len(s)-1].strip()
            self._data.append(Discipline(id, name))

    def __writeAllToJsonFile(self):
        list = []
        for s in self._data:
            list.append(self._encoder.encode(s))
        with open(self._filename, "w") as file:
            json.dump(list, file)

    def add(self, entity):
        self.__readAllFromJsonFile()
        Repository.add(self, entity)
        self.__writeAllToJsonFile()

    def remove(self,id):
        self.__readAllFromJsonFile()
        Repository.remove(self, id)
        self.__writeAllToJsonFile()

    def modify_name(self, id, newName):
        self.__readAllFromJsonFile()
        Repository.modify_name(self, id, newName)
        self.__writeAllToJsonFile()

class GradesJsonRepository(GradeRepository): # 23,45,ana
    def __init__(self, filename):
        GradeRepository.__init__(self)
        self._filename = filename
        self._encoder = GradeEncoder()

    def __readAllFromJsonFile(self):
        self._grades = []
        with open(self._filename, "r") as file:
            if os.stat(self._filename).st_size == 0:
                return
            list = json.load(file)
        for s in list:
            s = s[1:len(s)-1]
            list = s.split(",")
            sid = int(list[0])
            did = int(list[1])
            value = int(list[2])
            self._grades.append(Grade(sid, did, value))

    def __writeAllToJsonFile(self):
        list = []
        for s in self._grades:
            list.append(self._encoder.encode(s))
        with open(self._filename, "w") as file:
            json.dump(list, file)

    def add(self, grade, students, disciplines):
        self.__readAllFromJsonFile()
        GradeRepository.add(self, grade, students, disciplines)
        self.__writeAllToJsonFile()

    def removeG(self, type, id):
        self.__readAllFromJsonFile()
        list = GradeRepository.removeG(self, type, id)
        self.__writeAllToJsonFile()
        return list

    def remove_one(self, grade):
        self.__readAllFromJsonFile()
        GradeRepository.remove_one(self, grade)
        self.__writeAllToJsonFile()

    def addGrades(self,grades):
        self.__readAllFromJsonFile()
        GradeRepository.addGrades(self, grades)
        self.__writeAllToJsonFile()


