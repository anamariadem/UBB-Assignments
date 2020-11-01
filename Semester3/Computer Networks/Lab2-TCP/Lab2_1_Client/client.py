import socket

import struct

socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

command = input("Give shell comnand: ")
#print(command)

socket_descriptor.connect(("127.0.0.1", 4321))

socket_descriptor.send(struct.pack('100s', command.encode()))

result = socket_descriptor.recv(1024).decode()

print(result)

socket_descriptor.close()