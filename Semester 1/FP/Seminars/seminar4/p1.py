'''
specification
tests + test-driven development
exceptions
simple feature-driven development
undo ?!
modular programming
'''

# DOMAIN MODULE

'''
here u code everything about the domain
domain = circles, Q, Z, expenses, transaction, contest results
'''

# c= [0,0,1] unit circle - not valid

def create_circle(x,y,r):
    '''
    Creates a circle centered in (x,y) with radius r
    :param x: int >0
    :param y: int >0
    :param r: int >0
    :return: circle
    Raises ValueError if circle is invalid
    '''
    if r <= 0:
        raise ValueError("Radius < = 0")
    if  x < r or y < r:
        raise ValueError("Circle is not in q1")
    return [x,y,r]

def get_x(c):
    return c[0]
def get_y(c):
    return c[1]
def get_r(c):
    return c[2]


def tostr(c):
    return '(' +str(get_x(c)) + "," + str(get_y(c))  + ")" + ', r = ' + str(get_r(c))

def test_tostr():
    c =  create_circle(2,2,1)
    assert tostr(c) == '(2,2), r=1'
    c = create_circle(20,30,4)
    assert tostr(c) == '(20,30), r=4'
# 1. Write specifications
# 2. Write a test function
# 3. Run the test function - it has to fail
# 4. Write function
# 5. Run test again- ih should pass (repeat 3-5)
# 6. Optimize

def test_init():
    circles = []
    circles.append(create_circle(10,4,3))
    circles.append(create_circle(5, 2, 1))
    circles.append(create_circle(3, 7, 2))
    return circles

def test_create_circle():
    # nice circle
    c = create_circle(1,1,1)
    assert get_x(c) == 1 and get_y(c) == 1 and get_r(c) ==1

    # radius < 0
    try:
        c = create_circle(1, 1, -1)
        assert False
    except ValueError:
        assert True

    # not in first q
    try:
        c = create_circle(1, 1, 2)
        assert False
    except ValueError:
        assert True

test_create_circle()








