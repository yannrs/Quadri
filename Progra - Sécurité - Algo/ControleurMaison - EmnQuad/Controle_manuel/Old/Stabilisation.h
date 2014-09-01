/**
  *  Concaténation de l'ensemble des commandes de direction et des consignes de stabilisation
  *Entrées : - Information sur le quadricoptère, grâce à la centrale à intertie et après traitement avec le filtre de Kalman
  *          - instruction de la télécommande
  *Sorties : - Commande final envoyé
  **/
#ifndef STABILISATION_H_
#define STABILISATION_H_

#include "Variables.h"
#include "Gyroscope.h"
 /*
 Positionnement des moteurs dans une base liée au quadricoptère:
       z                          4
       |                         /
       |                        /
       |                1 ---------- 2
         -------  y          / 
      /                     /  
     /                     3
    x
   
   Donc il est définie par : 
       - theta_x (inclinaison autour de l'axe x)
       - theta_y (inclinaison autour de l'axe y)
       - theta_z (ou orientation : vers le Nord, vers le Sud ....)

   Origine : quand le quad est horizontal, vers le Nord

   Et dans un repère fixe:
       - X,Y,Z
   
 */

/************************************************************************/
/*              Acquisition des angles pour le filtre de Kalman         */
/************************************************************************/

/***************************/
/*       Variables         */
/***************************/

// Zero voltage values for the sensors - [0] = gyroY, [1] = accY, [2] = accZ
double zeroYValues[3] = { 0 };

// Results
double accYangle;
double gyroYrate;
double gyroYAngle;
double pitch;


// Zero voltage values for the sensors - [0] = gyroX, [1] = accX, [2] = accZ
double zeroXValues[3] = { 0 };

double accXangle;
double gyroXrate;
double gyroXAngle;
double roll;

/* IMU */
#define gyroY A0
#define gyroX A0
#define accX A1
#define accY A1
#define accZ A2



/*************************************************/
/*Fonctions d'acces aux valeurs du gyro et de l'acc */
/*************************************************/
double getGyroYrate() {
  getGyroValues(&X_gyro, &Y_gyro, &Z_gyro);
  // (gyroAdc-gyroZero)/Sensitivity (In quids) - Sensitivity = 0.00333/3.3*1023=1.0323
  double gyroRate = -((double)((double)Y_gyro - zeroXValues[0]) / 1.0323); //-((double)((double)analogRead(gyroY) - zeroYValues[0]) / 1.0323);
  return gyroRate;
}

double getAccY() {
  acc.read(&Xg, &Yg, &Zg);
  double accYval = ((double)Yg - zeroXValues[1]); //((double)analogRead(accY) - zeroYValues[1]);
  double accZval = ((double)Zg - zeroXValues[2]); //((double)analogRead(accZ) - zeroYValues[2]);
  // Convert to 360 degrees resolution
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We are then convert it to 0 to 2π and then from radians to degrees
  return (atan2(-accYval,-accZval)+PI)*RAD_TO_DEG;
}


// Même raisonnement que pour l'angle suivant Y
double getGyroXrate() {
  getGyroValues(&X_gyro, &Y_gyro, &Z_gyro);
  // (gyroAdc-gyroZero)/Sensitivity (In quids) - Sensitivity = 0.00333/3.3*1023=1.0323
  double gyroRate = -((double)((double)X_gyro - zeroXValues[0]) / 1.0323); //-((double)((double)analogRead(gyroxX - zeroXValues[0]) / 1.0323);
  return gyroRate;
}

double getAccX() {
  acc.read(&Xg, &Yg, &Zg);
  double accXval = ((double)Xg - zeroXValues[1]); //((double)analogRead(accX) - zeroXValues[1]);
  double accZval = ((double)Zg - zeroXValues[2]); //((double)analogRead(accZ) - zeroXValues[2]);
  // Convert to 360 degrees resolution
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We are then convert it to 0 to 2π and then from radians to degrees
  return (atan2(-accXval,-accZval)+PI)*RAD_TO_DEG;
}


void calibrateSensors() {
  for (uint8_t i = 0; i < 100; i++) { // Take the average of 100 reading
    getGyroValues(&X_gyro, &Y_gyro, &Z_gyro);
    acc.read(&Xg, &Yg, &Zg);
    
    // Pour le Pitch
    zeroYValues[0] += Y_gyro; //analogRead(gyroY);
    zeroYValues[1] += Yg; //analogRead(accY);
    zeroYValues[2] += Zg; //analogRead(accZ);
    // Pour le Roll
    zeroXValues[0] += X_gyro; //analogRead(gyroX);
    zeroXValues[1] += Xg; //analogRead(accX);
    zeroXValues[2] += Zg; //analogRead(accZ);
    delay(10);
  }
  zeroYValues[0] /= 100; // Gyro X-axis
  zeroYValues[1] /= 100; // Accelerometer Y-axis
  zeroYValues[2] /= 100; // Accelerometer Z-axis

  zeroXValues[0] /= 100; // Gyro Y-axis
  zeroXValues[1] /= 100; // Accelerometer X-axis
  zeroXValues[2] /= 100; // Accelerometer Z-axis

  acc.setZeroG(zeroXValues[1],zeroYValues[1],zeroXValues[2]);
  
/*
  if(zeroYValues[1] > 500) { // Check which side is lying down - 1g is equal to 0.33V or 102.3 quids (0.33/3.3*1023=102.3)
    zeroYValues[1] -= 102.3; // +1g when lying at one of the sides
    kalmanY.setAngle(90); // It starts at 90 degress and 270 when facing the other way
    gyroYAngle = 90;
  } else {
    zeroYValues[1] += 102.3; // -1g when lying at the other side
    kalmanY.setAngle(270);
    gyroYAngle = 270;
  }
  
  if(zeroXValues[1] > 500) { // Check which side is lying down - 1g is equal to 0.33V or 102.3 quids (0.33/3.3*1023=102.3)
    zeroXValues[1] -= 102.3; // +1g when lying at one of the sides
    kalmanX.setAngle(90); // It starts at 90 degress and 270 when facing the other way
    gyroXAngle = 90;
  } else {
    zeroXValues[1] += 102.3; // -1g when lying at the other side
    kalmanX.setAngle(270);
    gyroXAngle = 270;
  }*/
  
  // Commence à l'horizontal
  kalmanY.setAngle(0); 
  gyroYAngle = 0;
  kalmanX.setAngle(0); 
  gyroXAngle = 0;
  
/*
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);*/
}




/*
 void Stabilisation( Quad q, Pid pid, Controle c){
   
   //Objectif : Quad horizontale -> theta_x = theta_y = 0 et theta_z = cst
   
   
   
   
   
 }*/

 
#endif
