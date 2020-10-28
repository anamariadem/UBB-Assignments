from domain import *

class Service:
    def __init__(self):
        self._numbers = []

    def addNum(self,complex_num,history):
        '''
        adds a new complex number to the list
        :param complex_num: the number to be added
        :param history: the list of previous lists
        :return: appends the number to the list- if valid
            raises ValueError- otherwise
        '''
        for c in self._numbers:
            if c.RealPart == complex_num.RealPart and c.ImagPart == complex_num.ImagPart:
                raise ValueError("Number is already in the list")
        history.append(self._numbers[:])
        self._numbers.append(complex_num)

    def test_addNum(self):
        try:
            newNum = ComplexNumber('e',4)
            assert False
        except Exception as error:
            assert True
        self._numbers = [ComplexNumber(4,-2)]
        history = []
        try:
            self.addNum(ComplexNumber(4,-2),history)
            assert False
        except ValueError:
            assert True

    def showNums(self):
        return self._numbers

    def filterNums(self,p1,p2,history):
        '''
        filters the list- it contains only the numbers between indices pstart and pend
        :param p1: the starting point
        :param p2: the ending point
        :param history: the list of previous lists
        :return: the updated list
            raises TypeError - if p1 or p2 is invalid
            raises ValueError - if index is invalid
        '''
        try:
            p1 = int(p1)
            p2 = int(p2)
        except ValueError:
            raise ValueError("Positions are not integers")
        if p1 >= len(self._numbers) or p2 >= len(self._numbers):
            raise ValueError("Index out of range")
        if p1 > p2:
            raise ValueError("Start position is greater than end position")
        history.append(self._numbers[:])
        for i in range(p1-1,-1,-1):
            self._numbers.remove(self._numbers[i])
            p2 = p2-1
        for i in range(len(self._numbers)-1,p2,-1):
            self._numbers.remove(self._numbers[i])

    def test_filterNums(self):
        p1 = 'e'
        p2 = 4
        h = []
        try:
            self.filterNums(p1,p2,h)
            assert False
        except ValueError:
            assert True
        p1 = 7
        p2 = 4
        h = []
        try:
            self.filterNums(p1, p2, h)
            assert False
        except ValueError:
            assert True

    def undo(self,history):
        if len(history) == 0:
            return "No more undos!"
        self._numbers.clear()
        self._numbers.extend(history.pop())


s = Service()
Service.test_addNum(s)
Service.test_filterNums(s)