import threading
import socket
import sys
import random
import datetime
from os import system, name
from time import sleep
from collections import deque

def clear():
    # for windows
    if name == 'nt':
        _ = system('cls')
        # for mac and linux(here, os.name is 'posix')
    else:
        _ = system('clear')


class UdpBroadcastApp:
    def __init__(self, IP, port):
        self._ip = IP
        self._port = port
        self._list_of_peers = []
        self._malformed_messages = deque()

        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
        self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

        self._socket.bind((IP, port))

    def send(self, message):
        self._socket.sendto(bytes(message, "ascii"), ("<broadcast>", self._port))

    def send_time_query(self):
        message = "TIMEQUERY"
        self.send(message)

    def send_date_query(self):
        message = "DATEQUERY"
        self.send(message)

    def answer_time_query(self, ip, port):
        now = datetime.datetime.now()
        current_time = now.strftime("%H:%M:%S")
        message_to_send = "TIME " + current_time
        self._socket.sendto(bytes(message_to_send, "ascii"), (ip, self._port))

    def answer_date_query(self, ip, port):
        now = datetime.datetime.today()
        current_date = now.strftime("%Y-%m-%d")
        message_to_send = "DATE " + str(current_date)
        self._socket.sendto(bytes(message_to_send, "ascii"), (ip, self._port))

    def collect_malformed_data(self, address, data):
        self._malformed_messages.append((address, data))

    def is_malformed_data(self, data):
        split_data = data.split()

        if split_data[0] not in ["DATE", "TIME"]:
            return True

        if split_data[0] == "DATE":
            try:
                datetime.datetime.strptime(split_data[1], "%Y-%m-%d")
            except Exception:
                return True
        elif split_data[0] == "TIME":
            try:
                datetime.datetime.strptime(split_data[1], "%H:%M:%S")
            except Exception:
                return True
        return False

    def display_list_of_peers(self):
        for peer in self._list_of_peers:
            ip = peer[0][0]
            port = peer[0][1]
            print(ip, " : ", port, "\t-\t", peer[1])

    def display_malformed_data(self):
        if len(self._malformed_messages) == 0:
            print("No malformed data so far")
            return
        print("Malformed data: ")
        for message in self._malformed_messages:
            ip = message[0][0]
            port = message[0][1]
            print(ip, " : ", port, "\t-\t", message[1])

    def answer(self):
        while True:
            message, address = self._socket.recvfrom(1024)
            message = message.decode()
            if message == "TIMEQUERY":
                self.answer_time_query(address[0], self._port)
            elif message == "DATEQUERY":
                self.answer_date_query(address[0], self._port)
            elif self.is_malformed_data(message):
               self.collect_malformed_data(address, message)
            else:
                self._list_of_peers.append((address, message))
                clear()
                self.display_list_of_peers()
                self.display_malformed_data()

    def send_time_queries(self):
        while True:
            sleep(5)
            self.send_time_query()

    def send_date_queries(self):
        while True:
            sleep(15)
            self.send_date_query()

    def send_malformed_data(self):
        while True:
            sleep(12)
            messages = ["This is some message", "Not date or time", "Malformed message", "Go study", "Stop being lazy"]
            self._socket.sendto(random.choice(messages).encode(), ('<broadcast>', self._port))

if __name__ == "__main__":
    port = 7777
    app = UdpBroadcastApp("", port)

    time_query_thread = threading.Thread(target=app.send_time_queries)
    date_query_thread = threading.Thread(target=app.send_date_queries)
    malformed_data_thread = threading.Thread(target=app.send_malformed_data)
    answer_thread = threading.Thread(target=app.answer)

    time_query_thread.start()
    date_query_thread.start()
    malformed_data_thread.start()
    answer_thread.start()

    #while True:
     #   app.answer()