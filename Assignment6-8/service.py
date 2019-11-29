from repository import *
from exceptions import *
import random
from undoController import *
class StudentService:
    def __init__(self,studentRepo,undoController):
        self._studentRepo = studentRepo
        self._undoController = undoController

    def add(self, id, name):
        try:
            newStudent = Student(id,name)
            self._studentRepo.add(newStudent)
            undo = FunctionCall(self.remove, id)
            redo = FunctionCall(self.add, id, name)
            op = Operation(undo,redo)
            self._undoController.recordOperation(op)
        except StudentValueException:
            raise StudentValueException("Used ID")

    def modify_name(self,id,newName):
        try:
            undo = FunctionCall(self.modify_name, id, self._studentRepo.get_name(id))
            redo = FunctionCall(self.modify_name, id, newName)
            op = Operation(undo,redo)
            self._undoController.recordOperation(op)
            self._studentRepo.modify_name(id, newName)
        except StudentValueException:
            raise StudentValueException("ID not in the list")

    def remove(self,id):
        try:
            self._studentRepo.remove(id)
        except StudentValueException:
            raise StudentValueException("ID is not in the list")

    def getAll(self):
        return self._studentRepo.getAll()

    def find(self, id):
        try:
            return self._studentRepo.find(id)
        except StudentValueException:
            raise StudentValueException("ID is not in the list")

    def search_by_name(self,input):
        try:
            return self._studentRepo.search_by_name(input)
        except StudentValueException:
            raise StudentValueException("Name not found!")

    def initStudents(self):
        for i in range(6):
            s = Student(int(random.choice(list(open('ids.txt')))), random.choice(list(open('namess.txt'))).strip())
            while self._studentRepo.isDuplicate(s) == 0:
                s = Student(int(random.choice(list(open('ids.txt')))), random.choice(list(open('namess.txt'))).strip())
            self._studentRepo._data.append(s)

class DisciplineService:
    def __init__(self,disciplineRepo, undoController):
        self._disciplineRepo = disciplineRepo
        self._undoController = undoController

    def add(self,id,name):
        try:
            newDiscipline = Discipline(id,name)
            self._disciplineRepo.add(newDiscipline)
            undo = FunctionCall(self.remove, id)
            redo = FunctionCall(self.add, id, name)
            op = Operation(undo,redo)
            self._undoController.recordOperation(op)
        except StudentValueException:
            raise DisciplineValueException("ID is bot in the list")

    def modify_name(self,id,newName):
        try:
            undo = FunctionCall(self.modify_name, id, self._disciplineRepo.get_name(id))
            redo = FunctionCall(self.modify_name, id, newName)
            op = Operation(undo, redo)
            self._undoController.recordOperation(op)
            self._disciplineRepo.modify_name(id,newName)
        except StudentValueException:
            raise DisciplineValueException("ID is not in the list")
    def remove(self,id):
        try:
            self._disciplineRepo.remove(id)
        except StudentValueException:
            raise DisciplineValueException("ID is not in the list")

    def getAll(self):
        return self._disciplineRepo.getAll()

    def find(self, id):
        try:
            return self._disciplineRepo.find(id)
        except StudentValueException:
            raise DisciplineValueException("ID is not in the list")

    def search_by_name(self,input):
        try:
            return self._disciplineRepo.search_by_name(input)
        except StudentValueException:
            raise DisciplineValueException("Name not found!")

    def initDiscipline(self):
        for i in range(5):
            d = Discipline(int(random.choice(list(open('idd.txt')))), random.choice(list(open('namesd.txt'))).strip())
            while self._disciplineRepo.isDuplicate(d) == 0:
                d = Discipline(int(random.choice(list(open('idd.txt')))), random.choice(list(open('namesd.txt'))).strip())
            self._disciplineRepo._data.append(d)


