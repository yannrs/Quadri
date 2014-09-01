/*
#include <Wire.h>
#include "ADXL345.h"


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
int dx = 0;
int dy = 0;
int dz = 0;

void setup(){
 Serial.begin(9600);
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
}


void loop(){
 
 //Boring accelerometer stuff  
 int x,y,z; 
 adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables x,y,z

 // Output x,y,z values - Commented out
 Serial.print(x-dx); Serial.print(" ");
 Serial.print(y-dy);Serial.print(" ");
 Serial.println(z-dz);Serial.print(" ");
delay(200);

 
 //getInterruptSource clears all triggered actions after returning value
 //so do not call again until you need to recheck for triggered actions
 byte interrupts = adxl.getInterruptSource();

}
*/

/*const int Variateur_1 = 3;

  void setup()   { // debut de la fonction setup()
      Serial.begin(9600);
      pinMode(Variateur_1, OUTPUT);
        
      for(int i=100; i< 140; i=i+2){
          analogWrite(Variateur_1, i);
          Serial.println( i);
          delay(500);
      }
      analogWrite(Variateur_1, 127);
} 
     
void loop(){
    Serial.println("Je fais un tour");
    int j = 150;
    while (j<170 )
    {
        analogWrite(Variateur_1, j);
        Serial.println(j);
        delay(1000);
        j=j+2;
        if(j==170) {
          delay(5000);
        }
     }
     
    while (j>160)
    {
        analogWrite(Variateur_1, j);
        Serial.println(j);
        delay(1000);
        j=j-4;
     }
    // Arrêt moteur
     digitalWrite(Variateur_1, 127);
 }*/
