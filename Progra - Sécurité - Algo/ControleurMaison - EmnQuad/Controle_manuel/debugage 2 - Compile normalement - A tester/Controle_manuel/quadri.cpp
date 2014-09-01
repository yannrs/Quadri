#include "quadri.h"


/**************************************************
 *                 Class Quadri
 **************************************************/
//---------------- Constructeur -------------------//

/*Quadri::Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4){
 moteur_1( pin1, off1);
 moteur_2( pin2, off2);
 moteur_3( pin3, off3);
 moteur_4( pin4, off4);
 }*/
Quadri::Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4) :  
moteur_1( pin1, off1),  moteur_2( pin2, off2) ,  moteur_3( pin3, off3),  moteur_4( pin4, off4) 
{
}

//------------------ Methodes ---------------------//
/**
 * Retourne l'adresse du moteur "i"
 */
Moteur* Quadri::get_moteur(int i){      
  switch(i){
  case 1:
    return &moteur_1;
    break;
  case 2:
    return &moteur_2;
    break;
  case 3:
    return &moteur_3;
    break;
  default: // cas i = 4
    return &moteur_4;
    break;
  }
}  


/*
 *  Applique les instructions de la commande aux 4 moteurs
 */ 
void Quadri::Applique_commande(){
  moteur_1.Applique_puissance_m();
  moteur_2.Applique_puissance_m();
  moteur_3.Applique_puissance_m();
  moteur_4.Applique_puissance_m();
}


