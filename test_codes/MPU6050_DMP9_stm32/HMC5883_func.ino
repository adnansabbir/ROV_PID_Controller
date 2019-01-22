
void mag_init() {

  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();
}


void mag_update()
{
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  _mx = event.magnetic.x;
  _my = event.magnetic.y;
  _mz = event.magnetic.z;

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  //  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  //  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  //  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  //  float heading = atan2(event.magnetic.y, event.magnetic.x);
  //
  //  heading += declinationAngle;
  //
  //  // Correct for when signs are reversed.
  //  if (heading < 0)
  //    heading += 2 * PI;
  //
  //  // Check for wrap due to addition of declination.
  //  if (heading > 2 * PI)
  //    heading -= 2 * PI;
  //
  //  // Convert radians to degrees for readability.
  //  float headingDegrees = heading * 180 / M_PI;
  //
  //  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  // delay(15);
}




void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
