# 🚗 CAN Bus Based Obstacle Avoidance with TF-Luna LiDAR

This project implements **Obstacle Detection & Avoidance** using **CAN Bus Protocol** with MCP2515 modules.  
A TF-Luna LiDAR sensor measures the distance to obstacles, and the data is transmitted via CAN bus to another Arduino UNO that controls a DC motor.

---

## ⚡ Features
- CAN bus communication using MCP2515
- TF-Luna LiDAR for distance measurement
- Motor control based on safe distance threshold
- Modular design with separate transmitter and receiver nodes

---

## 🛠️ Hardware Used
- Arduino UNO (x2)
- MCP2515 CAN Bus Module (x2)
- TF-Luna LiDAR sensor
- L298N Motor Driver
- DC Motor
- Jumper wires & Breadboard

---

## 🔌 Connections

### Transmitter Node (LiDAR + CAN Tx)
- TF-Luna → Arduino UNO (UART)
- Arduino UNO → MCP2515 (SPI)

### Receiver Node (Motor Control + CAN Rx)
- MCP2515 → Arduino UNO
- Arduino UNO → Motor Driver → DC Motor

---