class GradeService:
    def __init__(self,gradeRepo, studRepo, discRepo, undoController):
        self._gradeRepo = gradeRepo
        self._studentRepo = studRepo
        self._disciplineRepo = discRepo
        self._undoController = undoController

    def add(self, sid,did,value , studentList, disciplineList):
        try:
            grade = Grade(sid,did,value)
            self._gradeRepo.add(grade,studentList,disciplineList)
            undo = FunctionCall(self._gradeRepo.remove_one, grade)
            redo = FunctionCall(self.add, sid,did,value,studentList,disciplineList)
            op = Operation(undo,redo)
            self._undoController.recordOperation(op)
        except GradeValueException:
            raise GradeValueException("ID not found")

    def removeG(self,type, id):
        try:
            return self._gradeRepo.removeG(type,id)
        except GradeValueException:
            raise GradeValueException("Invalid type")

    def removeStudent(self, type, id):
        list =  self._gradeRepo.removeG(type, id)
        undo1 = FunctionCall(self.addGrades, list)
        redo1 = FunctionCall(self.removeG, "s", id)
        op1 = Operation(undo1, redo1)
        s1 = self._studentRepo.find(id)
        undo2 = FunctionCall(self._studentRepo.add, s1)
        redo2 = FunctionCall(self._studentRepo.remove, id)
        op2 = Operation(undo2, redo2)
        cascade = CascadedOperation(op1, op2)
        self._undoController.recordOperation(cascade)
        self._studentRepo.remove(id)

    def removeDiscipline(self, type, id):
        list = self._gradeRepo.removeG(type, id)
        undo1 = FunctionCall(self.addGrades, list)
        redo1 = FunctionCall(self.removeG, "d", id)
        op1 = Operation(undo1, redo1)
        d1 = self._disciplineRepo.find(id)
        undo2 = FunctionCall(self._disciplineRepo.add, d1)
        redo2 = FunctionCall(self._disciplineRepo.remove, id)
        op2 = Operation(undo2, redo2)
        cascade = CascadedOperation(op1, op2)
        self._undoController.recordOperation(cascade)
        self._disciplineRepo.remove(id)

    def addGrades(self,grades):
        self._gradeRepo.addGrades(grades)

    def getAll(self):
        return self._gradeRepo.getAll()


class Service:
    def __init__(self, undoController):
        self._undoController = undoController

    def undo(self):
        self._undoController.undo()

    def redo(self):
        self._undoController.redo()

    def failing_students(self, studentList, disciplineList, gradeList):
        '''
        determines the students that failed at at least one discipline
        :param studentList: the list of students
        :param disciplineList: the list of disciplines
        :param gradeList: the list of grades
        :return: the list of failing students
            raises error if no failing students
        '''
        l = []
        for s in studentList:
            avg = 0
            counter = 0
            for d in disciplineList:
                for g in gradeList:
                    if s.StudId == g.StudId and d.DiscId == g.DiscId:
                        avg = avg + g.GradeValue
                        counter += 1
            if counter > 0:
                avg = avg / counter
                if avg < 5:
                    l.append({"Name": s.StudName, "Discipline": d.DiscName, "Average": avg})

        if len(l) == 0:
            raise GradeValueException("No failing students")
        else:
            return l

    def good_students(self, studentList, disciplineList, gradeList):
        '''
        deternimes the students with the best school situation
        :param studentList: the list of students
        :param disciplineList: the list of disciplines
        :param gradeList: the list of grades
        :return: a list of students sorted in descending order of their aggregated average
            raises error if no good students
        '''
        print(gradeList)
        l = []
        for s in studentList:
            avg = 0
            counter = 0
            for d in disciplineList:
                discAvg = 0
                counter2 = 0
                for g in gradeList:
                    if s.StudId == g.StudId and d.DiscId == g.DiscId:
                        discAvg = discAvg + g.GradeValue
                        counter2 += 1
                if counter2 > 0:
                    discAvg = discAvg / counter2
                    avg = avg + discAvg
                    counter += 1
            if counter > 0:
                avg = avg / counter
                if avg >= 5:
                    l.append({"Name": s.StudName, "Average": avg})
        if len(l) == 0:
            raise GradeValueException("No good students :(")
        else:
            l.sort(key = lambda x: x["Average"], reverse=True)
            return l

    def best_disciplines(self, studentList, disciplineList, gradeList):
        '''
        sorts the disciplines in descending order of the average grade received by all students
        :param studentList: the list of students
        :param disciplineList: the list of disciplines
        :param gradeList: the list of grades
        :return: raises error if the list is empty
        '''
        l = []
        for d in disciplineList:
            avg = 0
            counter = 0
            for s in studentList:
                for g in gradeList:
                    if d._id == g.DiscId and s._id == g.StudId:
                        avg = avg + g.GradeValue
                        counter += 1
            if counter > 0:
                avg /= counter
                l.append({"Name": d.DiscName, "Average": avg})
        if len(l) == 0:
            raise GradeValueException("Empty list")
        else:
            l.sort(key=lambda x: x["Average"], reverse=True)
            return l
