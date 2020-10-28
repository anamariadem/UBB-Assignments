
from p1 import *
from functions import *

'''
ui -> functions
ui - > domain
functions -> domain
'''


'''
Menu-driven circles program?!
    - add a circle (radius > 0, in the (+,+) first quadrant)
    - delete circles with radius < r
    - show circles
    - undo
    - exit
'''
'''
everything that reads/writes to the user (console)
the only module where you input/print/call functions that do that

function calls:
    ui -> functions
    ui -> domain
    functions -> domain
'''

# UI

def add_circle_ui(circles,history):
    x  = int(input("x= "))
    y = int(input("y= "))
    r = int(input("r= "))
    # surround with try except
    add_circle(circles,history,x,y,r)



def show_circles_ui(circles,history):
    for c in circles:
        print(tostr(c))


def print_menu():
    print("1. Add circle")
    print("3. Show circles")
    print("4. Undo")
    print("0. Exit")

def start():
    #circles = []
    circles = test_init()
    history = []
    # -command design pattern
    commands = {'1':add_circle_ui, '3':show_circles_ui, '4':undo}
    while True:
        print_menu()
        cmd = input("command: ")
        if cmd == "0":
            return
        if cmd in commands.keys():
            try:
                commands[cmd](circles,history)
            except ValueError as ve:
                # GUI
                # MessageBox , show(...,ve)
                print(ve)
        else:
            print("Bad command")


start()