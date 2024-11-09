import re
import socket
import threading
import time
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
broadcastAddress = '255.255.255.255'
port = 7777
timeQueryString = b"TIMEQUERY\0"
dateQueryString = b"DATEQUERY\0"
s.bind(('0.0.0.0', port))
peersList = dict()
malformedList = []


def sendDateQuery():
    global s, port, timeQueryString, dateQueryString, broadcastAddress
    msg = dateQueryString
    while True:
        b = s.sendto(msg, (broadcastAddress, port))
        if b != len(msg):
            print("no date query was sent")
        print("message sent")
        time.sleep(3)


def sendTimeQuery():
    global s, port, timeQueryString, dateQueryString, broadcastAddress
    msg = timeQueryString
    while True:
        b = s.sendto(msg, (broadcastAddress, port))
        if b != len(msg):
            print("no time query was sent")
        print("message sent")
        time.sleep(10)


def regexMatch(msg, pattern):
    pattern = re.compile(pattern)
    return pattern.fullmatch(msg)


def respondQuery():
    global s, port, timeQueryString, dateQueryString, peersList
    while True:
        msg, addr = s.recvfrom(1024)
        print(f"message received: {msg.decode()}")
        if msg == timeQueryString:
            myTime = time.strftime("TIME %H:%M:%S")
            print(f"responding with {myTime} to ip: {addr[0]}, port {addr[1]}")
            myTime = myTime.encode()
            b = s.sendto(myTime, addr)
            if b != len(myTime):
                print("my time not sent")
        elif msg == dateQueryString:
            myDate = time.strftime("DATE %d:%m:%Y")
            print(f"responding with {myDate} to ip: {addr[0]}, port {addr[1]}")
            myDate = myDate.encode()
            b = s.sendto(myDate, addr)
            if b != len(myDate):
                print("my date not sent")
        else:
            msg = msg.decode()
            if regexMatch(msg=msg, pattern="TIME [0-9]{2}:[0-9]{2}:[0-9]{2}") is None:
                malformedList.append((addr,))
            # TODO for date regex

            # TODO peers dict and removing part
            # if addr[0] not in peersList.keys():
            #   peersList[addr[0]] = (msg.decode(), 3)


if __name__ == '__main__':
    print("Running...")
    args = sys.argv
    if len(args) <= 1:
        print("specify the broadcast address")
        exit(-1)
    broadcastAddress = args[1]
    threads = []
    t1 = threading.Thread(target=sendTimeQuery)
    t2 = threading.Thread(target=sendDateQuery)
    threads.append(t1)
    threads.append(t2)
    t1.start()
    t2.start()
    respondQuery()
    for t in threads:
        t.join()
