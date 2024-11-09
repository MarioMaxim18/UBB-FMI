import socket

def send_command(command, host='127.0.0.1', port=1234):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))

    client.send(command.encode('utf-8'))

    response = client.recv(4096).decode('utf-8')
    print(response)
    client.close()

if __name__ == "__main__":
    command = input("Enter command to execute on server: ")
    send_command(command)
