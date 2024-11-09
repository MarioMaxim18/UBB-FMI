# The client sends to the server a string and a character. The server returns to the client a list of all positions
# in the string where specified character is found.

import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Input the string and character
string = input("Enter a string: ")
char = input("Enter a character to find: ")

s.connect(("172.30.243.217", 12345))

# Send the length, string and character to the server
length = len(string)
s.send(struct.pack("!i", length))
s.send(string.encode())
s.send(char.encode())

# Receive the list of positions
data = s.recv(4)

# Unpack the data
data = struct.unpack("!i", data)
print(data)

s.close()
