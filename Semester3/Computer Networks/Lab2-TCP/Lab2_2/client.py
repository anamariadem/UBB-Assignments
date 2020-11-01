import socket

import struct

if __name__ == '__main__':
    socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    command = input("Give file path: ")
    # print(command)

    socket_descriptor.connect(("127.0.0.1", 4321))

    #/Users/anamaria/Desktop/ComputerNetworks/Lab2_1_Server/cv.txt

    socket_descriptor.send(bytes(command, 'ascii'))

    file_size = socket_descriptor.recv(2)

    file_size = struct.unpack("!h", file_size)

    if file_size[0] == -1:
        print("File does not exist")
    else:
        result = socket_descriptor.recv(1024).decode("ascii")

        print("File has size " + str(file_size[0]))

        new_file_name = str(command) + "-copy"

        with open(new_file_name, "w") as new_file_name:
            new_file_name.write(result)

    socket_descriptor.close()