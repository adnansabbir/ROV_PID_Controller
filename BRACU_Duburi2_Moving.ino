#include "globalInclude.h"
#include "rollPID.h"

void setup() {

  gyro_init(2000);
  readGyro();


  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  rollPIDInit();
  pitchPIDInit();
  //  depthPIDInit();
  bar30Setup();
  movementPIDInit();
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  qualify();
  //  readGyro();
  //  //  readDepth();
  //  //  // display Euler angles in degrees
  //  //  calculateRoll();
  //  //  calculatePitch();
  //  //  //  calculateDepthOffset();
  //  //  altitudeHoldManual();
  //  //printGyro();
  //  //  moveAuv();
  //  fixHead();
  //  getDesiredAngle();
  //
  //
  //  // blink LED to indicate activity
  //  blinkState = !blinkState;
  //  digitalWrite(LED_PIN, blinkState);
}

void qualify() {
  readGyro();
  //  readDepth();
  getDepth();

  calculateRoll();
  dive();

  calculatePitch();
  balance();

  altitudeHoldManual();

  Serial.print("\t Depth Diff ");
  Serial.print(abs(depth - desired_depth));
  if (abs(depth - desired_depth) < .3)
    moveAUV();

  Serial.println();
}

int tempValofAngle;
void getDesiredAngle() {
  if (Serial.available() > 0) {
    tempValofAngle = Serial.parseInt();
    if (tempValofAngle != 0)
      setDesiredAngle(tempValofAngle);
    //    Serial.println(depth);
    //    delay(2000);
  }
}
