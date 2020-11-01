import socket, struct

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 1234))

length = int(input("Give array length: "))
client_socket.send(struct.pack("!i", length))

for i in range(length):
    element = float(input("Give element " + str(i) + " :"))
    client_socket.send(struct.pack("!f", element))

new_length = struct.unpack("!i", client_socket.recv(4))[0]
received_array = []
for i in range(new_length):
    element = struct.unpack("!f", client_socket.recv(4))[0]
    received_array.append(element)

print("I received: ", received_array)
client_socket.close()
