from ui import *
from repository import *
from service import *
from domain import *
from undoController import *
studentRepo = Repository()
disciplineRepo = Repository()
gradeRepo = GradeRepository()
undoController = UndoController()

studentService = StudentService(studentRepo,undoController)
disciplineService = DisciplineService(disciplineRepo,undoController)
gradeService = GradeService(gradeRepo,studentRepo,disciplineRepo,undoController)
service = Service(undoController)

ui = UI(studentService,disciplineService,gradeService,service,undoController)

ui.start()
