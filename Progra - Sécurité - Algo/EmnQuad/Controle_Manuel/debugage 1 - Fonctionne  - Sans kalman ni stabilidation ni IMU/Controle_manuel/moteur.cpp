#include "moteur.h"


/**************************************************
 *                 Class Moteur
 **************************************************/
//---------------- Constructeur -------------------//
Moteur::Moteur(int pin1, int offset1){
  pin = pin1;
  offset = offset1;
  puissance2_m = 120;
}

//------------------ Getters ---------------------//
int Moteur::get_pin(){
  return pin;
}

int Moteur::get_offset(){
  return offset;
}

int Moteur::get_puissance_m(){
  return puissance2_m;
}

//------------------ Setters ---------------------//
void Moteur::set_puissance_m(int puis){
  puissance2_m=puis;
}


void Moteur::Applique_puissance_m(){  
 analogWrite(get_pin(), get_puissance_m()); 
}

