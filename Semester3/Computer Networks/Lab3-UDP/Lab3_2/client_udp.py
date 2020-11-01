import socket, struct, random, sys, time

if __name__ == '__main__':
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    finished = False
    sr = 1
    er = 2 ** 17 - 1
    random.seed()

    step_count = 0
    while not finished:
        my_num = random.randint(sr, er)
        try:
            client_socket.sendto(struct.pack('!I', my_num), ("127.0.0.1", 1234))
            answer, address = client_socket.recvfrom(1)
        except socket.error as msg:
            print('Error: ', msg.strerror)
            client_socket.close()
            exit(-2)
        step_count += 1
        print('Sent ', my_num, ' Answer ', answer.decode('ascii'))
        if answer == b'H':
            sr = my_num
        if answer == b'S':
            er = my_num
        if answer == b'G' or answer == b'L':
            finished = True
        time.sleep(0.25)

    client_socket.close()
    if answer == b'G':
        print("I am the winner with", my_num, "in", step_count, "steps")
    else:
        print("I lost !!!")
#    input("Press Enter")
