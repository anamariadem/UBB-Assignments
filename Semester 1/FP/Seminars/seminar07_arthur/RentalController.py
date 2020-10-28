from CarRentalException import CarRentalException
from Rental import Rental

class RentalController:
    """
    Controller for rental operations
    """
    def __init__(self, validator, rentalRepo, carRepo, clientRepo):
        self.__validator = validator
        self.__repository = rentalRepo
        self.__carRepo = carRepo
        self._cliRepo = clientRepo

    def createRental(self, rentalId, client, car, start, end):
        rental = Rental(rentalId, start, end, client, car)
        self.__validator.validate(rental)
        
        '''
        Check the car's availability for the given period 
        '''
        if self.isCarAvailable(rental.car, rental.start, rental.end) == False:
            raise CarRentalException("Car is not available during that time!")

        self.__repository.store(rental)
        return rental

    def deleteRental(self, rentalId):
        return self._repository.delete(rentalId)

    def isCarAvailable(self, car, start, end):
        """
        Check the availability of the given car to be rented in the provided time period
        car - The availability of this car is verified
        start, end - The time span. The car is available if it is not rented in this time span
        Return True if the car is available, False otherwise
        """
        rentals = self.filterRentals(None, car)
        for rent in rentals:
            if start > rent.end or end < rent.start:
                continue
            return False
        return True

    def filterRentals(self, client, car):
        """
        Return a list of rentals performed by the provided client for the provided car
        client - The client performing the rental. None means all clients
        cars - The rented car. None means all cars 
        """
        result = []
        for rental in self.__repository.getAll():
            if client != None and rental.getClient() != client:
                continue
            if car != None and rental.car != car:
                continue
            result.append(rental)
        return result
        
    def mostOftenRentedCarMake(self):
        """
        A list of all car makes and the number of times each was rented
        """
        result = {}

        '''
        1. Build the temporary data structure
        '''
        for car in self.__carRepo.getAll():
            if car.make not in result.keys():
                result[car.make] = 0
           
            rentals = self.filterRentals(None, car)
            result[car.make] += len(rentals)

        '''
        2. Build the data transfer objects
        '''    
        dtoList = []
        for carMake in result.keys():
            dtoList.append(CarMakeRental(carMake, result[carMake]))

        '''
        3. Sort it
        '''
        dtoList.sort()
        return dtoList

    def mostOftenRentedCars(self):
        """
        Returns a list of all cars and the number of times it was rented , rented by number of rentals
        """
        result = []

        '''
        1. Build the data transfer object
        '''
        for car in self.__carRepo.getAll():
            rentals = self.filterRentals(None, car)
            result.append(CarRentalCount(car, len(rentals)))
            
        '''
        2. Sort it
        '''
        result.sort()
        return result

    def mostRentedCars(self):
        """
        Returns a list of all cars and the number of times it was rented , rented by number of rental days 
        """
        result = []

        '''
        1. Build the data transfer object
        '''
        for car in self.__carRepo.getAll():
            rentals = self.filterRentals(None, car)

            rentalCount = 0
            for rental in rentals:
                rentalCount += len(rental)
            # data transfer object
            result.append(CarRentalCount(car, rentalCount))
            
        '''
        2. Sort it
        '''
        result.sort()
        return result

class CarMakeRental():
    def __init__(self, carMake, rentalCount):
        self._carMake = carMake
        self._rentalCount = rentalCount

    @property
    def carMake(self):
        return self._carMake
    
    @property
    def rentalCount(self):
        return self._rentalCount
    
    def __lt__(self, carRental):
        """
        < operator required for sorting the list
        """
        return self.rentalCount < carRental.rentalCount
    
    def __str__(self):
        return str(self.rentalCount).ljust(10) + " for car " + str(self.carMake).ljust(40)

class CarRentalCount:
    def __init__(self, car, rentalCount):
        """
        Constructor for this data transfer object
        car - The car for this object
        rentalCount - The number of times/days the car was rented for  
        """
        self._car = car
        self.__rentals = rentalCount

    @property
    def car(self):
        return self._car
    
    def __lt__(self, carRental):
        """
        < operator required for sorting the list
        """
        return self.getRentalCount() < carRental.getRentalCount()
    
    def __str__(self):
        return str(self.getRentalCount()).ljust(10) + " for car " + str(self.car).ljust(40)
    
    def getRentalCount(self):
        return self.__rentals 
