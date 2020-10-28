class Rental:
    def __init__(self, rentalId, start, end, client, car):
        self._rentalId = rentalId
        self._client = client
        self._car = car
        self._start = start
        self._end = end

    @property
    def id(self):
        return self._rentalId

    @property
    def client(self):
        return self._client
    
    @client.setter
    def client(self, client):
        self._client = client

    @property
    def car(self):
        return self._car
    
    @car.setter
    def car(self, car):
        self._car = car
    
    @property
    def start(self):
        return self._start
    
    @start.setter
    def start(self, start):
        self._start = start

    @property
    def end(self):
        return self._end
    
    @end.setter
    def end(self, end):
        self._end = end

    def __len__(self):
        return (self._end - self._start).days + 1

    def __repr__(self):
        return str(self)

    def __str__(self):
        return "Rental: " + str(self._objectId) + "\nCar: " + str(self._car) + "\nClient: " + str(self._client) + "\nPeriod: " + self._start.strftime("%Y-%m-%d") + " to " + self._end.strftime("%Y-%m-%d")