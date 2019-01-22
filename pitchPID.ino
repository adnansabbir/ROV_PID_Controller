Servo back_Thruster_down;
float elapsedTimePitchY, timePitchY, timePitchYPrev;
float PIDPitchY, errorPitchY, previous_errorPitchY;
float pwmBackDown = stopThruster;
float PIDPitchY_p = 0;
float PIDPitchY_i = 0;
float PIDPitchY_d = 0;
/////////////////PIDPitchY CONSTANTS/////////////////
double kpPitchY = 2.55; //3.55
double kiPitchY = .01; //0.003
double kdPitchY = 0; //2.05
///////////////////////////////////////////////

double throttlePitchY = baseThrusterSpeed; //initial value of throttlePitchY to the motors
float desired_pitch_Y_angle, PitchY;


//balance to stay steady

void pitchPIDInit() {
  back_Thruster_down.attach(thrustersPins[2]);
  back_Thruster_down.writeMicroseconds(baseThrusterSpeed);
  timePitchY = millis(); //Start counting timePitchY in milliseconds
  //  desired_pitch_Y_angle = ypr[1] * 180 / M_PI; //This is the angle in which we whant the
  //  Serial.print("Angle set to ");
  //  Serial.println(desired_pitch_Y_angle);
}

void calculatePitch() {
  PitchY = (ypr[2] * 180 / M_PI) - pitchOffset;
  timePitchYPrev = timePitchY;  // the previous timePitchY is stored before the actual timePitchY read
  timePitchY = millis();  // actual timePitchY read
  elapsedTimePitchY = (timePitchY - timePitchYPrev) / 1000;

  errorPitchY = PitchY - desired_pitch_Y_angle;
  PIDPitchY_p = kpPitchY * errorPitchY;

  if (-pitch_Integration_tollerance < errorPitchY < pitch_Integration_tollerance)
  {
    PIDPitchY_i = PIDPitchY_i + (kiPitchY * errorPitchY);
  }
  PIDPitchY_d = kdPitchY * ((errorPitchY - previous_errorPitchY) / elapsedTimePitchY);

  /*The final PIDPitchY values is the sum of each of this 3 parts*/
  PIDPitchY = PIDPitchY_p + PIDPitchY_i + PIDPitchY_d;

  if (PIDPitchY < -400)
  {
    PIDPitchY = -400;
  }
  if (PIDPitchY > 400)
  {
    PIDPitchY = 400;
  }

  pwmBackDown = throttlePitchY - PIDPitchY;


  if (pwmBackDown < minThrusterSpeed)
  {
    pwmBackDown = minThrusterSpeed;
  }
  if (pwmBackDown > maxThrusterSpeed)
  {
    pwmBackDown = maxThrusterSpeed;
  }

}

void balance() {
  back_Thruster_down.writeMicroseconds(pwmBackDown);
  Serial.print("\tBD");
  Serial.print(pwmBackDown);
}


