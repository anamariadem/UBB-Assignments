from exceptions import *



class Student():
    def __init__(self,sid,sname):
        self._id = sid
        self._name = sname

    @property
    def StudId(self):
        return self._id

    @StudId.setter
    def StudId(self,value):
        self.StudId = value
    @property
    def StudName(self):
        return self._name

    @StudName.setter
    def StudName(self,sname):
        ok = 1
        for i in range(len(sname)):
            if sname[i] >= '0' and sname[i] <='9':
                ok = 0
        if ok == 0:
            raise StudentValueException("Name must contain only letters")
        self._name = sname

    def __eq__(self, other):
        return self._id == other._id

    def __str__(self):
        return  'ID:'.ljust(5)+ str(self.StudId).ljust(5) + ' Name: '.ljust(6)+ str(self.StudName)


class Discipline():
    def __init__(self, did, dname):
        self._id = did
        self._name = dname

    @property
    def DiscId(self):
        return self._id

    @DiscId.setter
    def DiscId(self,value):
        self.DiscId = value

    @property
    def DiscName(self):
        return self._name

    @DiscName.setter
    def DiscName(self, sname):
        for i in range(len(sname)):
            if sname[i]>='0' and sname[i] <='9':
                raise DisciplineValueException("Name must contain only letters")
        self._name = sname

    def __eq__(self, other):
        return self._id == other._id

    def __str__(self):
        return 'ID: '.ljust(5) + str(self.DiscId).ljust(5)  + 'Name: '.ljust(6)+ str(self.DiscName)


class Grade():
    def __init__(self,studId, discId,grade):
        self._sid = studId
        self._did = discId
        self._grade = grade

    @property
    def StudId(self):
        return self._sid

    @StudId.setter
    def StudId(self,value):
        self.StudId = value

    @property
    def DiscId(self):
        return self._did

    @DiscId.setter
    def DiscId(self, value):
        self.DiscId = value

    @property
    def GradeValue(self):
        return self._grade
    @GradeValue.setter
    def GradeValue(self,value):
        if int(value) < 1 or int(value) > 10:
            raise GradeValueException("Invalid grade")
        self._grade = value

    def __repr__(self):
        return 'Student ID: '.ljust(10) + str(self._sid).ljust(5)+ ' Discipline ID: ' + str(self._did).ljust(3) + " Grade: " + str(self._grade)
