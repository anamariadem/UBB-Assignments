from service import *
import random
import operator

class UI:
    def __init__(self,service):
        self._service = service

    def initStudents(self):
        for i in range(6):
            s = Student(int(random.choice(list(open('ids.txt')))),random.choice(list(open('namess.txt'))))
            while self._service.isDuplicate(s) == 0:
                s = Student(int(random.choice(list(open('ids.txt')))), random.choice(list(open('namess.txt'))))
            self._service._students.append(s)

    def initDiscipline(self):
        for i in range(3):
            d = Discipline(int(random.choice(list(open('idd.txt')))), random.choice(list(open('namesd.txt'))))
            while self._service.isDuplicateD(d) == 0:
                d = Discipline(int(random.choice(list(open('idd.txt')))), random.choice(list(open('namesd.txt'))))
            self._service._disciplines.append(d)


    def addStudent(self):
        id = input("Give student id: ")
        name = input("Give student name: ")
        newStudent = Student(id,name)
        try:
            self._service.addStudent(newStudent)
        except Exception as ve:
            print(ve)

    def addDiscipline(self):
        id = input("Give discipline id: ")
        name = input("Give discipline name: ")
        newDiscipline = Discipline(id,name)
        try:
            self._service.addDiscipline(newDiscipline)
        except ValueError as ve:
            print(ve)

    def removeStudent(self):
        sid = input("Give id: ")
        try:
            self._service.removeStudent(sid)
        except ValueError as ve:
            print(ve)

    def removeDiscipline(self):
        did = input("Give id: ")
        try:
            self._service.removeDiscipline(did)
        except ValueError as ve:
            print(ve)

    def gradeStudent(self):
        id1 = input("Give student id: ")
        id2 = input("Give discipline id: ")
        grade = input("Give grade: ")
        try:
            self._service.gradeStudent(id1,id2,grade)
        except Exception as e:
            print(e)
            return


    def showStudents(self):
        for i in range(len(self._service._students)):
            print(self._service._students[i])

    def showDisciplines(self):
        for i in range(len(self._service._disciplines)):
            print(self._service._disciplines[i])

    def showGrades(self):
        self._service._grades.sort(key=operator.attrgetter('_sid'))
        for i in range(len(self._service._grades)):
            print(self._service._grades[i])
            print(' ')

    def print_menu(self):
        print("Welcome to Students Catalogue!")
        print("Choose from the list below: ")
        print("1. Add a new student")
        print('2. Add a new discipline')
        print('3. Remove a student with given ID')
        print('4. Remove a discipline with given ID')
        print('5. Grade a student at a discipline')
        print('6 Show grades')
        print('0. Exit')

    def start(self):
        self.print_menu()
        self.initStudents()
        self.initDiscipline()
        while True:
            for i in range(len(self._service._students)):
                print(self._service._students[i])
            print("**********************")
            for i in range(len(self._service._disciplines)):
                print(self._service._disciplines[i])
            choice = input('>')
            if choice == '1':
                self.addStudent()
            elif choice == '2':
                self.addDiscipline()
            elif choice == '3':
                self.removeStudent()
            elif choice == '4':
                self.removeDiscipline()
            elif choice == '5':
                self.gradeStudent()
            elif choice == '6':
                self.showGrades()
            elif choice == '0':
                break
            else:
                print("Bad command")


