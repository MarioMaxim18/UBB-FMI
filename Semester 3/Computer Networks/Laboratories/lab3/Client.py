import socket
import struct
import random


if __name__ == '__main__':
    try:
        s = socket.create_connection(('172.30.243.217', 12345))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    finished = False
    sr = 1.0
    er = 100.0
    random.seed()

    data = s.recv(1024)
    print(data.decode('ascii'))

    try:
        my_num = random.uniform(sr, er)
        s.sendall(struct.pack('!f', my_num))
        print(f'Sent {my_num:.2f}')

        result = s.recv(1024)
        if result:
            print(result.decode('ascii'))

    except socket.error as msg:
        print('Error:', msg.strerror)
        s.close()
        exit(-2)

    s.close()