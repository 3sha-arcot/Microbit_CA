Tele-Operated Micro:bit & Arduino Vehicle Prototype

Overview
This project is a low-cost, tele-operated vehicle prototype developed as part of the Computer Architecture course under Prof. Karthikeyan Vaidyanathan. The system uses two BBC micro:bit v2 boards for tilt-based control and an Arduino Mega for motor actuation and obstacle avoidance. The vehicle demonstrates a complete sensor-to-actuator pipeline with wireless communication and real-time safety overrides using four HC-SR04 ultrasonic sensors.

Team Members
Aangir Doshi (BT2024078)
Thrissha Arcot (BT2024024)
Abhyudaya Singh (BT2024180)
Ayush Patel (BT2024171)
Utkarsh Rastogi (BT2024119)
Shive Bhat (BT2024067)
Vraj Vashi (BT2024062)

System Components

Hardware
2x BBC micro:bit v2: One for tilt control (accelerometer) and one for relaying commands.
Arduino Mega 2560: Processes commands and drives motors.
Adafruit Motor Shield v1: Controls two DC motors (left: M1, right: M2).
4x HC-SR04 Ultrasonic Sensors: Mounted front, left, right, and back for obstacle detection.
Power Supply: Two 9V batteries for motors, USB battery packs for micro:bits, and laptop connection for Arduino.

Software
Tilt-Remote (micro:bit): Python code reads accelerometer data, maps tilt to motor speeds, and sends via 2.4 GHz radio.
Relay (micro:bit): Python code receives radio packets and forwards them to Arduino via UART.
Arduino Logic: C++ code parses commands, reads sonar sensors, implements obstacle avoidance, and drives motors.

Setup Instructions

Hardware Wiring:
Connect the tilt-controller micro:bit to a USB battery pack.
Wire the receiver micro:bit’s P0 to Arduino Mega’s pin 19 (Serial1 RX).
Stack the Adafruit Motor Shield on the Arduino Mega.
Connect ultrasonic sensors:
Front: TRIG 28, ECHO 29
Left: TRIG 24, ECHO 25
Back: TRIG 22, ECHO 23
Right: TRIG 26, ECHO 27
Attach motors to Motor Shield ports M1 (left) and M2 (right).
Ensure all devices share a common ground.


Software Installation:
Flash the tilt-remote code to the first micro:bit using the micro:bit Python Editor.
Flash the relay code to the second micro:bit.
Upload the Arduino code to the Mega using the Arduino IDE with the AFMotor library installed.


Dependencies:
micro:bit: Python runtime (included in micro:bit firmware).
Arduino: AFMotor library for motor control.
Tools: micro:bit Python Editor, Arduino IDE.

Usage
Power on all components.
Hold the tilt-controller micro:bit and tilt it to control the vehicle:
Forward/back: Tilt along the Y-axis.
Left/right: Tilt along the X-axis.
The vehicle responds to tilt commands and automatically avoids obstacles using sonar data:
Stops or pivots if an obstacle is within 20 cm in front.
Adjusts turns to avoid side collisions.
Halts if reversing into an obstacle.

Project Structure
tilt_remote.py – Control micro:bit code
relay_node.py – Receiver micro:bit code
vehicle_controller.ino – Arduino code
Datasheets: HC-SR04, Adafruit Motor Shield
Full wiring diagrams

Testing Observations
Functionality: The vehicle responds accurately to tilt inputs, supporting forward/back and arc turns.
Safety: Sonar-based overrides successfully prevent collisions in static obstacle courses.
Controls: Intuitive but may exhibit minor jitter near dead-zone thresholds (±400).

Contributions
Hardware Integration: Aangir Doshi, Thrissha Arcot, Vraj Vashi, Abhyudaya Singh
Tilt-Control Algorithm: Ayush Patel, Utkarsh Rastogi, Shive Bhat
Obstacle Avoidance Logic: Aangir Doshi, Abhyudaya Singh, AI models
Guidance: Nitheezkant R, Ishan Jha

Future Enhancements
Add video streaming for richer feedback.
Implement lower-latency communication (e.g., 5G modules).
Enhance control precision by refining dead-zone filtering.

License
This project is for educational purposes and is not licensed for commercial use. Component datasheets and libraries are subject to their respective licenses.
Acknowledgments
We thank Prof. Karthikeyan Vaidyanathan for guidance and seniors Nitheezkant R and Ishan Jha for their support.
