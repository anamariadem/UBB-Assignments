from multiprocessing import Process
import socket
import struct
from pathlib import Path
import os
'''
2.   The client sends the complete path to a file. The server returns back the length of the file and its content in the 
case the file exists. When the file does not exist the server returns a length of -1 and no content. The client will 
store the content in a file with the same name as the input file with the suffix –copy appended 
(ex: for f.txt => f.txt-copy).
'''

def handle_task(client_socket):
    '''length = client_socket.recv(2).decode()
    length = struct.unpack('!H', length)
    print(length)'''

    file_path = client_socket.recv(1024).decode("ascii")

    try:
        file_stats = os.stat(file_path)
        file_size = file_stats.st_size
        #print(file_size)

        with open(file_path) as file:
            content = file.readlines()

        content_as_string = str()

        for line in content:
            content_as_string += line

        client_socket.send(struct.pack("!h", file_size))
        client_socket.send(bytes(content_as_string, 'ascii'))

    except FileNotFoundError:
        file_size = -1
        client_socket.send(struct.pack("!h", file_size))


    client_socket.close()


if __name__ == '__main__':
    global client_socket
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

        process = Process(target=handle_task, args=(client_socket,))
        process.start()
        process.join()
