from Client import Client
class ClientController:
    def __init__(self, validator, repository):
        self.__validator = validator
        self.__repository = repository

    def create(self, clientId, clientCNP, clientName):
        client = Client(clientId, clientCNP, clientName)
        self.__validator.validate(client)
        self.__repository.store(client)
        return client

    def delete(self, clientId):
        return self.__repository.delete(clientId)
        
    def update(self, client):
        self.__repository.update(client)
       
    def getClientCount(self):
        return len(self.__repository)
        
    
        
            
        
