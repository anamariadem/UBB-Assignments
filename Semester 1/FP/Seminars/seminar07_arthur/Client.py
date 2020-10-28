class Client:
    def __init__(self, clientId, cnp, name):
        self._clientId = clientId
        self._cnp = cnp
        self._name = name

    @property
    def id(self):
        return self._clientId

    @property
    def CNP(self):
        return self._cnp

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    def __eq__(self, z):
        if isinstance(z, Client) == False:
            return False
        return self._objectId == z._objectId

    def __str__(self):
        return "Id=" + str(self.id) + ", Name=" + str(self._name)
    
    def __repr__(self):
        return str(self)