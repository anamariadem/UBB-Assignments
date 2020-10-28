
class Student():
    def __init__(self,sid,sname):
        self._id = sid
        self._name = sname

    @property
    def StudId(self):
        return self._id

    @StudId.setter
    def StudId(self,value):
        try:
            self._id = int(value)
        except ValueError:
            raise ValueError("ID input is  not  an integer number")

    @property
    def StudName(self):
        return self._name
    @StudName.setter
    def StudName(self,sname):
        self._name = sname

    def __str__(self):
        return  'ID:' + str(self.StudId) + ' Name:'+ str(self.StudName)


class Discipline():
    def __init__(self, did, dname):
        self._id = did
        self._name = dname

    @property
    def DiscId(self):
        return self._id

    @DiscId.setter
    def DiscId(self, value):
        try:
            self._id = int(value)
        except ValueError:
            raise ValueError("ID input is  not  an integer number")

    @property
    def DiscName(self):
        return self._name

    @DiscName.setter
    def DiscName(self, sname):
        self._name = sname

    def __str__(self):
        return 'ID: ' + str(self.DiscId)  + ' '+ str(self.DiscName)


class Grade():
    def __init__(self,studId, discId,grade):
        self._sid = studId
        self._did = discId
        self._grade = grade

    def __str__(self):
        return 'Student ID: ' + str(self._sid) + ', Discipline ID: ' + str(self._did) + ", Grade:" + str(self._grade)









