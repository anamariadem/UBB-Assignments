import socket
import sys
import threading
import time
import random
import struct

#leader starts here
def send_leader_message(leader_students, port):
    print("Start sending leader message!")
    while True:
        message = "leader"
        leader_students.sendto(message.encode("ascii"), ("<broadcast>", port))
        time.sleep(5)

def handle_questions(leader_students, leader_teacher, port):
    while True:
        message, address = leader_students.recvfrom(1024)
        message = message.decode("ascii")
        print("Received question: ", message, " from  student", address)
        print("Forwarding to teacher...")
        leader_teacher.send(message.encode("ascii"))

        answer = leader_teacher.recv(1024).decode("ascii")
        length = struct.unpack("!i", leader_teacher.recv(4))[0]

        for i in range(length):
            number = struct.unpack("!i", leader_teacher.recv(4))[0]
            answer = answer + " " + str(number)

        print("Received from teacher: ", answer)
        print("Broadcasting to students...")

        broadcast_message = "Answer from teacher to question \"" + message + "\" : " + answer
        leader_students.sendto(broadcast_message.encode("ascii"), ("<broadcast>", port))

# socket.sendto(message.encode(), (IP, port))

def handle_group_leader(port):
    leader_students = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    leader_students.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    leader_students.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

    leader_teacher = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    leader_teacher.connect(("", 1234))

    send_leader_thread = threading.Thread(target=send_leader_message, args=(leader_students,port))
    send_leader_thread.start()

    handle_questions_thread = threading.Thread(target=handle_questions, args=(leader_students, leader_teacher, port))
    handle_questions_thread.start()


# student starts here
def send_question(student_leader, address):
    while True:
        if random.randint(0,1) == 1:
            question = "question"
            student_leader.sendto(question.encode("ascii"), address)
        time.sleep(3)

def get_answers(student_leader):
    while True:
        message, address = student_leader.recvfrom(1024)
        message = message.decode("ascii")
        if message != "leader":
            print("Receiver: ", message, " from ", address)

def handle_student(port):
    student_leader = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    student_leader.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    student_leader.bind(("0.0.0.0", port)) # bind on port "port" , any ip address

    message = str()
    leader_address = tuple()

    while message != "leader":
        message, leader_address = student_leader.recvfrom(1024)
        message = message.decode("ascii")
        print("Received message: ", message, " from ", leader_address)

    send_questions_thread = threading.Thread(target=send_question, args=(student_leader, leader_address))
    send_questions_thread.start()

    get_answers_thread = threading.Thread(target=get_answers, args=(student_leader,))
    get_answers_thread.start()


if __name__ == "__main__":
    port = int(sys.argv[1])
    is_leader = int(sys.argv[2])

    if is_leader == 1:
        handle_group_leader(port)
    else:
        handle_student(port)