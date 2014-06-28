
// --- Programme Arduino ---


// --- Que fait ce programme ? ---
/* Controle du quad grâce à la télecommande*/

// --- Inclusion des librairies utilisées ---
// ...
/*#include "ADXL345_Accelero.h"
#include "BMP085_Baro_Temp.h"
#include "L3G4200D_Gyro.h"
#include "MC5883L_Magneto.h"*/
#include "Pins.h"
#include "class_v2.h"

const int LedPin = 8;   

//offset obtenu grâce aux tests

int offset_moteur_1 = -14;
int offset_moteur_2 = 1;
int offset_moteur_3 = 1;
int offset_moteur_4 = 30;

//test - Cause demarrage de moteur incompris
/*int offset_moteur_1 = 0;
int offset_moteur_2 = 0;
int offset_moteur_3 = 0;
int offset_moteur_4 = 0;*/

Controle v_courant , v_precedent;
Quadri quad(Pin_Moteur_1,offset_moteur_1,Pin_Moteur_2,offset_moteur_2,Pin_Moteur_3,offset_moteur_3,Pin_Moteur_4,offset_moteur_4);

 void setup()   { 
       Serial.begin(115200);
          
      // --- ici instructions à exécuter au démarrage ---
      Serial.println("Début initialisation");
      //Initialise les sorties variateurs
      pinMode(Pin_Moteur_1, OUTPUT);
      pinMode(Pin_Moteur_2, OUTPUT);
      pinMode(Pin_Moteur_3, OUTPUT);
      pinMode(Pin_Moteur_4, OUTPUT);
      
      //Initialise les entrées de la commande Inutile car on utilise les sorties/entrées digitale avec pulseIn qui regard les variations des portss
     /* pinMode(Pin_Throttle , INPUT);
      pinMode(Pin_Roll , INPUT);
      pinMode(Pin_Pitch , INPUT);
      pinMode(Pin_Yaw , INPUT);*/
      
      //test
      pinMode(LedPin, OUTPUT);  
      
      //Initialise les moteurs
      /*analogWrite(Pin_Moteur_1, 127);
      analogWrite(Pin_Moteur_2, 127);
      analogWrite(Pin_Moteur_3, 127);
      analogWrite(Pin_Moteur_4, 127);
      */
//      delay(2000);
    
    // Initialise la télécommande:
    v_courant.Initialisation();
    
    // Initialise les moteurs  
    analogWrite((*quad.get_moteur(1)).get_pin(), 120);
    analogWrite((*quad.get_moteur(2)).get_pin(), 120);
    analogWrite((*quad.get_moteur(3)).get_pin(), 120);
    analogWrite((*quad.get_moteur(4)).get_pin(), 120);
    delay(5000);

      Serial.println("Fini initialisation");

} // fin de la fonction setup()



void loop(){ 
      Serial.println("Je fais un tour");
   
     v_courant.Direction_commande_actualise();
     v_courant.Instruction_moteurs( v_precedent , quad );
     
     //test
     digitalWrite(8,HIGH);  
     delay(100);
     digitalWrite(8,LOW);
     delay(100);
     

 }

