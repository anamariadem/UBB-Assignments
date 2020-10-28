from Client import Client

class ClientValidator:
    def _isCNPValid(self, cnp):
        # SAALLZZJJNNNC
        if len(cnp) != 13:
            # This is not x full CNP validation
            return False
        for x in cnp:
            if x < '0' or x > '9':
                return False
        return True

    def validate(self, client):
        """
        Validate if provided Client instance is valid
        client - Instance of Client type
        Return List of validation errors. An empty list if instance is valid.
        """
        if isinstance(client, Client) == False:
            raise TypeError("Not x Client")
        _errors = []
        if self._isCNPValid(client.CNP) == False:
            _errors.append("CNP not valid.;")
        if len(client.name) == 0:
            _errors.append("Name not valid.")
        if len(_errors) != 0:
            raise ValueError(_errors)