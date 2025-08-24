#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);  // CS pin

#define MOTOR_PIN 6    // Motor control pin (via motor driver IN1/EN)

const int SAFE_DISTANCE = 30;  // in cm

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);   // Motor OFF initially

  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x100) {  // LiDAR CAN ID
      int distance = canMsg.data[0] | (canMsg.data[1] << 8);

      Serial.print("Received Distance: ");
      Serial.println(distance);

      if (distance < SAFE_DISTANCE) {
        digitalWrite(MOTOR_PIN, LOW);  // Stop motor
        Serial.println("Obstacle detected! Motor stopped.");
      } else {
        digitalWrite(MOTOR_PIN, HIGH); // Start motor
        Serial.println("Path clear. Motor running.");
      }
    }
  }
}
