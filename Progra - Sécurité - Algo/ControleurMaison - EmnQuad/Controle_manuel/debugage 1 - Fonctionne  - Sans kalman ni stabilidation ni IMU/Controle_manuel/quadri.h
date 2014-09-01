#ifndef QUADRI_H_
#define QUADRI_H_  

#include "moteur.h"
/**************************************************
 *                 Class Quadri
 **************************************************/
class Quadri{
public: 
  Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4);
  Moteur* get_moteur(int i);
  void Applique_commande();

private :
  Moteur moteur_1;
  Moteur moteur_2;
  Moteur moteur_3;
  Moteur moteur_4;
};


#endif /*  Class  */
