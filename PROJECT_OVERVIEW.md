# Autonomous Mobile Robot (AMR) 

![Top View](IMG_8309.jpeg)
![Front View](IMG_8311.jpeg)
![Rear View](IMG_8312.jpeg)
![Undercarriage Motors](IMG_8313.jpeg)


## Project Overview

**Focus:** Embedded Systems, PWM Motor Control, Sensor Integration

This project focused on the firmware architecture and sensor integration for a differential-drive mobile robot. Utilizing a standard 4WD chassis as a testbed, I developed a C++ control loop for autonomous reactive navigation and 3-DOF manipulator control. The system integrates ultrasonic time-of-flight sensing with an H-Bridge motor driver to execute collision avoidance logic in real-time.

## System Architecture

* **Microcontroller:** ATmega328P (Arduino Uno R3).
* **Actuation (Locomotion):** L298N Dual H-Bridge Driver controlling 4x DC Geared Motors.
* **Actuation (Manipulation):** 3x PWM-controlled Servos (Base, Arm, End-Effector).  
* **Perception:** HC-SR04 Ultrasonic Sensor (40 kHz) for time-of-flight distance sensing.
* **Power Supply:** 7.4V Li-Po Bus regulated to 5V logic.

## Electrical Wiring & Pin Mapping

| Function | Component Pin | Arduino Pin |
|---------|---------------|-------------|
| Ultrasonic Trigger | TRIG | D12 |
| Ultrasonic Echo | ECHO | D13 |
| Left Motor Direction | IN1 | D2 |
| Left Motor PWM | ENA | D5 |
| Right Motor Direction | IN3 | D4 |
| Right Motor PWM | ENB | D6 |
| Claw Servo | Signal | D9 |
| Arm Servo | Signal | D10 |
| Base Servo | Signal | D11 |

## Firmware Implementation (C++)

### Autonomous Navigation Logic

The navigation firmware operates on a reactive control loop (Finite State Machine concept):

**Ping Cycle:** Triggers ultrasonic pulse (10 µs) and calculates Time-of-Flight

Threshold Check: If distance < 25 cm, the avoidance routine is triggered

Avoidance Routine:

State A (Braking): PWM to 0 instantly to halt momentum

State B (Evaluation): If distance < 15 cm (Critical Proximity), execute Reverse Impulse

State C (Re-route): Execute Differential Turn (Left Motors: REV, Right Motors: FWD) until path is clear

### Manipulator Control
Implemented a standard Pick-and-Place sequence using blocking servo movements. Calibrated specific PWM duty cycles for the "Home," "Grip," and "Drop" positions to ensure mechanical stability without servo stall.

## Engineering Challenges & Optimizations
Sensor Signal Noise
Problem: The ultrasonic sensor produced erratic readings due to acoustic reflections on soft surfaces. Solution: Implemented a hardware filter by physically isolating the sensor mount and refining the trigger timing logic to ensure clean echo reception.

## Technical Retrospective
This project served as a foundational exploration into embedded C++ and electromechanical integration. While the initial version utilized blocking delays (delay()), it highlighted the need for non-blocking architecture (millis() timers) for future multitasking—a concept I am currently implementing in my advanced robotic end-effector project.
