class StudentException(Exception):
    def __init__(self,msg):
        Exception.__init__(self,msg)

class StudentValueException(StudentException):
    def __init__(self,msg):
        StudentException.__init__(self,msg)

class DisciplineException(Exception):
    def __init__(self,msg):
        Exception.__init__(self,msg)

class DisciplineValueException(DisciplineException):
    def __init__(self,msg):
        DisciplineException.__init__(self,msg)

class GradeException(Exception):
    def __init__(self,msg):
        Exception.__init__(self,msg)

class GradeValueException(GradeException):
    def __init__(self,msg):
        DisciplineException.__init__(self,msg)