'''
we keep a class called Number
an object of type Number has a base and a value
'''
class Number:
    def __init__(self, base, value):
        self._base = base
        self._value = value

    @property
    def Base(self):
        return self._base

    @property
    def Value(self):
        return self._value
    @Value.setter
    def Value(self, value):
        if self._base != 16:
            i = 0
            while i < len(value) :
                if int(value[i]) >= int(self.Base):
                    raise  ValueError("Invalid number in base" + str(self.Base))
                i +=1
        else:
            i = 0
            while i < len(value):
                if value[i] >= "F":
                    raise ValueError("Invalid number in base 16")


    def __str__(self):
        return "base: " + str(self.Base) + "value: "+ str(self.Value)
