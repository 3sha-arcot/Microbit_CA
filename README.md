# Microbit_CA
The project is a tele-operated Micro:bit and Arduino vehicle prototype.It presents a low-cost, tilt-controlled vehicle using:

    Two BBC micro:bit v2 boards (for wireless control and communication),

    An Arduino Mega 2560 (for motor control and obstacle avoidance),

    Four HC-SR04 ultrasonic sensors (for safety overrides),

    An Adafruit Motor Shield (for driving the DC motors).

The prototype demonstrates a full sensor-to-actuator loop and serves as a foundation for more advanced teleoperation systems.
System Architecture
Nodes

    Control Node (Handheld):
    Tilt-based input using micro:bit accelerometer.

    Relay Node (On-Vehicle micro:bit):
    Receives control data over radio and transmits via UART to Arduino.

    Processing & Actuation Node (Arduino Mega):
    Parses commands, reads sensor inputs, and controls motors with safety overrides.

Hardware Components

    BBC micro:bit v2 (×2)

        Accelerometer, 2.4 GHz radio

    Arduino Mega 2560

        UART communication, GPIO support

    Adafruit Motor Shield v1

        Controls 2 DC motors

    HC-SR04 Ultrasonic Sensors (×4)

        Front, Back, Left, Right configuration

    Power Supply

        Motors: Two 9V batteries

        Micro:bits: USB battery packs

        Arduino: USB via laptop


Software Components
1. Tilt-Control Code (micro:bit)

    Uses accelerometer to determine X/Y tilt

    Maps tilt to speed values (with dead-zone logic)

    Sends speeds over radio every 10ms

2. Relay micro:bit Code

    Receives radio packets and forwards them via UART at 9600 baud

3. Arduino Code

    Parses UART data

    Reads sonar distances

    Overrides user input if obstacles are too close

    Drives motors accordingly

Key Features

    Real-time Tilt Control
    Smooth user interaction via micro:bit accelerometer

    Wireless Communication
    Low-latency control using micro:bit radio and UART bridging

    Obstacle Avoidance
    Sensor-based logic prevents collisions by overriding commands

Results

    Accurate Control: Vehicle successfully responds to tilt directions

    Effective Safety Layer: Obstacle avoidance logic overrides unsafe commands

    User Experience: Controls are intuitive, minor jitter near dead-zone

Contributions

    Hardware: Aangir Doshi, Thrissha Arcot, Vraj Vashi, Abhyudaya Singh

    Tilt-Control Algorithm: Ayush Patel, Utkarsh Rastogi, Shive Bhat

    Obstacle Avoidance Logic: Aangir Doshi, Abhyudaya Singh, AI Models

    Guidance: Nitheezkant R, Ishan Jha

Future Work

    Add video streaming for richer feedback

    Explore low-latency communication (e.g., 5G or Wi-Fi modules)

    Upgrade motor control with PID algorithms

Files

    tilt_remote.py – Control micro:bit code

    relay_node.py – Receiver micro:bit code

    vehicle_controller.ino – Arduino code

    Datasheets: HC-SR04, Adafruit Motor Shield

    Full wiring diagrams (optional)

