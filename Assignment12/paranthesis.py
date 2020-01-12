from copy import deepcopy
def printing(list, n):
    for i in range(n):
        if list[i] == 0:
            print("(", end="")
        elif list[i] == 1:
            print(")",end="")
    print()

def valid(list, index, n):
    open = 0
    close = 0
    for i in range(index + 1):
        if list[i] == 0:
            open +=1
        elif list[i] == 1:
            close +=1

    if close > open or open > n/2:
        return False
    return True

def backtrackingRec(list, index, n):
    list = deepcopy(list)

    for i in range(0,2):
        list[index] = i
        if valid(list, index, n) == True:
            if index == n-1:
                printing(list, n)
                index = 0
                list = [9] * 2* n
            elif index + 1 < n:
                backtrackingRec(list, index+1, n)
                #index += 1

def backtrackingIter(list, index, n):
    list[index] = -1

    while index > -1:
        candidate = False
        while not candidate and list[index] < 1:
            list[index] += 1
            candidate = valid(list, index, n)

        if candidate == False:
            index -=1
        else:
            if index == n-1:
                printing(list, n)
            else:
                index += 1
                list[index] = -1

def start():
    n = int(input("Give number: "))
    list = [9] * 2* n
    choice = input("Choose method: recursive(rec)/ iterative(iter): ")
    if choice == "rec":
        backtrackingRec(list, 0,2*n)
    elif choice == "iter":
        backtrackingIter(list, 0, 2*n)
    else:
        print("Bad command")

start()