import RPi.GPIO as GPIO
import time
import bluetooth

# parameters & their integer values in the mobile application
ThrottleMinValue = 11
ThrottleMaxValue = 111
SteeringMinValue = -10
SteeringMaxValue = 10
Brake_Pressed = 112
Brake_Released = 113
P = 114
R = 115
N = 116
D = 117

# Constant Variables
FORWARD = True
BACKWARD = False

# Global Variables
recent_state = P
Steer = 0
Throt = 34
Brake_var = Brake_Released

# Motor pins
MOTOR_ENA = 17  # Enable pin for Motor R
MOTOR_IN1 = 27  # Input 1 pin for Motor R
MOTOR_IN2 = 22  # Input 2 pin for Motor R
MOTOR_IN3 = 16  # Input 3 pin for Motor L
MOTOR_IN4 = 20  # Input 4 pin for Motor L
MOTOR_ENB = 21  # Enable pin for Motor L

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup([MOTOR_ENA, MOTOR_IN1, MOTOR_IN2, MOTOR_ENB, MOTOR_IN3, MOTOR_IN4], GPIO.OUT)



## @brief Function to control motor in right direction and speed.
 # @param speed.
 # @param clockwise.
 # @retval Distance value.
def control_motor_r(speed, clockwise):
    # Set motor direction
    GPIO.output(MOTOR_IN1, GPIO.HIGH if clockwise else GPIO.LOW)
    GPIO.output(MOTOR_IN2, GPIO.LOW if clockwise else GPIO.HIGH)

    # Set motor speed
    pwm_r.ChangeDutyCycle(speed)

## @brief Function to control motor in left direction and speed.
 # @param speed.
 # @param clockwise.
 # @retval Distance value.
def control_motor_l(speed, clockwise):
    # Set motor direction
    GPIO.output(MOTOR_IN3, GPIO.HIGH if clockwise else GPIO.LOW)
    GPIO.output(MOTOR_IN4, GPIO.LOW if clockwise else GPIO.HIGH)

    # Set motor speed
    pwm_l.ChangeDutyCycle(speed)

## @brief Function to control motor to brake.
def Brake_func():
    pwm_r.ChangeDutyCycle(0)
    pwm_l.ChangeDutyCycle(0)
## @brief Function to drive the vehicle forward based on throttle and steering input.
# @param Throttle The throttle value ranging from ThrottleMinValue to ThrottleMaxValue.
# @param Steering The steering value ranging from SteeringMinValue to SteeringMaxValue.
# @retval None
def Drive_func(Throttle, Steering):
    if Steering == 0:
        SPEED = Throttle - 11
        control_motor_l(SPEED, FORWARD)
        control_motor_r(SPEED, FORWARD)

    elif Steering >= -5 and Steering <= 5:
        # Turning wide right
        if Steering > 0:
            SPEED_l = Throttle - 11
            SPEED_r = ((5 - Steering)*(Throttle - 11))/5
            control_motor_l(SPEED_l, FORWARD)
            control_motor_r(SPEED_r, FORWARD)

        # Turning wide left
        elif Steering < 0:
            SPEED_l = ((5 + Steering)*(Throttle - 11))/5
            SPEED_r = Throttle - 11
            control_motor_l(SPEED_l, FORWARD)
            control_motor_r(SPEED_r, FORWARD)

    # Turning sharp right 
    elif Steering > 5:
        SPEED_l = Throttle - 11
        SPEED_r = ((Steering - 5)*(Throttle - 11))/5 
        control_motor_l(SPEED_l, FORWARD)
        control_motor_r(SPEED_r, FORWARD)

    # Turning sharp left
    elif Steering < 5:
        SPEED_l = ((-5 - Steering)*(Throttle - 11))/5
        SPEED_r = Throttle - 11
        control_motor_l(SPEED_l, FORWARD)
        control_motor_r(SPEED_r, FORWARD)

