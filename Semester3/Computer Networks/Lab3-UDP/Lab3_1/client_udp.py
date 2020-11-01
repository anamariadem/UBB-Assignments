import sys
import socket
'''
1.   The client sends periodical PING datagrams with a random content to a <server> and <port> specified in command 
line. The server returns back (echoes) the same packets (content). The client checks the content of the received packets 
to match what was sent and computes the round trip time and displays it to the user – for each sent packet.
'''

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

UDP_Id = sys.argv[1]
UDP_Port = int(sys.argv[2])

message = input("Give message to send: ")

client_socket.sendto(bytes(message, "ascii"), (UDP_Id, UDP_Port))

data, address = client_socket.recvfrom(1024)

data_ascii = data.decode("ascii")

print("Received back: " + data_ascii)