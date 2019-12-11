from ui import *
from repository import *
from service import *
from domain import *
from undoController import *
from FileRepository import *
from PickleRepository import *
from JsonRepository import *


def load_properties(filepath, sep= "="):
    '''
    Read the file passed as parameter as a properties file
    '''
    props = {}
    with open(filepath, "rt") as file:
        for line in  file:
            l = line.strip()
            if len(l)!=0 :
                key_value = l.split(sep)
                key = key_value[0].strip()
                value = key_value[1].strip()
                props[key] = value
    return props

def start_program():
    props = load_properties("settings.properties")
    if props['repository'] == 'inmemory':
        studentRepo = Repository()
        disciplineRepo = Repository()
        gradeRepo = GradeRepository()
    elif props['repository'] == 'CSV':
        studentRepo = FileRepository(props['students'], Student.readStudent, Student.writeStudent)
        disciplineRepo = FileRepository(props['disciplines'], Discipline.readDiscipline, Discipline.writeDiscipline)
        gradeRepo = GradeFileRepository(props['grades'], Grade.readGrade, Grade.writeGrade)
    elif props['repository'] == 'binary':
        studentRepo = PickleRepository(props['students'])
        disciplineRepo = PickleRepository(props['disciplines'])
        gradeRepo = GradePickleRepository(props['grades'])
    elif props['repository'] == 'json':
        studentRepo = StudentsJsonRepository(props['students'])
        disciplineRepo = DisciplinesJsonRepository(props['disciplines'])
        gradeRepo= GradesJsonRepository(props['grades'])
    else:
        print("Repo type not avaliable")

    undoController = UndoController()

    studentService = StudentService(studentRepo, undoController)
    disciplineService = DisciplineService(disciplineRepo, undoController)
    gradeService = GradeService(gradeRepo, studentRepo, disciplineRepo, undoController)
    service = Service(undoController)

    ui = UI(studentService, disciplineService, gradeService, service, undoController)
    ui.start()

start_program()

'''
studentRepo = StudentsJsonRepository("studentsRepo.json")
disciplineRepo = DisciplinesJsonRepository("disciplinesRepo.json")
gradeRepo = GradesJsonRepository("gradeRepo.json")

undoController = UndoController()

studentService = StudentService(studentRepo,undoController)
disciplineService = DisciplineService(disciplineRepo,undoController)
gradeService = GradeService(gradeRepo,studentRepo,disciplineRepo,undoController)
service = Service(undoController)

ui = UI(studentService,disciplineService,gradeService,service,undoController)

ui.start()
'''
