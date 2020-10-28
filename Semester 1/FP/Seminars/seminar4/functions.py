'''
place functions which solve problem requirments
'''
from p1 import *
'''
ways to implement undo:
    1. keep a list of operation and their parameters and revers them (efficient but complicated)
    2. keep the history of program data in a list
'''


def undo(circles,history):
    # update the circles with the last elem of the history
    if len(history) == 0:
        raise ValueError("No more undos!")
    # same variable
    circles.clear()
    circles.extend(history.pop())



def add_circle(circles,history,x,y,r):
    c = create_circle(x,y,r)
    history.append(circles[:])
    circles.append(c)



