class Car:
    def __init__(self, carId, licenseNumber, make, model, color):
        self._id = carId
        self.License = licenseNumber
        self._make = make
        self._model = model

    @property
    def Id(self):
        return self._id

    @property
    def License(self):
        return self._license

    @License.setter
    def License(self, value):
        self._license = value

    @property
    def Make(self):
        return self._make

    @property
    def Model(self):
        return self._model

    def __eq__(self, z):
        if isinstance(z, Car) == False:
            return False
        return self.Id == z.Id

    def __str__(self):
        return "Id: " + str(self.Id) + ", License: " + self.License + ", Car type: " + self.Make + ", " + self.Model

    def __repr__(self):
        return str(self)

