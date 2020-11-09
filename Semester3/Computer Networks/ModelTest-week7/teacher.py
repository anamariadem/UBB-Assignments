import socket
import select
import random
import struct

'''
server --------------------
 |    
t_l ---------> client_socket
 |
 |
 |
client
'''

if __name__=="__main__":
    teacher_leader = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    teacher_leader.bind(("", 1234))

    teacher_leader.listen(10)

    master = [teacher_leader]

    print("Waiting for questions from leaders...")

    while True:
        ready_to_read, _, _ = select.select(master, [], [])

        for file_descriptor in ready_to_read:
            if file_descriptor == teacher_leader:
                leader_socket, address = teacher_leader.accept()
                print("Leader ", address, "connected")
                master.append(leader_socket)
            else:
                question = file_descriptor.recv(1024).decode()
                print("Received question: ", question)
                print("Sending answer to leader...")
                answer = "answer"
                file_descriptor.send(answer.encode("ascii"))
                length = random.randint(1,10)
                file_descriptor.send(struct.pack("!i", length))
                for i in range(length):
                    number = random.randint(1,1000)
                    file_descriptor.send(struct.pack("!i", number))