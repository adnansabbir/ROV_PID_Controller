int startTimeDepth = millis();
//bool aboveTargetDepth = true;
//int baseSpeed;

void altitudeHoldManual() {
  if (depth < desired_depth) {
      throttleRollx +=(desired_depth-depth)*20;
  } else if (depth > desired_depth) {
      throttleRollx +=(desired_depth-depth)*20;
  }

  if (throttleRollx > 1900)
    throttleRollx = 1900;
  if (throttleRollx < 1100)
    throttleRollx = 1100;
//  Serial.println(baseSpeed);
}
