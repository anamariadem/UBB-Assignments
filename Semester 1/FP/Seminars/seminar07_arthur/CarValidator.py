from Car import Car
from ValidatorException import ValidatorException

class CarValidator:
    
    def __init__(self):
        # and so on...
        self.__counties = ["AB", "B", "CJ"]
        self._errors = ""

    def _licensePlateValid(self, plate):
        token = str(plate).split(' ')
        if len(token) != 3:
            return False
        if token[0] not in self.__counties:
            return False
        try:
            n = int(token[1])
            if len(token[1]) < 2 or len(token[1]) > 3:
                return False
            if n < 1 or n > 999:
                return False
            if n > 99 and token[0] != "B":
                return False
        except TypeError:
            return False
        if len(token[2]) != 3:
            return False
        tu = str(token[2]).upper()
        if tu[0] in ['I', 'O']:
            return False
        for x in tu:
            if x < 'A' or x > 'Z':
                return False
            if x == 'Q':
                return False
        return True

    def validate(self, car):
        """
        Validate if provided Car instance is valid
        car - Instance of Car type
        Return List of validation errors. An empty list if instance is valid.
        """
        if isinstance(car, Car) == False:
            raise TypeError("Can only validate Car objects!")
        _errors = []
        if len(car.make) == 0:
            _errors.append("Car must have a make")
        if len(car.model) == 0:
            _errors.append("Car must have a model;")
        if self._licensePlateValid(car.license) == False:
            _errors.append("Bad license plate number;")
        if len(_errors) > 0:
            raise ValidatorException(_errors)
        return True