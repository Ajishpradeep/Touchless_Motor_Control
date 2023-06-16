# Touchless_Motor_Control
This repository contains an Arduino code for controlling the fire level in the Gas stove using a servo motor based on the distance measured by an ultrasonic sensor

# Arduino Servo Control

This repository contains an Arduino code for controlling a servo motor based on the distance measured by an ultrasonic sensor. The code adjusts the position of the servo motor based on the distance readings and turns the servo on or off when a hand is detected within a certain range.

## Components Used

- Arduino board
- Servo motor
- Ultrasonic sensor (HC-SR04)

## Circuit Setup

Connect the components as follows:

- Connect the VCC and GND pins of the ultrasonic sensor to the 5V and GND pins of the Arduino board, respectively.
- Connect the TRIGGER pin of the ultrasonic sensor to digital pin 8 of the Arduino board.
- Connect the ECHO pin of the ultrasonic sensor to digital pin 9 of the Arduino board.
- Connect the signal wire (usually yellow or orange) of the servo motor to digital pin 2 of the Arduino board.
- Connect the VCC and GND pins of the servo motor to the 5V and GND pins of the Arduino board, respectively.

## Code Explanation

The Arduino code performs the following tasks:

1. Defines constants for pin assignments, servo positions, distance thresholds, and timing parameters.

2. Sets up the servo motor and initializes variables.

3. Reads the distance from the ultrasonic sensor.

4. Handles the servo position based on whether it is turned on or off.

5. Adjusts the servo position based on the measured distance.

6. Updates the servo position and determines if the servo should be turned on or off.

7. Writes the servo position and sends debug information via the serial monitor.

8. Loops continuously to perform the above tasks.

## Usage

1. Connect the Arduino board to your computer.

2. Upload the code to the Arduino board using the Arduino IDE.

3. Open the serial monitor to view debug information.

4. Move your hand within the specified range of the ultrasonic sensor to control the servo motor. The servo will turn on or off based on your hand's proximity.

## Notes

- Adjust the distance thresholds (`DISTANCE_ON`, `DISTANCE_OFF`, `MIN_DISTANCE`, `MAX_DISTANCE`, `DISTANCE_1`, `DISTANCE_2`, `DISTANCE_3`, `DISTANCE_4`, `DISTANCE_5`) according to your requirements and the characteristics of your setup.
- Ensure the correct pin assignments (`SERVO_PIN`, `TRIGGER_PIN`, `ECHO_PIN`) are set in the code based on your circuit connections.
- Make sure to install the required libraries (if any) in the Arduino IDE.

## License

This project is licensed under the [MIT License](LICENSE).
