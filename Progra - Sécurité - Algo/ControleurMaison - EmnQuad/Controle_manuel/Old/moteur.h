#ifndef MOTEUR_H_
#define MOTEUR_H_  

#include "Arduino.h"
/**************************************************
 *                 Class Moteur
 **************************************************/
class Moteur{
public:
  Moteur(int pin, int offset);
  int get_pin();
  int get_offset();
  int get_puissance_m();
  void set_puissance_m(int);
  void Applique_puissance_m();

private:
  int pin;
  int offset;
  int puissance2_m;
};

#endif 
