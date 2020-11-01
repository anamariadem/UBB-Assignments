import socket, struct
import threading

'''
4.   The clients send an integer number N and an array of N float values. The server will merge sort the numbers 
received from all clients until it gets an empty array of floats (N=0). The server returns to each client the size of 
the merge-sorted array followed by the merge-sorted arrays of all floats from all clients.
'''

threads = []
clients = []
final_array = []
event = threading.Event()
lock = threading.Lock()
event.clear()


def merge_arrays(arr1, arr2, n1, n2):
    arr3 = [None] * (n1 + n2)
    i = 0
    j = 0
    k = 0
    while i < n1 and j < n2:
        if arr1[i] < arr2[j]:
            arr3[k] = arr1[i]
            k = k + 1
            i = i + 1
        else:
            arr3[k] = arr2[j]
            k = k + 1
            j = j + 1

    while i < n1:
        arr3[k] = arr1[i]
        k = k + 1
        i = i + 1

    while j < n2:
        arr3[k] = arr2[j]
        k = k + 1
        j = j + 1

    return arr3


def handle_task(client_socket):
    global final_array, finished
    length = struct.unpack("!i", client_socket.recv(4))[0]
    received_array = []

    if length == 0:
        event.set()

    for i in range(length):
        element = struct.unpack("!f", client_socket.recv(4))[0]
        received_array.append(element)

    received_array = sorted(received_array)
    print(received_array)
    lock.acquire()
    final_array = merge_arrays(final_array, received_array, len(final_array), length)
    lock.release()

    event.wait()
    client_socket.send(struct.pack("!i", len(final_array)))
    for element in final_array :
        client_socket.send(struct.pack("!f", element))


    client_socket.close()

def join_threads():
    global threads, event, clients, final_array
    while True:
        event.wait()
        for thread in threads:
            thread.join()
        print("Threads are finished now")
        final_array = []
        event.clear()
        print("Server was reset")

if __name__ == "__main__":
    socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 1234)
    #socket_descriptor.connect(server_address)
    socket_descriptor.bind(server_address)

    socket_descriptor.listen(10)

    thread = threading.Thread(target=join_threads, daemon=True)
    thread.start()
    while True:
        print('Waiting for connection')

        client_socket, client_address = socket_descriptor.accept()
        print("Client with address ", client_address, "connected")

        client_thread = threading.Thread(target=handle_task, args=(client_socket,))
        clients.append(client_socket)
        threads.append(client_thread)
        client_thread.start()