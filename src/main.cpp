#include <Arduino.h>
#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial4
#define DEBUG_SERIAL Serial
const int DXL_DIR_PIN = 6; // DYNAMIXEL Shield DIR PIN

const uint8_t DXL_ID = 2;
const float DXL_PROTOCOL_VERSION = 2.0;


using namespace ControlTableItem;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup() {
   // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  pinMode(DXL_DIR_PIN,OUTPUT);
  digitalWrite(DXL_DIR_PIN,HIGH);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(115200);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT_BASED_POSITION);
  dxl.torqueOn(DXL_ID);

  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID, 100);
}

void loop() {
  dxl.setGoalVelocity(DXL_ID,2,UNIT_RPM);
  // Set Goal Current using RAW value

  if(Serial.available() > 0){
    float ind = Serial.parseFloat();
      if(ind != 0.0){
        dxl.setGoalCurrent(DXL_ID, 100 , UNIT_PERCENT);
        dxl.setGoalPosition(DXL_ID, ind, UNIT_DEGREE);
        
      }

  }
  Serial.println(dxl.getPresentPosition(DXL_ID,UNIT_DEGREE));






}