import socket
import RPi.GPIO as GPIO

# Set the GPIO mode to BCM
GPIO.setmode(GPIO.BCM)

easy = 14
warning = 15
brake = 18

GPIO.setup(easy, GPIO.OUT)  # Set GPIO pins as output
GPIO.setup(warning, GPIO.OUT)
GPIO.setup(brake, GPIO.OUT)

server_ip = "0.0.0.0"  # Listen on all available interfaces
server_port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_ip, server_port))
server_socket.listen(1)  # Listen for one incoming connection

print("Server is listening for connections...")

while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connection established with {client_address}")

    try:
        while True:
            data = client_socket.recv(1024)
            decoded_data = int(data)
            if not data:
                break  # Break the loop if no more data is received
            if decoded_data < 20:
                GPIO.output(brake, GPIO.HIGH)
                GPIO.output(easy, GPIO.LOW)
                GPIO.output(warning, GPIO.LOW)
            elif decoded_data < 40:
                GPIO.output(brake, GPIO.LOW)
                GPIO.output(easy, GPIO.LOW)
                GPIO.output(warning, GPIO.HIGH)
            elif decoded_data > 40:
                GPIO.output(brake, GPIO.LOW)
                GPIO.output(easy, GPIO.HIGH)
                GPIO.output(warning, GPIO.LOW)
            print(f"Received data: {data.decode('utf-8')}")

    except ConnectionResetError:
        print("Connection with the client reset.")
    except Exception as e:
        print(f"Error: {e}")

    finally:
        client_socket.close()
        print("Connection closed.")