from math import sqrt
'''
starry nights
stars have a location (x,y,z) distance at least 1ly between 2 stars,
weight (in solar masses, between [0,1,50]) and apparent magnitude (between [-1,15])
    1. Add a new star to the catalogue (generated some stars)
    2. Show all stars, sorted by any of the parameters
    3. Which starts are dangerous for earth? (weight > 10 Sm, AppMagnitude <3
'''

'''
classes 
    - how do they work in python?
    - which classes to write and how to turn them into a program?
test(classes), validation
'''

class Location:
    '''
    x,y,z - integers
    '''

    def __init__(self, x, y, z):
        self._x = x
        self._y = y
        self._z = z

    # properties without setters are called read-only
    @property
    def X(self):
        return self._x

    @property
    def Y(self):
        return self._y

    @property
    def Z(self):
        return self._z

    @X.setter
    def X(self, value):
        self._x = value

    @Y.setter
    def Y(self, value):
        self._y = value

    @Z.setter
    def Z(self, value):
        self._z = value

    def __sub__(self, loc):
        return sqrt((self.X - loc.X)**2 + (self.Y - loc.Y)**2 + (self.Z - loc.Z)**2)

    def __str__(self):
        return '(' + str(self.X) + ',' + str(self.Y) + ',' + str(self.Z) + ')'


def test_location():
    alderaam = Location(1, 2, 3)  # function call operator
    assert alderaam.X == 1 and alderaam.Y == 2 and alderaam.Z == 3
    alderaam.X = 10
    assert alderaam.X == 10
    alderaam.Y += 5
    assert alderaam.Y == 7
    assert str(alderaam) == '(10,7,3)'

    '''
    # death star in coming - help plz
    alderaam.get_x()
    
    #allows me to validate star s posotion  
    alderaamset_x()
    alderaam.set_x(alderaam.get_x() + 50) #you run the code so you can validate; ok but ugly
    # python properties to the resq!
    alderaam.X += 50 #code runs, so you can validate it
    '''



class Star:
    '''
    location, mass, magnitude
    '''
    def __init__(self,loc,mass,mag):
        self._loc = loc
        self._mass = mass
        self._mag = mag

    @property
    def Location(self):
        return self._loc
    @Location.setter
    def Location(self,value):
        self._loc = value

    @property
    def Mass(self):
        return self._mass
    @Mass.setter
    def Mass(self,value):
        if int(value) <0.1 or int(value) > 50:
            raise ValueError("Star's mass must be between 0.1 and 50")
        self._mass=value

    @property
    def Magnitude(self):
        return self._mag
    @Magnitude.setter
    def Magnitude(self,value):
        if int(value) < -1 or int(value) > 15:
            raise ValueError("Star magnitude is not un [1-;15]")
        self._mag = value
        
