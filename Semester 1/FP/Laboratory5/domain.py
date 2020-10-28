
class ComplexNumber:
    def __init__(self,realpart,imagpart):
        self.RealPart = realpart
        self.ImagPart = imagpart

    @property
    def RealPart(self):
        return self._r
    @RealPart.setter
    def RealPart(self,value):
        try:
            self._r = int(value)
        except ValueError:
            raise ValueError("Invalid input")

    @property
    def ImagPart(self):
        return self._i
    @ImagPart.setter
    def ImagPart(self,value):
        try:
            self._i = int(value)
        except ValueError:
            raise ValueError("Invalid input")
    def __str__(self):
        if self.RealPart == 0:
            return str(self.ImagPart) + 'i'
        if self.ImagPart == 0:
            return str(self.RealPart)
        if self.ImagPart == -1:
            return str(self.RealPart) + '-i'
        if self.ImagPart < 0:
            return str(self.RealPart) + str(self.ImagPart) + 'i'
        if self.ImagPart == 1:
            return str(self.RealPart) + 'i'
        return str(self.RealPart) + '+' + str(self.ImagPart) + 'i'


def test_ComplexNumber():
    c = ComplexNumber(4,5)
    assert c.RealPart == 4 and c.ImagPart == 5
    try:
        c = ComplexNumber('e',7)
        assert False
    except ValueError:
        assert True