## @brief Function to drive the vehicle in reverse based on throttle and steering input.
# @param Throttle The throttle value ranging from ThrottleMinValue to ThrottleMaxValue.
# @param Steering The steering value ranging from SteeringMinValue to SteeringMaxValue.
# @retval None
def Reverse_func(Throttle, Steering):
    if Steering == 0:
        SPEED = Throttle - 11
        control_motor_l(SPEED, BACKWARD)
        control_motor_r(SPEED, BACKWARD)

    elif Steering >= -5 and Steering <= 5:
        # Turning wide right
        if Steering > 0:
            SPEED_l = Throttle - 11
            SPEED_r = ((5 - Steering)*(Throttle - 11))/5
            control_motor_l(SPEED_l, BACKWARD)
            control_motor_r(SPEED_r, BACKWARD)

        # Turning wide left
        elif Steering < 0:
            SPEED_l = ((5 + Steering)*(Throttle - 11))/5
            SPEED_r = Throttle - 11
            control_motor_l(SPEED_l, BACKWARD)
            control_motor_r(SPEED_r, BACKWARD)

    # Turning sharp right 
    elif Steering > 5:
        SPEED_l = Throttle - 11
        SPEED_r = ((Steering - 5)*(Throttle - 11))/5 
        control_motor_l(SPEED_l, BACKWARD)
        control_motor_r(SPEED_r, BACKWARD)

    # Turning sharp left
    elif Steering < 5:
        SPEED_l = ((-5 - Steering)*(Throttle - 11))/5
        SPEED_r = Throttle - 11
        control_motor_l(SPEED_l, BACKWARD)
        control_motor_r(SPEED_r, BACKWARD)
    
## @brief Function to check the current state of the vehicle.
# @param Data The data received from the vehicle's sensors or controls.
# @retval None
def BL_check(Data):
    global recent_state, Steer, Throt, Brake_var
    
    # 112 => Brake, 114 => P, 116 => N
    if Data == Brake_Pressed or Data == P or Data == N:
        Brake_var = Brake_Pressed
        Brake_func()
        # print("     Brake")

    elif Data == D:
        if Brake_var == Brake_Released:
            recent_state = Data
            Drive_func(Throt, Steer)
            # print("     Drive")

    elif Data == R:
        if Brake_var == Brake_Released:
            recent_state = Data
            Reverse_func(Throt, Steer)
            # print("     Reverse")

    # 113 => Brake is released, then check the recent state
    elif Data == Brake_Released:
        # print("     Brake released")
        Brake_var = Brake_Released
        if recent_state == D:
            Drive_func(Throt, Steer)
            # print("     recent state: Drive")
        elif recent_state == R:
            Reverse_func(Throt, Steer)
            # print("     recent state: Reverse")

    elif Data >= SteeringMinValue and Data <= SteeringMaxValue:
        Steer = Data
        # print("     Steering")
        if Brake_var == Brake_Released:
            if recent_state == D:
                Drive_func(Throt, Steer)
                # print("     recent state: Drive")
            elif recent_state == R:
                Reverse_func(Throt, Steer)
                # print("     recent state: Reverse")
        elif Brake_var == Brake_Pressed:
            Brake_func()
            # print("     recent state: Brake")

    elif Data >= ThrottleMinValue and Data <= ThrottleMaxValue:
        Throt = Data
        # print("     Throttle")
        if Brake_var == Brake_Released:
            if recent_state == D:
                Drive_func(Throt, Steer)
                # print("     recent state: Drive")
            elif recent_state == R:
                Reverse_func(Throt, Steer)
                # print("     recent state: Reverse")
        elif Brake_var == Brake_Pressed:
            Brake_func()
            # print("     recent state: Brake")


# Set up PWM
pwm_frequency = 1000  # 1 kHz
pwm_r = GPIO.PWM(MOTOR_ENA, pwm_frequency)
pwm_l = GPIO.PWM(MOTOR_ENB, pwm_frequency)
pwm_r.start(0)
pwm_l.start(0)

# Create RFCOMM server socket
server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
server_sock.bind(("", bluetooth.PORT_ANY))
server_sock.listen(1)

# print("Waiting for Bluetooth connection...")

# Accept incoming connection
client_sock, client_info = server_sock.accept()
# print("Accepted connection from", client_info)

try:
    while True:
        # print(" !!! WHILE LOOP")
        # Receive command from the client
        data = client_sock.recv(1024)
        # print("data is received !!!")
        if not data:
            # print("NO DATA ...")
            break
        
        # Print received data and its type
        # print("Received data:", data) 
 
        # Convert ASCII data to decimal
        decimal_data = ord(data)
        # print("Decimal data:", decimal_data)

        BL_check(decimal_data)
        # print("-----------------")

finally:
    # Cleanup GPIO and close sockets
    GPIO.cleanup()
    client_sock.close()
    server_sock.close()
