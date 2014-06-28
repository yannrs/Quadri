
// --- Programme Arduino ---
// Début octobre 2013

// --- Que fait ce programme ? ---
/* Controle du quadricoptère grâce à la télecommande
    + Stabilisation*/


/*************************************************/
/*                   Librairies                  */
/*************************************************/
#include "Pins.h"
#include "Kalman.h" // Kalman filter library see: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
#include "Stabilisation.h"

#include "Wire.h"

/*************************************************/
/*        Librairies - Centre à Inertie          */
/*************************************************/
#include "ADXL345.h" // Accéleromètre 3 axes
#include "Gyroscope.h"// Gyroscope 3 axes
 
/*************************************************/
/*                   Variables                   */
/*************************************************/
#include "Variables.h" // Contient toutes les variables utiles
ADXL345 acc; // Accéléromètre  - Défini ici pour pouvoir l'utiliser partout

/*************************************************/
/*               Initialisation                  */
/*************************************************/

void setup()   { 
  Serial.begin(19200); //Débit pour le moniteur
  Serial.println("Début initialisation");

  /*Initialisation sortie Led*/
  pinMode(LedPin, OUTPUT);  


  /* Initialisation des Capteurs*/
  /* Calibrate the gyro and accelerometer relative to ground */
  acc.begin();
  delay(100);  
  Wire.begin(); 
  delay(100);
  setupL3G4200D(2000);
  calibrateSensors(acc);



  /* Setup timing */
  loopStartTime = micros();
  timer = loopStartTime;




  Serial.println("Fini initialisation");

} // fin de la fonction setup()



/*************************************************/
/*                   Boucle                      */
/*************************************************/

void loop(){ 
  Serial.println("Je fais un tour");

      /*  Calcule du Roll et du Pitch  */
 /* Calculate pitch */
  accYangle = getAccY(acc);
  gyroYrate = getGyroYrate();
  gyroYAngle += gyroYrate*((double)(micros()-timer)/1000000);
  // See my guide for more info about calculation the angles and the Kalman filter: http://arduino.cc/forum/index.php/topic,58048.0.htm
  pitch = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros() - timer)/1000000); // Calculate the angle using a Kalman filter


  /* Calculate roll */
  accXangle = getAccX(acc);
  gyroXrate = getGyroXrate();
  gyroXAngle += gyroXrate*((double)(micros()-timer)/1000000);
  // See my guide for more info about calculation the angles and the Kalman filter: http://arduino.cc/forum/index.php/topic,58048.0.htm
  roll = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros() - timer)/1000000); // Calculate the angle using a Kalman filter
  timer = micros(); 

// Vérifier si cela fonctionne
   /*Serial.print(" Pitch :");
   Serial.println(pitch);
   Serial.print(" Roll :");
   Serial.println(roll);*/
// Pour Processing
   Serial.print("PitchRoll,");
   Serial.print(pitch);
   Serial.print(",");
   Serial.print(roll);
   Serial.println(",");

  //Visualisation de la boucle, grâce à la Led
  digitalWrite(8,HIGH);  
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  
}// fin de la fonction loop()




/*************************************************/
/*              Fonctions Annexes                */
/*************************************************/


