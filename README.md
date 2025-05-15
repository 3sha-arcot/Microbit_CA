# README - Tele-Operated Micro:bit & Arduino Vehicle Prototype

## Project Overview
This project involves the design and implementation of a low-cost remote-driving vehicle using two BBC micro:bit v2 boards for tilt-based control and an Arduino Mega for motor actuation and obstacle avoidance. The system demonstrates a complete sensor-to-actuator loop, including wireless communication, real-time obstacle detection, and safety overrides.

## Team Members
1. Aangir Doshi (BT2024078)  
2. Thrissha Arcot (BT2024024)  
3. Abhyudaya Singh (BT2024180)  
4. Ayush Patel (BT2024171)  
5. Utkarsh Rastogi (BT2024119)  
6. Shive Bhat (BT2024067)  
7. Vraj Vashi (BT2024062)  

**Course:** Computer Architecture  
**Professor:** Prof. Karthikeyan Vaidyanathan  

## Hardware Components
- **BBC micro:bit v2 (×2)**: Used for tilt-based control and wireless communication.
- **Arduino Mega 2560**: Processes commands and controls motors.
- **Adafruit Motor Shield v1**: Drives two DC motors (left and right).
- **HC-SR04 Ultrasonic Sensors (×4)**: Provides obstacle detection (front, left, right, back).
- **Power Supply**: Two 9V batteries for motors; micro:bits powered by USB battery packs; Arduino powered via laptop.

## Wiring Setup
- **Tilt-Controller micro:bit**: Communicates wirelessly with the relay micro:bit.
- **Relay micro:bit**: Forwards commands via UART to Arduino Mega (P0 → Arduino pin 19).
- **Motor Shield**: Stacked on Arduino Mega, connected to motors (M1: left, M2: right).
- **Ultrasonic Sensors**: Each sensor's TRIG and ECHO pins connected to distinct digital pins on the Arduino.
- **Common Ground**: All devices share a common ground.

## Software Implementation
### 1. Tilt-Remote Code (micro:bit)
- **Language**: Python (micro:bit Python Editor).
- **Features**:
  - Reads accelerometer data (x, y-axis).
  - Maps tilt values to discrete speeds (dead-zone: ±400, thresholds: ±800).
  - Sends left/right motor speeds wirelessly to the relay micro:bit.

### 2. Relay Code (micro:bit)
- **Function**: Receives wireless commands and forwards them via UART to the Arduino.

### 3. Arduino Logic
- **Language**: C++ (Arduino IDE).
- **Features**:
  - Parses motor speed commands from UART.
  - Implements obstacle avoidance using ultrasonic sensors.
  - Overrides remote commands if obstacles are detected (e.g., stops or reverses if front obstacle < 20 cm).
  - Controls motors via the Adafruit Motor Shield.

## Testing & Observations
- **Functional Check**: Vehicle responds accurately to tilt commands (forward, backward, left, right).
- **Safety Test**: Obstacle avoidance successfully prevents collisions in static environments.
- **Feedback**: Controls are intuitive, with minor jitter near dead-zone thresholds.

## Contributions
- **Hardware Integration**: Aangir Doshi, Thrissha Arcot, Vraj Vashi, Abhyudaya Singh.
- **Tilt-Control Algorithm**: Ayush Patel, Utkarsh Rastogi, Shive Bhat.
- **Obstacle Avoidance Logic**: Aangir Doshi, Abhyudaya Singh, AI models.
- **Guidance**: Seniors Nitheezkant R and Ishan Jha.

## Conclusion
This project successfully demonstrates a teleoperated vehicle pipeline, from human input to motor actuation with safety overrides. It serves as a foundation for future enhancements, such as video streaming or lower-latency communication modules.

## Appendix
- **Full Code Listings**: Available in attached `.py` and `.ino` files.
- **Component Datasheets**: Refer to HC-SR04 and AFMotor library documentation.
