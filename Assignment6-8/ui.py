from service import *
from exceptions import *
import operator
import random
from undoController import *
class UI:
    def __init__(self, studentService, disciplineService, gradeService, service, undoController):
        self._studentService = studentService
        self._disciplineService = disciplineService
        self._gradeService = gradeService
        self._service = service
        self._undoController = undoController

    def initGrades(self):
        for i in range(10):
            students = self._studentService.getAll()
            disciplies = self._disciplineService.getAll()
            stud = random.choice(students)
            disc = random.choice(disciplies)
            value = random.randint(1,10)
            grade = Grade(stud.StudId,disc.DiscId,value)
            self._gradeService._gradeRepo.add(grade,students,disciplies)


    def addStudent(self):
        id = int(input("Give student id: "))
        name = input("Give student name: ")
        #newStudent = Student(id,name)
        try:
            self._studentService.add(id,name)
        except Exception as ve:
            print(ve)

    def addDiscipline(self):
        id = int(input("Give discipline id: "))
        name = input("Give discipline name: ")
        #newDiscipline = Discipline(id,name)
        try:
            self._disciplineService.add(id,name)
        except Exception as ve:
            print(ve)

    def addGrade(self):
        sid = int(input("Give student id: "))
        did = int(input("Give discipline id: "))
        value = int(input("Give grade value: "))
        if int(value) < 1 or int(value) > 10:
            print("Invalid grade value")
        students = self._studentService.getAll()
        disciplines = self._disciplineService.getAll()
        try:
            self._gradeService.add(sid,did,value,students,disciplines)
        except Exception as e:
            print(e)

    def modify_name(self):
        id = int(input('Give student id: '))
        name = input('Give new name: ')
        try:
            self._studentService.modify_name(id,name)
        except Exception as e:
            print(e)

    def modify_nameD(self):
        id = int(input('Give discipline id: '))
        name = input('Give new name: ')
        try:
            self._disciplineService.modify_name(id,name)
        except Exception as e:
            print(e)

    '''def removeStudent(self):
        sid = int(input("Give student id: "))
        try:
            list = self._gradeService.removeG("s", sid)
            undo1 = FunctionCall(self._gradeService.addGrades, list)
            redo1 = FunctionCall(self._gradeService.removeG, "s",sid)
            op1 = Operation(undo1,redo1)
            s1 = self._studentService.find(sid)
            undo2 = FunctionCall(self._studentService.add, sid, s1.StudName)
            redo2 = FunctionCall(self._studentService.remove,sid)
            op2 = Operation(undo2,redo2)
            cascade = CascadedOperation(op1,op2)
            self._undoController.recordOperation(cascade)
            self._studentService.remove(sid)
        except Exception as e:
            print(e)'''

    def removeStudent(self):
        sid = int(input("Give student id: "))
        try:
            self._gradeService.removeStudent("s",sid)
        except StudentValueException as e:
            print(e)

    def removeDiscipline(self):
        did = int(input("Give discipline id: "))
        try:
            self._gradeService.removeDiscipline("d",did)
        except StudentValueException as e:
            print(e)

    '''def removeDiscipline(self):
        did = int(input("Give discipline id: "))
        try:
            list =self._gradeService.removeG("d",did)
            undo1 = FunctionCall(self._gradeService.addGrades, list)
            redo1 = FunctionCall(self._gradeService.removeG, "d", did)
            op1 = Operation(undo1,redo1)
            d1 = self._disciplineService.find(did)
            undo2 = FunctionCall(self._disciplineService.add, did, d1.DiscName)
            redo2 = FunctionCall(self._disciplineService.remove,did)
            op2 = Operation(undo2,redo2)
            cascade = CascadedOperation(op1,op2)
            self._undoController.recordOperation(cascade)
            self._disciplineService.remove(did)
        except Exception as e:
            print(e)'''

    def search_students(self):
        user = input("Give ID or name: ")
        try:
            user = int(user)
            try:
                s = self._studentService.find(user)
                print(s)
            except Exception as e:
                print(e)
        except:
            try:
                students = self._studentService.search_by_name(user)
                for s in students:
                    print(s)
            except StudentValueException as e:
                print(e)

    def search_disciplines(self):
        user = input("Give ID or name: ")
        try:
            user = int(user)
            try:
                s = self._disciplineService.find(user)
                print(s)
            except Exception as e:
                print(e)
        except:
            try:
                disciplines = self._disciplineService.search_by_name(user)
                for s in disciplines:
                    print(s)
            except DisciplineValueException as e:
                print(e)

    def failing_students(self):
        try:
            studentList = self._studentService.getAll()
            disciplineList = self._disciplineService.getAll()
            gradeList = self._gradeService.getAll()
            print(gradeList)
            list = self._service.failing_students(studentList,disciplineList,gradeList)
            for l in list:
                print("Name: ".ljust(12) + l["Name"] + "Discipline: ".ljust(12) + l["Discipline"] + "Average: ".ljust(12) + str(l["Average"]))
                print()
        except GradeValueException as e:
            print(e)

    def good_students(self):
        try:
            studentList = self._studentService.getAll()
            disciplineList = self._disciplineService.getAll()
            gradeList = self._gradeService.getAll()
            list = self._service.good_students(studentList, disciplineList, gradeList)
            for l in list:
                print("Name: ".ljust(12) + l["Name"] + "Average: ".ljust(12)+ str(l["Average"]))
                print()
        except GradeValueException as e:
            print(e)

    def best_disciplines(self):
        try:
            studentList = self._studentService.getAll()
            disciplineList = self._disciplineService.getAll()
            gradeList = self._gradeService.getAll()
            list = self._service.best_disciplines(studentList,disciplineList,gradeList)
            for l in list:
                print("Name: ".ljust(12) + l["Name"] + "Average: ".ljust(12) + str(l["Average"]))
                print()
        except GradeValueException as e:
            print(e)

    def undo(self):
        try:
            self._undoController.undo()
        except ValueError as e:
            print(e)

    def redo(self):
        try:
            self._undoController.redo()
        except ValueError as e:
            print(e)

    def showStudents(self):
        students = self._studentService.getAll()
        students.sort(key = lambda x: int(x._id))
        for s in students:
            print(s)

    def showDisciplines(self):
        disciplines = self._disciplineService.getAll()
        disciplines.sort(key = lambda x: int(x._id))
        for d in disciplines:
            print(d)

    def showGrades(self):
        grades = self._gradeService.getAll()
        grades.sort(key= lambda x: (int(x._sid),int(x._did)))
        for g in grades:
            print(g)

    def print_menu(self):
        print("Welcome to Students Catalogue!")
        print("Choose from the list below: ")
        print("1.  Add a new student")
        print('2.  Add a new discipline')
        print('3.  Remove a student with given ID')
        print('4.  Remove a discipline with given ID')
        print('5.  Grade a student at a discipline')
        print('6.  Update a student s name')
        print('7.  Update a discipline s name')
        print('8.  Show grades')
        print('9.  Search for students based on ID or name')
        print('10. Search for disciplines based on ID or name')
        print('11. Show all students failing at one or more disciplines')
        print('12. Show students with the best school situation')
        print('13. Show disciplines sorted in descending order of the average grade')
        print('14. Undo the last operation')
        print('15. Redo the last operation')
        print('0.  Exit')

    def start(self):
        self._studentService.initStudents()
        self._disciplineService.initDiscipline()
        self.initGrades()
        while True:
            self.print_menu()
            self.showStudents()
            print('********************')
            self.showDisciplines()
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
                self.addGrade()
            elif choice == '6':
                self.modify_name()
            elif choice == '7':
                self.modify_nameD()
            elif choice == '8':
                self.showGrades()
            elif choice == '9':
                self.search_students()
            elif choice == '10':
                self.search_disciplines()
            elif choice == '11':
                self.failing_students()
            elif choice == '12':
                self.good_students()
            elif choice == '13':
                self.best_disciplines()
            elif choice == '14':
                self.undo()
            elif choice == '15':
                self.redo()
            elif choice == '0':
                return
            else:
                print("Bad command")






