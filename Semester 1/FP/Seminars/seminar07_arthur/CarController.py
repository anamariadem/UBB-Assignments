from Car import Car
class CarController:
    def __init__(self, validator, repository):
        self.__validator = validator
        self.__repository = repository
        
    def create(self, carId, licensePlate, carMake, carModel):
        car = Car(carId, licensePlate, carMake, carModel)
        self.__validator.validate(car)
        self.__repository.store(car)
        return car

    def delete(self, clientId):
        return self.__repository.delete(clientId)
        
    def findByID(self, clientId):
        return self.__repository.find(clientId)
        
    def filter(self, make, model):
        return self.__repository.filter(make, model)
        
    def update(self, client):
        self.__repository.update(client)
        
    def getCarCount(self):
        return len(self.__repository)
        
    
        
            
        
