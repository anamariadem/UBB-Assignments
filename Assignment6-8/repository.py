from domain import *
from exceptions import *
from undoController import *
from iterable_structure import *
class Repository(Structure):
    def __init__(self):
        super().__init__()
        #self._data = []
        #self._data = Structure()

    def add(self, object):
        '''
        adds a new object to the list
        :param object: the object to be added
        :return: the updated list
            -> raises error if same ID
        '''
        for d in self._data:
            if int(d._id) == int(object._id):
                raise StudentValueException("Used ID")
        self._data.append(object)

    def isDuplicate(self,object):
        '''
        checks if an object is in the list
        :param object: the object to be checked
        :return: 0 -> if found, 1-> otherwise
        '''
        for s in self._data:
            if int(s._id) == int(object._id):
                return 0
        for s in self._data:
            if s._name == object._name:
                return 0
        return 1

    def find(self,id): #search
        '''
        finds an object in the list based on its ID
        :param id: the given id
        :return: the object if found, raises error otherwise
        '''
        for s in self._data:
            if int(s._id) == int(id):
                return s
        raise StudentValueException("ID is not in the list!")

    def modify_name(self, id, newName):
        '''
        changes the name of an object based on its ID
        :param id: the given ID
        :param newName: the new name
        :return: raises error if ID not found
        '''
        try:
            s = self.find(id)
            s._name = newName
        except StudentValueException:
            raise StudentValueException("ID is not in the list!")

    def remove(self,id):
        '''
        removes an object from the list based on its ID
        :param id: the given ID
        :return: raises error if ID not found
        '''
        try:
            s = self.find(id)
            self._data.remove(s)
        except StudentValueException:
            raise StudentValueException("ID is not in the list")

    def search_by_name(self, input):
        '''
        searches by name based on an input
        :param input: the given input
        :return: a list with all names containing that input
            raises error if nothing found
        '''
        l = []
        for i in self._data:
            name = i._name.upper()
            if name.find(input.upper()) != -1:
                l.append(i)
        if len(l) > 0:
            return list(l)
        else:
            raise StudentValueException("Name not found!")

    def __len__(self):
        return len(self._data)

    def get_name(self,id):
        '''
        gets the name of an object based on its id
        :param id: the give id
        :return: the corresponding name
        '''
        s = self.find(id)
        return s._name





class GradeRepository:
    def __init__(self):
        self._grades = []

    def add(self, grade, students, disciplines):
        '''
        adds a new grade to the list
        :param grade: the given grade object
        :param students: the list of students
        :param disciplines: the list of disciplines
        :return: the updated list
            raises error if ID not found
        '''
        ok1 = 0
        ok2 = 0
        for s in students:
            if int(s.StudId) == int(grade.StudId):
                ok1 = 1
                break
        for d in disciplines:
            if int(d.DiscId) == int(grade.DiscId):
                ok2 = 1
                break
        if ok1 == ok2 and ok1 == 1:
            self._grades.append(grade)
        else:
            raise GradeValueException("ID not found")

    def removeG(self, type, id):
        '''
        removes grades based on id and type
        :param type: the given type
        :param id: the given id
        :return: the updated list
        '''
        list = []
        if type == "s":
            '''for g in self._grades:
                if int(g.StudID) == int(id):
                    self._grades.remove(g)'''
            for i in range(len(self._grades)-1,-1,-1):
                if int(self._grades[i].StudId) == int(id):
                    list.append(self._grades[i])
                    self._grades.remove(self._grades[i])
        elif type == "d":
            '''for g in self._grades:
                if int(g.DiscID) == int(id):
                    self._grades.remove(g)'''
            for i in range(len(self._grades) - 1, -1, -1):
                if int(self._grades[i].DiscId) == int(id):
                    list.append(self._grades[i])
                    self._grades.remove(self._grades[i])
        else:
            raise GradeValueException("Invalid type")
        return list

    def remove_one(self, grade):
        '''
        removes a single grade from the grade list
        :param grade: the given grade
        :return:
        '''
        for g in self._grades:
            if g  == grade:
                self._grades.remove(g)
                return

    def __len__(self):
        return len(self._grades)

    def getAll(self):
        return self._grades

    def addGrades(self,grades):
        '''

        :param grades:
        :return:
        '''
        for g in grades:
            self._grades.append(g)

