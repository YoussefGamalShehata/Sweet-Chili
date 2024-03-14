import RPi.GPIO as GPIO
import time
import socket

server_ip = "192.168.1.32"  # Replace with the actual IP address of Pi A
server_port = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((server_ip, server_port))

# Set GPIO mode
GPIO.setmode(GPIO.BCM)

# Define GPIO pins
TRIG_PIN = 5
ECHO_PIN = 6

# Setup GPIO pins
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)

 ## @brief This function Measures the distacne using Ultrasonic sensor.
 # @param void.
 # @retval Distance value.
def measure_distance():
    # Trigger pulse
    GPIO.output(TRIG_PIN, GPIO.HIGH)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, GPIO.LOW)

    # Wait for echo to start
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    # Wait for echo to end
    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    # Calculate distance
    pulse_duration = pulse_end - pulse_start
    distance = pulse_duration * 34300 / 2  # Speed of sound = 343 meters/second

    return distance

try:
    while True:
        message = measure_distance()
        int_message = int(message)  # Convert the distance to an integer
        client_socket.sendall(str(int_message).encode('utf-8'))
        print(f"Distance: {int(message)} cm")
        time.sleep(1)

except KeyboardInterrupt:
    print("Measurement stopped by user")

finally:
    # Cleanup GPIO
    GPIO.cleanup()