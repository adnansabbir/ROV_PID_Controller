
void accelgyro_init() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize device
  Serial.println("Initializing I2C devices...");
  /*
           setClockSource(MPU6050_CLOCK_PLL_XGYRO);
           setFullScaleGyroRange(MPU6050_GYRO_FS_250);
           setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  */
  accelgyro.initialize();

  //Your offsets:  -5783 - 2000   968  - 72  - 970  - 326  //gy521
  //Your offsets:  -4720   1987  1022     9  - 40      26  // gy88 10dof
  //               -5030   1989  1035    13  - 42      31  //gy88 10dof_stm
  //
  //Data is printed as: acelX acelY acelZ giroX giroY giroZ
  accelgyro.setZAccelOffset(1022);

  accelgyro.setXGyroOffset(9);
  accelgyro.setYGyroOffset(-40);
  accelgyro.setZGyroOffset(26);


  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}




void processGyroData() {
  _gx = gx / 131.0 * DEG_TO_RAD;
  _gy = gy / 131.0 * DEG_TO_RAD;
  _gz = gz / 131.0 * DEG_TO_RAD;
}

void processAccelData() {
  _ax = ax / 16384.0;
  _ay = ay / 16384.0;
  _az = az / 16384.0;
}
