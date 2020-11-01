import socket
import struct
import os

def execute_command(client_socket):
    print("here")

    exit(0)

if __name__ == '__main__':
    try:
        socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_descriptor.bind(('127.0.0.1', 4321))
        socket_descriptor.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)

    while True:
        print("Listening for incomming connections")

        client_socket, addrc = socket_descriptor.accept()

        print("A client connected")

        pid = os.fork()
        if pid == 0:
            execute_command(client_socket)