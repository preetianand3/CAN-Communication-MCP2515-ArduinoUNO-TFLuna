#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);   // CS pin for MCP2515

#define LIDAR_SERIAL Serial2   // Use Serial2 if available, else SoftwareSerial

int readLidarDistance() {
  uint8_t buf[9];
  int dist = -1;

  if (LIDAR_SERIAL.available() >= 9) {
    if (LIDAR_SERIAL.read() == 0x59) {   // Frame header 1
      if (LIDAR_SERIAL.read() == 0x59) { // Frame header 2
        for (int i = 0; i < 7; i++) {
          buf[i] = LIDAR_SERIAL.read();
        }
        dist = buf[0] + (buf[1] << 8);   // distance in cm
      }
    }
  }
  return dist;
}

void setup() {
  Serial.begin(9600);
  LIDAR_SERIAL.begin(115200);   // TF-Luna default baudrate

  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  int distance = readLidarDistance();

  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.println(distance);

    canMsg.can_id  = 0x100;   // CAN ID for LiDAR data
    canMsg.can_dlc = 2;       // sending 2 bytes
    canMsg.data[0] = distance & 0xFF;       // lower byte
    canMsg.data[1] = (distance >> 8) & 0xFF; // higher byte

    mcp2515.sendMessage(&canMsg);
    delay(100);
  }
}
