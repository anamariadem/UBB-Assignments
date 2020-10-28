from service import Service
from domain import *

class UI:
    def __init__(self,service):
        self._service = service
    def initList(self):
        self._service._numbers.append(ComplexNumber(5, -1))
        self._service._numbers.append(ComplexNumber(0, -2))
        self._service._numbers.append(ComplexNumber(9, 10))
        self._service._numbers.append(ComplexNumber(13, -5))
        self._service._numbers.append(ComplexNumber(6, 0))
        self._service._numbers.append(ComplexNumber(9, 0))
        self._service._numbers.append(ComplexNumber(-3, -1))
        self._service._numbers.append(ComplexNumber(-5, 7))
        self._service._numbers.append(ComplexNumber(-8, 0))
        self._service._numbers.append(ComplexNumber(0, -10))

    def addNum(self,history):
        r = input("Give real part: ")
        i = input("Give imag part: ")
        try:
            newNum = ComplexNumber(r,i)
            self._service.addNum(newNum,history)
        except ValueError as ve:
            print(ve)

    def showNums(self):
        for i in range(len(self._service._numbers)):
            print(self._service._numbers[i])

    def filterNums(self,history):
        p1 = input("Give start point: ")
        p2 = input("Give end point: ")
        try:
            self._service.filterNums(p1,p2,history)
        except Exception as error:
            print(error)

    def print_menu(self):
        print("1. Add a number to the list")
        print("2. Show the list of numbers on the console.")
        print("3. Filter the list so that it contains only the numbers between indices pstart and pend")
        print("4. Undo the last operation")
        print("5. Exit")

    def start(self):
        self.print_menu()
        self.initList()
        history = []
        while True:
            for i in range(len(self._service._numbers)):
                print(self._service._numbers[i], end = ' ')
            print(' ')
            cmd = input('>')
            if cmd == '1':
                self.addNum(history)
            elif cmd == '2':
                self.showNums()
            elif cmd == '3':
                self.filterNums(history)
            elif cmd == '4':
                if self._service.undo(history) == "No more undos":
                    print("No more undos")
            elif cmd == '5':
                return
            else:
                print("Bad command")

#s = Service()
#ui = UI(s)
ui = UI(Service())
ui.start()
