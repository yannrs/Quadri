#ifndef CLASS_H_
#define CLASS_H_  
                                               // Uniquement le nom des fonctions
#include "Arduino.h"
#include "Pins.h"

class Moteur{
  
  public:
  
  Moteur(int pin, int offset);
  int get_pin();
  int get_offset();
  int get_puissance_m();
  void set_puissance_m(int);
  
  
  private:
  
  int pin;
  int offset;
  int puissance_m;
  
};



class Quadri{
  
  public: 
  Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4);
  Moteur get_moteur(int i);
  
  private :
  Moteur moteur_1;
  Moteur moteur_2;
  Moteur moteur_3;
  Moteur moteur_4;
};

class Controle{
  
  public :
  
  Controle();
  Controle(float w_x, float w_y, float w_z, float puissance);
  void Direction_commande_actualise();
  void Instruction_moteurs(Controle &v_precedent, Quadri &quad);
  void Copie(Controle &v);
  void Copie(float w_x, float w_y, float w_z, float puissance);
  
  //Acces
  float get_w_x();
  float get_w_y();
  float get_w_z();
  float get_puissance();
  
  
  private:
  
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ;  // [0,100]
  
  
};






#endif /*  Class  */
