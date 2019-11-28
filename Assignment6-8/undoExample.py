from exceptions import *
from domain import *
from repository import *
from service import *
from undoController import *
from ui import *

def undoExampleHardest():

    studentRepo = Repository()
    disciplineRepo = Repository()
    gradeRepo = GradeRepository()
    undoController = UndoController()

    studentService = StudentService(studentRepo, undoController)
    disciplineService = DisciplineService(disciplineRepo, undoController)
    gradeService = GradeService(gradeRepo, studentRepo, disciplineRepo, undoController)
    service = Service()
    ui = UI(studentService, disciplineService, gradeService, service, undoController)

    '''
    We add 1 client, 1 car and 2 rentals
    '''

    studentSophia = studentService.add(103,"Sophia")
    disciplineHyundai = disciplineService.add(201, "Hyundai")
    students = studentService.getAll()
    disciplines = disciplineService.getAll()
    gradeService.add(103, 201, 10, students,disciplines)
    gradeService.add(103, 201, 8, students, disciplines)

    print("We added Sophia, the Hyundai and its 2 grades")
    ui.showStudents()
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    gradeService.removeDiscipline("d",201)
    print("Delete the Hyundai (also deletes its grades)")
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")
    '''
    Now undo the performed operations, one by one
    '''
    undoController.undo()
    print("1 undo, the Hyundai and its grades are back")

    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    undoController.undo()
    print("1 undo deletes the second grade")
    ui.showGrades()
    print("*************************")

    undoController.undo()
    print("1 undo deletes the first grade")
    ui.showGrades()
    print("*************************")

    undoController.undo()
    print("1 undo deletes the Hyundai")
    ui.showDisciplines()
    print("*************************")

    '''
    After 5 undos, all repos should be empty, as we did 5 operations in total
    '''
    undoController.undo()
    print("1 undo deletes Sophia (no more undos)")
    ui.showStudents()

    '''
        Redos start here
        '''
    undoController.redo()
    print("1 redo and Sophia is added")
    ui.showStudents()
    print("*************************")

    undoController.redo()
    print("1 redo adds the Hyundai")
    ui.showStudents()
    ui.showDisciplines()
    print("*************************")

    undoController.redo()
    print("1 redo adds the first grade")
    ui.showStudents()
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    undoController.redo()
    print("1 redo adds the second grade")
    ui.showStudents()
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    undoController.redo()
    print("1 redo deletes the Hyundai and its grades (again)")
    ui.showStudents()
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    '''
        Let's do a few undos again...
        '''
    undoController.undo()
    undoController.undo()
    undoController.undo()

    print("3 undos later, we have Sophia and the Hyundai")
    ui.showStudents()
    ui.showDisciplines()
    ui.showGrades()
    print("*************************")

    '''
        Now we try something new - let's add another car!

        NB!
            A new operation must invalidate the history for redo() operations
        '''
    disciplineService.add(202,"Dacia")
    #print("\n Do we have a redo? -", undoController.redo(), "\n")
    '''
        Now we should have 2 cars
        '''
    print("After adding the Dacia, there is no redo ")
    ui.showDisciplines()
    try:
        undoController.redo()
    except ValueError as e:
        print(e)

    '''
        However, undos is still available !
        '''
    undoController.undo()
    print("1 undo deletes the Dacia")
    ui.showDisciplines()
    print("*************************")

    undoController.undo()
    print("1 undo deletes the Hyundai")
    ui.showDisciplines()
    print("*************************")


undoExampleHardest()
