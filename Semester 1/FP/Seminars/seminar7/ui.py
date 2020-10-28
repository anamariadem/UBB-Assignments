from service import *

class UI:
    def __init__(self, carService, clientService, rentalService):
        self._carService = carService
        self._clientService = clientService
        self._rentalService = rentalService

    def deleteClient(self):
        '''
        When we delete a client, we delete their rentals
        '''
        try:
            clientID = input("Client id= ")
            self._rentalService.deleteAllRentals(clientID)
            # 1. Find menthod
        except RepositoryException as re:
            print(re)

    # All cars in the car pool sorted by number of days they were rented.
    # 0 days for cars that were never rented

    def _mostRentedCars(self):
        result = self._rentalService.mostRentedCars()
        for r in result:
            print(r)
        # car info -> number of day

    def _rentCar(self):
        try:
            # 1. Determine the client(get client ID)
            clientID = input("Client id= ")
            client = self._clientService(clientID)
            # 2. Determine the car(get car ID)
            carID = input("Car id= ")
            car = self._carService.getCar(carID)
            # 3. Validation
            # 4. Create rental
            rent = Rental(100, date(), date(), client, car)
            self._rentalService.addRental(rent)
        except RepositoryException as re:
            print(re)

    def start(self):
        '''
        Start program, display menu, read user input, call other methods....
        '''
        pass