class ValidatorException(Exception):
    def __init__(self, messageList=["Validation error!"]):
        self._messageList = messageList
        
    @property
    def messages(self):
        return self._messageList
    
    def __str__(self):
        result = ""
        for message in self.messages:
            result += message
            result += "\n"
        return result
