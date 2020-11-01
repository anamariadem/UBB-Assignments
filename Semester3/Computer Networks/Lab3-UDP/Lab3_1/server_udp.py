import socket, sys

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

UDP_Id = sys.argv[1]
UDP_Port = int(sys.argv[2])

server_socket.bind((UDP_Id, UDP_Port))

while True:
    print("Waiting for data")
    data, address = server_socket.recvfrom(1024)
    data_ascii = data.decode("ascii")

    print("Received: " + data_ascii)

    server_socket.sendto(bytes(data_ascii, "ascii"), address)
    