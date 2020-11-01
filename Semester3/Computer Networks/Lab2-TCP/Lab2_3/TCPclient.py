import threading
import struct
import random
import socket
import time

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 7777))
    client_number = random.uniform(0, 100)
    print('Client number: ', client_number)
    sock.sendall(struct.pack("!f", client_number))
    answer = sock.recv(1, 0)
    print(answer)

main()