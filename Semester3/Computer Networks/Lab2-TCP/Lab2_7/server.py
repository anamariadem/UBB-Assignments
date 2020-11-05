'''
7.   The client reads a username and a password from the standard input. It sends the username to the server. The server
 uses the getpwent system call repeatedly to find the password information about the username. If the entry for the
 username is found, the password field from the struct passwd is returned to the client. The client recovers the salt
 of the password and checks the input password with the received encrypted version using the crypt system call.
 If there is no user username, the server returns back to the client the empty string and closes the connection.
'''

import socket
import pwd
from multiprocessing import Process
IP = "127.0.0.1"
port = 1234

def handle_task(client_socket):
    user_name = client_socket.recv(1024).decode("ascii")

    try:
        crypted_password = pwd.getpwnam(user_name)[1]
        if crypted_password == 'x' or crypted_password == '*':
            messsage = 'No support for shadow passwords'
            client_socket.send(bytes(messsage, "ascii"))
        else:
            client_socket.send(bytes(crypted_password, "ascii"))

    except KeyError:
        message = "No such username entry"
        client_socket.send(bytes(message, "ascii"))

    client_socket.close()

if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_socket.bind((IP, port))
    server_socket.listen(10)

    while True:
        print("Waiting for connections")
        client_socket, address = server_socket.accept()
        print("Client with address ", address, " connected")

        process = Process(target=handle_task, args=(client_socket,))
        process.start()
        process.join()