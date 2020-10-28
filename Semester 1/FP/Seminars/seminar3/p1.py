
#add <student id>, <name>, <grade>
#e.g. add 123, Popescu Elena<9
##e.g. add 123, Popescu Elena<9 -> program screm error
# delete 123
#delete 21 -> erroe
'''
add <student id>, <name>, <grade>
delete student id
list
exit
'''
def  create_student(sid, name, grade): #non ui
    '''
    create a student
    :param sid: id
    :param sname: string of len>=3
    :param sgrade: int between 1 and 10
    :return: succes- the student
            erroe -> return None
    '''
    if len(name) < 3:
        return None
    grade = int(grade)
    if grade < 1 or grade > 10:
        return None
    return [sid,name,grade]

def find_student(studentList,sid): #non ui
    '''
    Find student with given id
    :param studentList:
    :param sid:
    :return: none, student with given id not in the list
    student havin given id
    '''
    for s in studentList:
        if get_id(s) == sid:
            return s
    return None

def get_id(student):
    return student[0]
def get_name(student):
    return student[1]
def get_grade(student):
    return student[2]

def add_student(studentList, student): #non ui
    '''
    adds a student to list
    :param studentList: the list of students
    :param student: the student
    :return: 0-success
            1- Duplicate student
    '''
    if find_student(studentList, get_id(student)) != None:
        return 1
    studentList.append(student)
    return 0


def readCommand():  #ui
    '''
    Read and parse the user s command
    :return:
    '''
    #add 123, Elena, 9
    cmd = input("command: ")
    #cmd = 'exit'
    # 1. SEparate the command word from list of parameters
    # 2. Identify parameters
    # 3. Return tuple(command, list of param)
    idx = cmd.find(" ")
    if idx == -1:
        return (cmd, [])
    command = cmd[:idx]
    params = cmd[idx:]
    params = params.split(",")
    for i in range(len(params)):
        params[i] = params[i].strip()
    return (command,params)

def add_student_ui(studentList, params):
    if len(params) != 3:
        print("Bad student params")
        return
    s = create_student(params[0], params[1], params[2])
    if s == None:
        print("Invalid student data")
        return
    if add_student(studentList,s) == 1:
        print("Duplicate id")

def remove_student(studentList,student):
    if find_student(studentList,get_id(student)) != None:
        return 1
    studentList.remove(student)
    return 0

def remove_student_ui(studentList, params):
    if len(params) != 3:
        print("Bad student params")
        return
    if remove_student(studentList,s) == 0:
        print("Student is not in list")
        return
    remove_student()






def start():  #ui
    studentList = []
    while True:
        print(studentList)
        cmdtuple = readCommand()
        cmd = cmdtuple[0]
        params = cmdtuple[1]
        if cmd == "add":
            add_student_ui(studentList,params)
        elif cmd == "remove":
            remove_student(studentList,params)
        elif cmd == 'exit':
            break
        else:
            print("Bad command")

start()


# what do test functions do?
    #   1. Take no parameters
    #   2. Have no user input/output
    #   3. If the code is correct, do nothing visible
    #   4. If the code has an erroe -> scream


def test_add_student():
    slist = []
    s1 = create_student(1, "Marie", 10)
    assert add_student(slist, s1) == 0
    assert len(slist) == 1
    assert get_id(slist[0]) == 1

    assert add_student(slist, s1) == 1
    assert len(slist) == 1
