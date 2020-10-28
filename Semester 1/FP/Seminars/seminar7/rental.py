class Rental:
    def __init__(self, rentalId, start, end, client, car):
        self._id = rentalId
        self.Client = client
        self.Car = car
        self.Start = start
        self.End = end

    @property
    def Id(self):
        return self._id

    @property
    def Client(self):
        return self._client

    @Client.setter
    def Client(self, value):
        self._client = value

    @property
    def Car(self):
        return self._car

    @Car.setter
    def Car(self, value):
        self._car = value

    @property
    def Start(self):
        return self._start

    @Start.setter
    def Start(self, value):
        self._start = value

    @property
    def End(self):
        return self._end

    @End.setter
    def End(self, value):
        self._end = value

    def __len__(self):
        # _start and _end and python date() type
        # self._end - self._start => timedelta
        return (self._end - self._start).days + 1

    def __repr__(self):
        return str(self)

    def __str__(self):
        return "Rental: " + str(self._id) + "\nCar: " + str(self._car) + "\nClient: " + str(
            self._client) + "\nPeriod: " + self._start.strftime("%Y-%m-%d") + " to " + self._end.strftime("%Y-%m-%d")