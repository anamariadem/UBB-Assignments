from service import Service
from p1 import *




class UI:
    # can the ui do its job without the service?
    #no -> it does not make sense to create a ui without a service
    def __init__(self,service):
        self._service = service


    def addStar(self):
        #read star location, mass, magnitude
        #check star is valid
        #call service.addStar(newStar)
        x = input("Give coord x for location: ")
        y = input("Give coord y for location: ")
        z = input("Give coord z for location: ")
        loc = Location(x,y,z)
        mass = input("Give mass of star: ")
        mag = input("Give mag of star: ")
        try:
            newStar = Star(loc, mass, mag)
            self._service.addStar(newStar)
        except ValueError as ve:
            print(ve)

    def sortStars(self):
        pass

    def print_menu(self):
        print("1. Add a new star to the catalogue")
        print("2. Show all stars, sorted by any of the parameters")
        print("3. Which starts are dangerous for earth? (weight > 10 Sm, AppMagnitude <3")
        print("4. Exit")



    def start(self):
        print("welcome to star catalogue")
        '''
                print menu
                read user' s code
                bla bla bla
                call addStar sortStars methods
                '''
        self.print_menu()
        while True:
            print(self._service._stars)
            cmd = input(">")
            if cmd == '1':
                self.addStar()
            elif cmd == '4':
                return




s = Service()
ui =UI(s)
ui.start()