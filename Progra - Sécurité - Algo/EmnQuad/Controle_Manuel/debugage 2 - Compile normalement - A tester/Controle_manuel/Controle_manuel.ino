
// --- Programme Arduino ---
// Début octobre 2013

// --- Que fait ce programme ? ---
/* Controle du quadricoptère grâce à la télecommande
    + Stabilisation*/


/*************************************************/
/*                   Librairies                  */
/*************************************************/
#include "Pins.h"
#include "controle.h" // Utilise la Télécommande pour asservir le quad
#include "moteur.h" // Contient toutes les infos sur 1 moteur
#include "quadri.h" // Contient toutes les infos sur 1 quadricoptère
#include "telecommande.h" // Contient les paramétres de la télécommande (Min, max...)
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
  Serial.begin(115200); //Débit pour le moniteur
  Serial.println("Début initialisation");

  /*Initialise les sorties Variateurs*/
  pinMode(Pin_Moteur_1, OUTPUT);
  pinMode(Pin_Moteur_2, OUTPUT);
  pinMode(Pin_Moteur_3, OUTPUT);
  pinMode(Pin_Moteur_4, OUTPUT);

  /*Initialisation sortie Led*/
  pinMode(LedPin, OUTPUT);  


  /*Initialise la Télécommande:*/
  telecommande.Initialisation(false);// False -> Utilisation des valeurs pré-enregistrées.
  
  /* Initialise les Moteurs  */
  analogWrite((*quad.get_moteur(1)).get_pin(), 120);
  analogWrite((*quad.get_moteur(2)).get_pin(), 120);
  analogWrite((*quad.get_moteur(3)).get_pin(), 120);
  analogWrite((*quad.get_moteur(4)).get_pin(), 120);
  delay(5000);


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

  v_courant.Direction_commande_actualise(telecommande); // Va chercher les instructions de la télécommande
  v_courant.Conversion_en_Instruction_moteurs( v_precedent , quad ); // Crée les instructions à envoyer aux moteurs
  quad.Applique_commande(); // Envoie des instructions


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
   Serial.print(" Pitch :");
   Serial.println(pitch);
   Serial.print(" Roll :");
   Serial.println(roll);


  //Visualisation de la boucle, grâce à la Led
  digitalWrite(8,HIGH);  
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  
}// fin de la fonction loop()




/*************************************************/
/*              Fonctions Annexes                */
/*************************************************/


