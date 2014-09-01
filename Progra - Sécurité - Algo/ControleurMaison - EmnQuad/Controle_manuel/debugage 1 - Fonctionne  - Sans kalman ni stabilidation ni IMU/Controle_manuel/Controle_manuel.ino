 
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
#include "Variables.h" // Contient toutes les variables utiles

#include "Wire.h"

/*************************************************/
/*        Librairies - Centre à Inertie          */
/*************************************************/

 
/*************************************************/
/*                   Variables                   */
/*************************************************/

//Cf : Variables.h


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


  //Visualisation de la boucle, grâce à la Led
  digitalWrite(8,HIGH);  
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  
}// fin de la fonction loop()




/*************************************************/
/*              Fonctions Annexes                */
/*************************************************/


