//Arduino 1.0+ only
#include "L3G4200D.h"
#include "Wire.h"

L3G4200D gyro;


void setup(){

  Wire.begin();
  Serial.begin(9600);

  Serial.println("starting up L3G4200D");

  delay(1500); //wait for the sensor to be ready 
}

void loop(){
    
  // Version avec la librairie L3G4200D
  gyro.read();
  
  Serial.print(" X : ");
  Serial.println(gyro.g.x);
  
  Serial.print(" Y : ");
  Serial.println(gyro.g.y);
  
  Serial.print(" Z : ");
  Serial.println(gyro.g.z);
  
  delay(500);
  
}

