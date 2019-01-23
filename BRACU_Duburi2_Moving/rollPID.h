Servo right_Thruster_down;
Servo left_Thruster_down;
float elapsedTimeRollx, timeRollx, timeRollxPrev;
float PIDRollx, errorRollx, previous_errorRollx;
float  pwmLeftDown, pwmRightDown = stopThruster;
float PIDRollx_p = 0;
float PIDRollx_i = 0;
float PIDRollx_d = 0;
/////////////////PIDRollx CONSTANTS/////////////////
double kpRollx = 5; //3.55
double kiRollx = 0; //0.003
double kdRollx = 0; //2.05
///////////////////////////////////////////////

double throttleRollx = baseThrusterSpeed; //initial value of throttleRollx to the motors
float desired_roll_X_angle, rollx;


//balance to stay steady

void rollPIDInit() {
  right_Thruster_down.attach(thrustersPins[0]); //attatch the right motor to pin 3
  left_Thruster_down.attach(thrustersPins[1]);  //attatch the left motor to pin 5

  left_Thruster_down.writeMicroseconds(baseThrusterSpeed);
  right_Thruster_down.writeMicroseconds(baseThrusterSpeed);
  timeRollx = millis(); //Start counting timeRollx in milliseconds
  //  desired_roll_X_angle = ypr[1] * 180 / M_PI; //This is the angle in which we whant the
  //  Serial.print("Angle set to ");
  //  Serial.println(desired_roll_X_angle);
}

void calculateRoll() {
  rollx = (ypr[1] * 180 / M_PI) - rollOffset;
  timeRollxPrev = timeRollx;  // the previous timeRollx is stored before the actual timeRollx read
  timeRollx = millis();  // actual timeRollx read
  elapsedTimeRollx = (timeRollx - timeRollxPrev) / 1000;

  errorRollx = rollx - desired_roll_X_angle;
  PIDRollx_p = kpRollx * errorRollx;
  if (-roll_Integration_tollerance < errorRollx < roll_Integration_tollerance)
  {
    PIDRollx_i = PIDRollx_i + (kiRollx * errorRollx);
  }
  PIDRollx_d = kdRollx * ((errorRollx - previous_errorRollx) / elapsedTimeRollx);

  /*The final PIDRollx values is the sum of each of this 3 parts*/
  PIDRollx = PIDRollx_p + PIDRollx_i + PIDRollx_d;

  if (PIDRollx < -400)
  {
    PIDRollx = -400;
  }
  if (PIDRollx > 400)
  {
    PIDRollx = 400;
  }


  pwmRightDown = throttleRollx + PIDRollx;
  pwmLeftDown = throttleRollx - PIDRollx;


  if (pwmRightDown < minThrusterSpeed)
  {
    pwmRightDown = minThrusterSpeed;
  }
  if (pwmRightDown > maxThrusterSpeed)
  {
    pwmRightDown = maxThrusterSpeed;
  }
  //Left
  if (pwmLeftDown < minThrusterSpeed)
  {
    pwmLeftDown = minThrusterSpeed;
  }
  if (pwmLeftDown > maxThrusterSpeed)
  {
    pwmLeftDown = maxThrusterSpeed;
  }
  
}

void dive(){
  left_Thruster_down.writeMicroseconds(pwmLeftDown);
  right_Thruster_down.writeMicroseconds(pwmRightDown);
  
  Serial.print("\tLD ");
  Serial.print(pwmLeftDown);
  Serial.print("\tRD ");
  Serial.print(pwmRightDown);
  }


