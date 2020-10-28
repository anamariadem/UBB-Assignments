from datetime import date

from CarController import CarController
from ClientController import ClientController
from RentalController import RentalController
from CarValidator import CarValidator
from Repository import Repository
from ClientValidator import ClientValidator
from RentalValidator import RentalValidator

def statisticsExample():
    """
    An example for the creation of statistics.
    Several cars, clients and rentals are created and then statistics are calculated over them.
    
    Implement the following statistics:
        - "Most rented cars". The list of cars, sorted by the number of times they were rented
        - "Most rented cars". The list of cars, sorted by the number of days they were rented
        - "Most rented car make". The list of car makes, sorted by the number of rentals
    
    Follow the code below and figure out how it works!
    """

    """
        1. We initialize the required layers of the application
    """

    '''
    Start client Controller
    '''
    clientRepo = Repository()
    clientValidator = ClientValidator()
    clientController = ClientController(clientValidator, clientRepo)

    aaron = clientController.create(100, "1820203556699", "Aaron")
    bob = clientController.create(101, "2750102885566", "Bob")
    carol = clientController.create(102, "1820604536579", "Carol")

    '''
    Start car Controller
    '''
    carRepo = Repository()
    carValidator = CarValidator()
    carController = CarController(carValidator, carRepo)

    audiA3 = carController.create(200, "CJ 01 AAA", "Audi", "A3")
    audiA4 = carController.create(201, "CJ 01 BBB", "Audi", "A4")
    audiA5 = carController.create(202, "CJ 01 CCC", "Audi", "A5")
    audiA6 = carController.create(203, "CJ 01 DDD", "Audi", "A6")
    audiA7 = carController.create(204, "CJ 01 EEE", "Audi", "A7")
    vwpolo = carController.create(205, "CJ 01 FFF", "VW", "Polo")
    vwpassat = carController.create(206, "CJ 01 GGG", "VW", "Passat")
    vwgolf = carController.create(207, "CJ 01 HHH", "VW", "Golf")
    dacialodgy = carController.create(208, "CJ 01 ERT", "Dacia", "Lodgy")
    daciaduster = carController.create(209, "CJ 01 YTH", "Dacia", "Duster")

    '''
    Start rental Controller
    '''
    rentRepo = Repository()
    rentValidator = RentalValidator()
    rentController = RentalController(rentValidator, rentRepo, carRepo, clientRepo)

    rentController.createRental(300, aaron, audiA3, date(2015, 11, 20), date(2015, 11, 22))
    rentController.createRental(301, carol, audiA5, date(2015, 11, 24), date(2015, 11, 25))
    rentController.createRental(302, carol, audiA6, date(2015, 12, 10), date(2015, 12, 12))
    rentController.createRental(303, aaron, audiA4, date(2015, 11, 21), date(2015, 11, 25))
    rentController.createRental(304, aaron, audiA3, date(2015, 11, 24), date(2015, 11, 27))
    rentController.createRental(305, bob, audiA5, date(2015, 11, 26), date(2015, 11, 27))
    rentController.createRental(306, carol, audiA6, date(2015, 12, 15), date(2015, 12, 20))
    rentController.createRental(307, bob, audiA4, date(2015, 12, 1), date(2015, 12, 10))
    rentController.createRental(308, carol, audiA4, date(2015, 12, 11), date(2015, 12, 15))
    rentController.createRental(309, aaron, audiA5, date(2015, 11, 28), date(2015, 12, 2))

    rentController.createRental(310, aaron, vwpolo, date(2015, 11, 20), date(2015, 11, 22))
    rentController.createRental(311, carol, vwgolf, date(2015, 11, 24), date(2015, 11, 25))
    rentController.createRental(312, carol, vwpassat, date(2015, 12, 10), date(2015, 12, 12))
    rentController.createRental(313, aaron, dacialodgy, date(2015, 11, 21), date(2015, 11, 25))
    rentController.createRental(314, aaron, vwpolo, date(2015, 11, 24), date(2015, 11, 27))
    rentController.createRental(315, bob, vwgolf, date(2015, 11, 26), date(2015, 11, 27))
    rentController.createRental(316, carol, vwgolf, date(2015, 12, 15), date(2015, 12, 20))
    rentController.createRental(317, bob, daciaduster, date(2015, 12, 1), date(2015, 12, 10))
    rentController.createRental(318, carol, daciaduster, date(2015, 12, 11), date(2015, 12, 15))
    rentController.createRental(319, aaron, vwpassat, date(2015, 11, 28), date(2015, 12, 2))

    """
    Statistic 1:
        - "Most rented cars". The list of cars, sorted by the number of times they were rented
    """
    print("Most rented cars. The list of cars, sorted by the number of times they were rented")
    print("Times".ljust(10) + " Car".ljust(40))
    for cr in rentController.mostOftenRentedCars(): 
        print (cr)

    print("-"*70)

    """
    Statistic 2:
        - "Most rented cars". The list of cars, sorted by the number of days they were rented
    """
    print("Most rented cars. The list of cars, sorted by the number of days they were rented")
    print("Days".ljust(10) + " Car".ljust(40))
    for cr in rentController.mostRentedCars():
        print (cr)

    print("-"*70)
    
    """
    Statistic 3:
        - "Most rented car make". The list of car makes, sorted by the number of rentals
    """
    print("Most rented car make. The list of car makes, sorted by the number of rentals")
    print("Times".ljust(10) + " Car make".ljust(40))
    for cr in rentController.mostOftenRentedCarMake():
        print (cr)

statisticsExample()
















