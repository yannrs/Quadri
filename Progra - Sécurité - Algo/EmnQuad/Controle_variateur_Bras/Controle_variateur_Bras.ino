#include <Wire.h>
#include "ADXL345.h"
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 105; //I2C address of the L3G4200D
ADXL345 adxl; 

int x,y,z;
int dx,dy,dz;
int x2,y2,z2; 
const int Variateur_1 = 3;
int j = 150;

void setup(){

  Wire.begin();
  Serial.begin(9600);

 
  Serial.println("starting up L3G4200D");
  setupL3G4200D(2000); // Configure L3G4200  - 250, 500 or 2000 deg/sec

 adxl.powerOn();


 //set activity/ inactivity thresholds (0-255)
 adxl.setActivityThreshold(75); //62.5mg per increment
 adxl.setInactivityThreshold(75); //62.5mg per increment
 adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

 //look of activity movement on this axes - 1 == on; 0 == off 
 adxl.setActivityX(1);
 adxl.setActivityY(1);
 adxl.setActivityZ(1);

 //look of inactivity movement on this axes - 1 == on; 0 == off
 adxl.setInactivityX(1);
 adxl.setInactivityY(1);
 adxl.setInactivityZ(1);

 //look of tap movement on this axes - 1 == on; 0 == off
 adxl.setTapDetectionOnX(0);
 adxl.setTapDetectionOnY(0);
 adxl.setTapDetectionOnZ(1);

 //set values for what is a tap, and what is a double tap (0-255)
 adxl.setTapThreshold(50); //62.5mg per increment
 adxl.setTapDuration(15); //625μs per increment
 adxl.setDoubleTapLatency(80); //1.25ms per increment
 adxl.setDoubleTapWindow(200); //1.25ms per increment

 //set values for what is considered freefall (0-255)
 adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
 adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

 //setting all interupts to take place on int pin 1
 //I had issues with int pin 2, was unable to reset it
 adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,  ADXL345_INT1_PIN );
 adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,  ADXL345_INT1_PIN );
 adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,  ADXL345_INT1_PIN );
 adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,   ADXL345_INT1_PIN );
 adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,  ADXL345_INT1_PIN );

 //register interupt actions - 1 == on; 0 == off 
 adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
 adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
 adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT, 1);
 adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,  1);
 adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
 
 adxl.readAccel(&dx, &dy, &dz);
 delay(200);
 adxl.readAccel(&dx, &dy, &dz);
  delay(1500); //wait for the sensor to be ready 
  
  pinMode(Variateur_1, OUTPUT);
        
      for(int i=100; i< 140; i=i+2){
          analogWrite(Variateur_1, i);
          Serial.println( i);
          delay(500);
      }


      analogWrite(Variateur_1, 127);
      
}


void loop(){
   getGyroValues();  // This will update x, y, and z with new values

/*
  Serial.println(" ");
  Serial.print(x);

  Serial.print(" ");
  Serial.print(y);

  Serial.print(" ");
  Serial.println(z);
*/
  //Boring accelerometer stuff  
   int x2,y2,z2; 
   adxl.readAccel(&x2, &y2, &z2); //read the accelerometer values and store them in variables x,y,z
  
   // Output x,y,z values - Commented out
  // Serial.print(x2-dx); Serial.print(" ");
   Serial.print(y2-dy);Serial.print(" ");
  // Serial.println(z2-dz);Serial.print(" ");
 
    Serial.println(j);Serial.print(" ");
 
      getGyroValues();
      adxl.readAccel(&x2, &y2, &z2);
      
      if(y2-dy<0 && j<200){
        j+=1;
      }
      else j-=1;
      
      analogWrite(Variateur_1, j);
      delay(250);
 }
 

void getGyroValues(){

  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  x = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  y = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  z = ((zMSB << 8) | zLSB);
}

int setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
        // waiting
    }

    v = Wire.read();
    return v;
}

