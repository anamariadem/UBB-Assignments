'''
    1. Add a new star to the catalogue (generated some stars)
    2. Show all stars, sorted by any of the parameters
        by distance from sun (0,0,0)
        mass
        app. magnitude
    3. Which starts are dangerous for earth? (weight > 10 Sm, AppMagnitude <3)

'''
from p1 import *
#where are all the starts?

'''
here we have the list of stars and the non-ui functions
'''
class Service:
    def __init__(self):
        self._stars = []

    def addStar(self,star):
        '''
        add the new star to the catalogue
        :param star:
        raise ValueError - if new star too close to existing ones
        :return:
        '''
        for s in self._stars:
            if s.Location - star.Location < 1:
                raise ValueError("Stars are too close")
        self._stars.append(star)
        print(self._stars)


    def sortStar(self,cmp):
        '''
        sort stars by given parameter
        :param cmp: refference to a comparator function
        :return: the sorted list of stars
        '''
        pass

    def dangerousStar(self,mass,mag):
        '''
        return list of dangerous stars
        :param mass,mag
        '''
        pass

s = Service()
sun = Star(Location(0,0,0),40,5)
Service.addStar(s,sun)