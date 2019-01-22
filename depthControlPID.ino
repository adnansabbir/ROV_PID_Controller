//float elapsedTimedepth, timedepth, timedepthPrev;
//float PIDdepth, errordepth, previous_errordepth;
//float PIDdepth_p = 0;
//float PIDdepth_i = 0;
//float PIDdepth_d = 0;
///////////////////PIDDepth CONSTANTS/////////////////
//double kpDepth = 20; //3.55
//double kiDepth = 50; //0.003
//double kdDepth = 10; //2.05
/////////////////////////////////////////////////
//
////double targetDepth = 5; //initial value of targetDepth to the motors
//
//
//
////balance to stay steady
//
//void depthPIDInit() {
//  timedepth = millis(); //Start counting timedepth in milliseconds
//}
//
//void calculateDepthOffset() {
////  getDepth();
//  timedepthPrev = timedepth;  // the previous timedepth is stored before the actual timedepth read
//  timedepth = millis();  // actual timedepth read
//  elapsedTimedepth = (timedepth - timedepthPrev) / 1000;
//
//  errordepth = depth - desired_depth;
//  
//  PIDdepth_p = kpDepth * errordepth;
//  PIDdepth_i = PIDdepth_i + (kiDepth * errordepth);
//  PIDdepth_d = kdDepth * ((errordepth - previous_errordepth));
//
//  /*The final PIDdepth values is the sum of each of this 3 parts*/
//  PIDdepth = PIDdepth_p + PIDdepth_i + PIDdepth_d;
//
//  if (PIDdepth < -400)
//  {
//    PIDdepth = -400;
//  }
//  if (PIDdepth > 400)
//  {
//    PIDdepth = 400;
//  }
//
//  throttleRollx = baseThrusterSpeed - PIDdepth;
//
//
//  if (throttleRollx <minThrusterSpeed)
//  {
//    throttleRollx = minThrusterSpeed;
//  }
//  if (throttleRollx > maxThrusterSpeed)
//  {
//    throttleRollx = maxThrusterSpeed;
//  }
////  Serial.print(throttleRollx);Serial.print("\t");Serial.println(depth);
//}
//
float tempValofDepth;
void getDepth(){
  if(Serial.available()>0){
    tempValofDepth = Serial.parseFloat();
    if(tempValofDepth!=0)
      depth = tempValofDepth;
//    Serial.println(depth);
//    delay(2000);
    }
  }


