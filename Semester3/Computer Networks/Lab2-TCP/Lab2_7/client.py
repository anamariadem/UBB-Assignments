import socket
import crypt
import getpass
from hmac import compare_digest as compare_hash

IP = "127.0.0.1"
port = 1234

if __name__ == "__main__":
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    client_socket.connect((IP, port))

    user_name = input("Give username: ")

    client_socket.send(bytes(user_name, "ascii"))

    message = client_socket.recv(1024).decode("ascii")

    if message.split()[0] == "No":
        print(message)
    else:
        crypted_passwd = message
        cleartext = getpass.getpass()
        result = compare_hash(crypt.crypt(cleartext, crypted_passwd), crypted_passwd)
        if result:
            print("Correct password")
        else:
            print("Incorrect password")