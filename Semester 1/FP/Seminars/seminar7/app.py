'''
0. Writing domain classes
1. Unit testing the proper way
2. A new layer? - Repository

Ass 01-05
    UI -> Service -> Domain
        ->Domain
    UI - user interface for entire program
    Service -functions that solve the problem

    !! Repository - manage the list of domain entities
    Domain - entities from problem domain

    => UI-> Serive -> Repository -> Domain
                    -> Domain
'''
from domain import *
from car import *
from rental import *
from repository import *
from service import *
from ui import *


clientRepo = ClientRepository()
clientRepo.store((cl1 := Client(1,"Pop Maria", 20)))
clientRepo.store((cl2 := Client(2,"Vlad Maria", 25)))
#service needs a repo that stores entities
clientService = clientService(clientRepo)
carRepo = Repository()
carRepo.store( (car1 := Car(1, "CJ01ERT", "Dacia", "Lodgy", "red")) )
carRepo.store( (car2 := Car(1, "CJ01XVT", "Vovlo", "XC60", "red")) )

rentalRepo = Repository()
rentalRepo.store(Rental(1,date(2010,11,20), date(2010,11,30), cl1, car1))
rentalRepo.store(Rental(2,date(2016,12,25), date(2017,11,20), cl1, car1))

#Services
carService = CarService(carRepo)
clientService = ClientService(clientRepo)
rentalService = RentalService(rentalRepo)

#UI and start program
ui = UI(carService, clientService, rentalService)
ui.start()