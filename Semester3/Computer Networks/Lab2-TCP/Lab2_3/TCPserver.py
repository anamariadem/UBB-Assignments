import threading
import struct
import random
import socket
import time

rand_number = 0
threads = []
numbers = []
lock = threading.Lock()

def communicate(connection):
    variabila = connection.recv(4)
    numar = struct.unpack("!f", variabila)[0]
    lock.acquire()
    numbers.append((connection, numar))
    lock.release()

def main():
    rand_number = random.uniform(0, 100)
    print(rand_number)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 7777)
    sock.bind(server_address)
    sock.listen(100)
    sock.settimeout(10)
        
    while True:
        print('Waiting for connection')
        try:
            connection, client_address = sock.accept()
            print(connection)
            t1 = threading.Thread(target = communicate, args = (connection,))
            t1.start()
            threads.append(t1)
        except socket.timeout:
            break

    winner = ""
    min = 9999999999999
    for tuplu in numbers:
        if abs(rand_number - tuplu[1]) < min:
            min = abs(rand_number - tuplu[1])
            winner = tuplu[0]
    for tuplu in numbers:
        if tuplu[0] == winner:
            tuplu[0].sendall(b's')
        else:
            tuplu[0].sendall(b'w')
        tuplu[0].close()

    for tred in threads:
        tred.join()

main()