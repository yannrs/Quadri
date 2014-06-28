
// --- Programme Arduino ---


// --- Que fait ce programme ? ---
/* Fait clignoter une LED*/

// --- Circuit à réaliser ---
// Connecter une LED en série avec résistance sur la broche 2 (configurée en sortie)

// --- Inclusion des librairies utilisées ---
// ...
/*#include "ADXL345_Accelero.h"
#include "BMP085_Baro_Temp.h"
#include "L3G4200D_Gyro.h"
#include "MC5883L_Magneto.h"*/
#include "Instruction_commande_v2.h"
#include "Instruction_moteurs.h"
#include "Pins.h"

const int LedPin = 8;   

const int Variateur_1 = 3;
const int Variateur_2 = 9;
const int Variateur_3 = 10;
const int Variateur_4 = 11;
int i =0 ;

Vecteur v;

 void setup()   { // debut de la fonction setup()
      // Serial.begin(115200);
          
      // --- ici instructions à exécuter au démarrage ---
      
      //initialise les sorties variateurs
      pinMode(Variateur_1, OUTPUT);
      pinMode(Variateur_2, OUTPUT);
      pinMode(Variateur_3, OUTPUT);
      pinMode(Variateur_4, OUTPUT);
      //Initialise les entrées de la commande
      pinMode(Pin_Throttle , INPUT);
      pinMode(Pin_Roll , INPUT);
      pinMode(Pin_Pitch , INPUT);
      pinMode(Pin_Yaw , INPUT);
      //test
      pinMode(LedPin, OUTPUT);  
      
      //initialise les moteurs
      analogWrite(Variateur_1, 127);
      analogWrite(Variateur_2, 127);
      analogWrite(Variateur_3, 127);
      analogWrite(Variateur_4, 127);
      delay(3000);
      //Serial.println("COucou");


v.w_x=0;
v.w_y=0;
v.w_z=0;
v.puissance=155;


} // fin de la fonction setup()



void loop(){ // debut de la fonction loop()
     // Serial.println("Je fais un tour");
      // --- ici instructions à exécuter par le programme principal ---
   
     Direction_commande(v);
     instruction_moteurs(v);
     
     digitalWrite(8,HIGH);  
     delay(500);
     digitalWrite(8,LOW);
     

 }

