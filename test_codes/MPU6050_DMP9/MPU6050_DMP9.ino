
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
//#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro;
//////////////////////////////////
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// Find yours here: http://www.magnetic-declination.com/
// Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
float declinationAngle = 0; //0.22;




////////////////////////////////////////////////////////////////////////////////
//the Serial needs this library https://github.com/geneReeves/ArduinoStreaming

#include "SensorFusion.h"
#include "Streaming.h"
int16_t gx, gy, gz, ax, ay, az, mx, my, mz;
float _gx, _gy, _gz, _ax, _ay, _az, _mx, _my, _mz;
float pitch, roll, yaw;
float deltat;
SF filter;

#define EULER_DATA
//#define RAW_DATA
//#define PROCESSING


#define LED_PIN LED_BUILTIN // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

  Serial.begin(115200);

  accelgyro_init();
  
  mag_init();

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  delay(1000);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  processAccelData();
  processGyroData();

  mag_update();



  // now you should read the gyroscope, accelerometer (and magnetometer if you have it also)
  // NOTE: the gyroscope data have to be in radians
  // if you have them in degree convert them with: DEG_TO_RAD example: gx * DEG_TO_RAD

  deltat = filter.deltatUpdate(); //this have to be done before calling the filter update
  //choose only one of these two:
  //filter.MahonyUpdate(_gx, _gy, _gz, _ax, _ay, _az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow
  filter.MadgwickUpdate(_gx, _gy, _gz, _ax, _ay, _az, _mx, _my, _mz, deltat);  //else use the magwick, it is slower but more accurate

  pitch = filter.getPitch();
  roll = filter.getRoll();    //you could also use getRollRadians() ecc
  yaw = filter.getYaw();


  Serial.print(roll);
  Serial.print("\t");
  Serial.print(pitch);
  Serial.print("\t");
  Serial.print(yaw);
  Serial.print("\t\t");
  Serial.println(deltat,5);



  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
