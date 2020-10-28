from domain1 import *

class Service():
    def __init__(self):
        self._students = []
        self._disciplines = []
        self._grades = []

    def addStudent(self,newStudent):
        '''
        Adds a new student to the list
        :param newStudent: the new student
        :return: the updated list
        '''

        for s in self._students:
            if int(s._id) == int(newStudent._id):
                raise ValueError("There is another student with that id")
        self._students.append(newStudent)

    def isDuplicate(self,newStudent):
        for s in self._students:
            if int(s._id) == int(newStudent._id):
                return 0
        for s in self._students:
            if s._name == newStudent._name:
                return 0

    def addDiscipline(self,newDiscipline):
        '''

        :param newDiscipline:
        :return:
        '''
        for d in self._disciplines:
            if int(d.DiscId) == int(newDiscipline.DiscId):
                raise ValueError("There is another discipline with that id")
        self._disciplines.append(newDiscipline)

    def isDuplicateD(self,newDiscipline):
        for s in self._disciplines:
            if int(s._id) == int(newDiscipline._id):
                return 0
        for s in self._disciplines:
            if s._name == newDiscipline._name:
                return 0

    def findStud(self,sid):
        #stud = Student(sid,sname)
        for s in self._students:
            if int(s._id) == int(sid):
                return s
        raise ValueError

    def findDisc(self,did):
        for d in self._disciplines:
            if int(d._id) == int(did):
                return d
        raise ValueError

    def removeStudent(self,sid):
        '''

        :param sid:
        :return:
        '''
        try:
            s = self.findStud(sid)
            self._students.remove(s)
            for i in range(len(self._grades)-1,-1,-1):
                if int(self._grades[i]._sid) == int(sid):
                    self._grades.remove(self._grades[i])
        except ValueError:
            raise ValueError("Student is not in the list")


    def removeDiscipline(self,did):
        '''

        :param did:
        :return:
        '''
        try:
            d = self.findDisc(did)
            self._disciplines.remove(d)
            for i in range(len(self._grades) - 1, -1, -1):
                if int(self._grades[i]._did) == int(did):
                    self._grades.remove(self._grades[i])
        except ValueError:
            raise ValueError("Discipline is not in the list")

    def gradeStudent(self,sid,did,grade):
        '''

        :param grade:
        :return:
        '''
        try:
            stud = self.findStud(sid)
        except ValueError:
            raise ValueError("Student is not in list")
        try:
            disc = self.findDisc(did)
        except ValueError:
            raise ValueError("Discipline is not in list")
        if int(grade) < 0 or int(grade) > 10:
            raise ValueError('The grade must be between 1 and 10!')
        self._grades.append(Grade(sid,did,grade))


