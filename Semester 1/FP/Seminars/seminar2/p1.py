

def create_student(sid = -1, sname = "n/a", sgrade = None):
    return {"id":sid, "name":sname, "grade":sgrade}

def get_student_id(student):
    return student["id"]
def get_student_name(student):
    return student["name"]
def get_student_grade(student):
    return student["grade"]

def show_students(students):
    print("List of students: ")
    for s in students:
        print("id: " + str(get_student_id(s)) + "name: " + get_student_name(s) + "grade: " + str(get_student_grade(s)))

def read_student():
    sid = int(input("Student id: "))
    sname = input("Student name: ")
    sgrade = int(input("Student grade: "))
    return create_student(sid, sname, sgrade)

def validate_student(student, studentList):
    for s in studentList:
        if get_student_id(s) == get_student_id(student):
            return "Duplicate student id"
    name = get_student_name(student)
    if len(name) == 0:
        return "Empty name!"
    grade = get_student_grade(student)
    if grade < 1 or grade > 10:
        return "Invalid grade"
    return None

def add_student(studentList):
    student = read_student()
    msg = validate_student(student, studentList)
    if msg is not None:
        print(msg)
    else:
        studentList.append(student)

def print_menu():
    print("1. Show students")
    print("2. Add student")
    print("3. Exit")

def init_students():
    res = []
    res.append(create_student(100, "Alice", 10))
    res.append(create_student(101, "Bob", 8))
    return res

def start():
    students = init_students()
    while True :
        print_menu()
        choice = input(">")
        if choice == "1":
            show_students(students)
        elif choice == "2":
            add_student(students)
        elif choice == "3":
            return
        else:
            print("Invalid command")

start()

