import socket
import threading
import random
import struct
import sys
import time

random.seed()
start = 1
stop = 2 ** 17 - 1
my_num = random.randint(start, stop)
print('Server number: ', my_num)

if __name__ == '__main__':
    try:
        rs = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        rs.bind(('127.0.0.1', 1234))
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)

    players = list()

    while True:
        client_number, address = rs.recvfrom(4)
        players.append(address)
        cnumber = struct.unpack('!I', client_number)[0]
        if cnumber > my_num:
            rs.sendto(b'S', address)
        if cnumber < my_num:
            rs.sendto(b'H', address)
        if cnumber == my_num:
            winner = address
            break

    for addr in players:
        if addr == winner:
            rs.sendto(b'G', addr)
        else:
            rs.sendto(b'L', addr)


