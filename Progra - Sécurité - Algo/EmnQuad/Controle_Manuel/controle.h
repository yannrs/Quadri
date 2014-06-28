#ifndef CONTROLE_H_
#define CONTROLE_H_ 

#include "Arduino.h"
#include "Pins.h"
#include "moteur.h"
#include "quadri.h"
#include "telecommande.h"
/**************************************************
 *                 Class Controle
 **************************************************/
class Controle{
public :
  Controle();
  Controle(float w_x, float w_y, float w_z, float puissance);
  void Direction_commande_actualise(Telecommande t);
  void Conversion_en_Instruction_moteurs(Controle &v_precedent, Quadri &quad);
  void Copie(Controle &v);
  void Copie(float w_x, float w_y, float w_z, float puissance);


  // Acces
  float get_w_x();
  float get_w_y();
  float get_w_z();
  float get_puissance();
 
  // Modification
  void set_w_x(float w_xe);
  void set_w_y(float w_xe);
  void set_w_z(float w_xe);
  void set_puissance(float puissance_e);


private:
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ;  // [0,100]
 
};

#endif
