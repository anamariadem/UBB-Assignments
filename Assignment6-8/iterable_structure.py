from domain import *

class Structure:
    def __init__(self):
        self._data = []

    def __iter__(self):
        return StructureIterator(self)

    def __getitem__(self, item):
        return self._data[item]

    def __setitem__(self, key, value):
        self._data[key] = value

    def __delitem__(self, key):
        self._data.remove(self._data[key])

    def compare(self, object1, object2, sign, attribute):
        if isinstance(object1, Student) and isinstance(object2, Student):
            if attribute == "id":
                if sign == "ascending":
                    if object1.StudId < object2.StudId:
                        return 0
                    return 1
                else:
                    if object1.StudId > object2.StudId:
                        return 0
                    return 1
            elif attribute == "name":
                if sign == "ascending":
                    if object1.StudName < object2.StudName:
                        return 0
                    return 1
                else:
                    if object1.StudName > object2.StudName:
                        return 0
                    return 1

        if isinstance(object1, Discipline) and isinstance(object2, Discipline):
            if attribute == "id":
                if sign == "ascending":
                    if object1.DiscId < object2.DiscId:
                        return 0
                    return 1
                else:
                    if object1.DiscId > object2.DiscId:
                        return 0
                    return 1
            elif attribute == "name":
                if sign == "ascending":
                    if object1.DiscName < object2.DiscName:
                        return 0
                    return 1
                else:
                    if object1.DiscName > object2.DiscName:
                        return 0
                    return 1

    def sort(self, sign, attribute):
        # gnome sort
        pos = 0
        while pos < len(self._data):
            if pos == 0 or self.compare(self._data[pos], self._data[pos - 1], sign, attribute) == 1:
                pos +=1
            else:
                aux = self._data[pos]
                self._data[pos] = self._data[pos-1]
                self._data[pos - 1] = aux
                pos -=1

    def checkFilterCondition(self, object, sign, value):
        if isinstance(object, Student):
            if sign == "<":
                if object.StudId < value:
                    return True
                return False
            elif sign == ">":
                if object.StudId > value:
                    return True
                return False
        if isinstance(object, Discipline):
            if sign == "<":
                if object.DiscId < value:
                    return True
                return False
            elif sign == ">":
                if object.DiscId > value:
                    return True
                return False

    def filter(self, sign, value):
        for i in range(len(self._data)-1, -1, -1):
            if self.checkFilterCondition(self._data[i], sign, value) == False:
                self.__delitem__(i)

    def append(self, object):
        self._data.append(object)


class StructureIterator:
    def __init__(self, structure):
        self._structure = structure
        self._index = 0

    def __next__(self):
        if self._index < len(self._structure._data):
            result = self._structure._data[self._index]
            self._index += 1
            return result
        raise StopIteration

'''s = Structure()
s.append(Discipline(23, "Ana"))
s.append(Discipline(3, "Maria"))
s.append(Discipline(300, "Math"))
sign = ">"
value = 100
s.filter(sign, value)
for i in s:
    print(i)
'''

