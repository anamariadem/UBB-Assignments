from repository import *

class CarService:
    def __init__(self, carRepo):
        self._carRepo = carRepo


class ClientService:
    def __init__(self, clientRepo):
        self._rentRepo = clientRepo


# We implement a data transfer object (DTO)


class CarRentalDays:
    def __init__(self, car, days):
        self._car = car
        self._days = days

    def __str__(self):
        return str(self._days) + " - " + str(self._car)


class RentalService:
    def __init__(self, rentalRepo, carRepo, clientRepo):
        self._rentRepo = rentalRepo
        self._carRepo = carRepo
        self._clientRepo = clientRepo

    def getAllRentals(self):
        '''
        Return all rentals
        '''
        pass

    def deleteRental(self, rentalID):
        pass

    def deleteAllRentals(self, clientID):
        '''
        Delete all rentals associated with given client
        '''
        i = 0
        while i < len(self._rentRepo):
            rental = self._rentRepo[i]
            if clientID == rental.client.id:
                self._rentRepo.delete(clientID)
            else:
                i += 1

    def _mostRentedCars(self):
        d = dict()
        # for rental in self._rentRepo --> __iter__
        for i in range(len(self._rentRepo)):
            rent = self._rentRepo[i]  # __getitem__
            if rent.Car not in d:
                # keys are cars, values are the number of rental days
                d[rent.Car] = len(rent)
            else:
                d[rent.Car] += len(rent)

        # cars that were never rented?
        for i in range(len(self._carRepo)):
            car = self._carRepo[i]
            # ...
        # sort the list of CarRentalDays by the _days field