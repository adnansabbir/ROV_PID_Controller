Servo Thruster1, Thruster2, Thruster3, Thruster4;
float elapsedTimeMovement, timeMovement, timeMovementPrev;
float PIDMovement, errorMovement, previous_errorMovement;
float PIDMovement_p = 0;
float PIDMovement_i = 0;
float PIDMovement_d = 0;
/////////////////PIDMovement CONSTANTS/////////////////
double kpMovement = 5; //3.55
double kiMovement = 0; //0.003
double kdMovement = 0; //2.05
///////////////////////////////////////////////

float desired_angle, angle;

float errorAngle;

int thruster1PWM, thruster2PWM, thruster3PWM, thruster4PWM = baseThrusterSpeed;

void movementPIDInit() {
  Thruster1.attach(thrustersPins[3]);
  Thruster2.attach(thrustersPins[4]);
  Thruster3.attach(thrustersPins[5]);
  Thruster4.attach(thrustersPins[6]);

  Thruster1.writeMicroseconds(baseThrusterSpeed);
  Thruster2.writeMicroseconds(baseThrusterSpeed);
  Thruster3.writeMicroseconds(baseThrusterSpeed);
  Thruster4.writeMicroseconds(baseThrusterSpeed);


  timeMovement = millis(); //Start counting timeRollx in milliseconds
  //  desired_roll_X_angle = ypr[1] * 180 / M_PI; //This is the angle in which we whant the
  //  Serial.print("Angle set to ");
  //  Serial.println(desired_roll_X_angle);
  desired_angle = (ypr[0] * 180 / M_PI)+180;
}

void calculatePID() {
  angle = (ypr[0] * 180 / M_PI)+180;
  timeMovementPrev = timeMovement;  // the previous timeMovement is stored before the actual timeMovement read
  timeMovement = millis();  // actual timeMovement read
  elapsedTimeMovement = (timeMovement - timeMovementPrev) / 1000;

  errorMovement = angle - desired_angle;
  PIDMovement_p = kpMovement * errorMovement;
  PIDMovement_i = PIDMovement_i + (kiMovement * errorMovement);
  PIDMovement_d = kdMovement * ((errorMovement - previous_errorMovement) / elapsedTimeMovement);

  /*The final PIDPitchY values is the sum of each of this 3 parts*/
  PIDMovement = PIDMovement_p + PIDMovement_i + PIDMovement_d;

  if (PIDMovement < -400)
  {
    PIDMovement = -400;
  }
  if (PIDMovement > 400)
  {
    PIDMovement = 400;
  }


}

void moveAUV() {
  calculatePID();
  thruster2PWM = maxMovementSpeed + PIDMovement;
  thruster3PWM = maxMovementSpeed + PIDMovement;

  thruster1PWM = maxMovementSpeed - PIDMovement;
  thruster4PWM = maxMovementSpeed - PIDMovement;

  if (thruster2PWM > maxMovementSpeed) {
    thruster2PWM = maxMovementSpeed;
    thruster3PWM = maxMovementSpeed;
  }

  if (thruster1PWM > maxMovementSpeed) {
    thruster1PWM = maxMovementSpeed;
    thruster4PWM = maxMovementSpeed;
  }

  Serial.print("\tLeft Thruster ");
  Serial.print(thruster1PWM);
  Serial.print("\tRight Thruster ");
  Serial.print(thruster2PWM);
//  Serial.print("\tAngle ");
//  Serial.println(angle);
}

void setDesiredAngle(int angle){
  desired_angle+=angle;
  if(desired_angle>360)
    desired_angle = desired_angle-360;
  if(desired_angle<0)
    desired_angle = desired_angle+360;
  }
  

void fixHead() {
  calculatePID();

  thruster2PWM = baseThrusterSpeed + PIDMovement;
  thruster3PWM = baseThrusterSpeed + PIDMovement;

  thruster1PWM = baseThrusterSpeed - PIDMovement;
  thruster4PWM = baseThrusterSpeed - PIDMovement;

  Serial.print("Left Thruster ");
  Serial.print(thruster1PWM);
  Serial.print("\tRight Thruster ");
  Serial.print(thruster2PWM);
  Serial.print("\tAngle ");
  Serial.print(angle);
  Serial.print("\tTarget Angle ");
  Serial.println(desired_angle);

}
