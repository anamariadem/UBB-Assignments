'''
write a ClientRepository class:
    -it keeps a list of clients(private)
    - functions to add a new client (raise ex if client with same id already in repo)
    - function that returns all clients
'''

'''
how to implement repo
    1->Separate Repo Class for each entity (CarRepo, ClientRepo, RentalRepo)
        + Different functionalities for each entity
        - More Code
    2 -> A general Repo Class
        -Only common stuff
        + less code, easier to understand
'''
import copy
from domain import *


class Repository:
    def __init__(self):
        self._data = []

    def size(self):
        return len(self._data)

    def find(self, value):
        if value not in self._data:
            raise ValueError("ID is not in the list!")
        for x in self._data:
            if x.id == value:
                return x

    def store(self, value):
        if value in self._data:
            raise ValueError("ID already in the list!")
        self._data.append(value)

    def delete(self, value):
        self._data.remove(value)

    def __len__(self):
        return len(self._data)

    def __getitem__(self, item):
        return getattr(self,item)


class RepoTest(unittest.TestCase):
    def testRepo(self):
        r = Repository()
        # check length of repo using len()
        self.assertEquals(0, len(r))
        r.store((c := Client(1, "Ana", 19)))
        self.assertEquals(1, len(r))
        # use [] operator to access repo stuff
        self.assertEquals(c, r[0])  # __getitem__
        r.store((c2 := Client(2, "Marius", 20)))
        self.assertEquals(2, len(r))
        self.assertEquals(c, r[0])
        self.assertEquals(c2, r[1])
        # client with id 2 is at index 1
        self.assertEquals(1, r.find(2))
        # trying to add Marius again shoud raise an exception
        self.assertRaises(ValueError, r.store, c2)
        # delete clients from repo
        r.delete(1)
        r.delete(2)
        self.assertEquals(0, len(r))
