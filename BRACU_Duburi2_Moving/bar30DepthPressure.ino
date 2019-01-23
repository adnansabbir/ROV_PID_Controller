//#include <Wire.h>
#include "MS5837.h"

MS5837 sensor;

void bar30Setup() {
  
//  Serial.begin(9600);
  
  Serial.println("Initializing Bar30 Depth Sensor");
  
//  Wire.begin();

  sensor.setModel(MS5837::MS5837_30BA);
  sensor.init();
  
  sensor.setFluidDensity(997); // kg/m^3 (997 freshwater, 1029 for seawater)
}

void readDepth() {

  sensor.read();
//  sensor.pressure();
//  sensor.temperature();
  depth = sensor.depth();
//  sensor.altitude();

  Serial.print("\t Depth ");
  Serial.print(sensor.depth());

//  Serial.print("Pressure: "); 
//  Serial.print(sensor.pressure()); 
//  Serial.println(" mbar");
//  
//  Serial.print("Temperature: "); 
//  Serial.print(sensor.temperature()); 
//  Serial.println(" deg C");
//  
//  Serial.print("Depth: "); 
//  Serial.print(sensor.depth()); 
//  Serial.println(" m");
//  
//  Serial.print("Altitude: "); 
//  Serial.print(sensor.altitude()); 
//  Serial.println(" m above mean sea level");
//
//  delay(1000);
}
