class Car:
    def __init__(self, carId, licenseNumber, make, model):
        self._carId = carId
        self.license = licenseNumber
        self._make = make
        self._model = model

    @property
    def id(self):
        return self._carId

    @property
    def license(self):
        return self._license

    @license.setter
    def license(self, licenseNumber):
        self._license = licenseNumber

    @property
    def make(self):
        return self._make

    @property
    def model(self):
        return self._model

    def __eq__(self, z):
        if isinstance(z, Car) == False:
            return False
        return self.id == z.id

    def __str__(self):
        return "Id: " + str(self.id) + ", License: " + self.license + ", Car type: " + self.make + ", " + self.model

    def __repr__(self):
        return str(self)
    
