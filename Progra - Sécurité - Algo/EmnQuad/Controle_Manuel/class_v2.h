/**
 * Fichier headers, contenant les declarations des classes (signature des méthodes et les attributs)
 * Version 2 Avril 2014
 **/
#ifndef CLASS_H_
#define CLASS_H_  
#include "Arduino.h"
#include "Pins.h"
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
    
  private:
    int pin;
    int offset;
    int puissance2_m;
};


/**************************************************
 *                 Class Quadri
 **************************************************/
class Quadri{
  public: 
    Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4);
    Moteur* get_moteur(int i);
    
  private :
    Moteur moteur_1;
    Moteur moteur_2;
    Moteur moteur_3;
    Moteur moteur_4;
};


/**************************************************
 *                 Class Controle
 **************************************************/
class Controle{
  public :
    Controle();
    Controle(float w_x, float w_y, float w_z, float puissance);
    void Direction_commande_actualise();
    void Instruction_moteurs(Controle &v_precedent, Quadri &quad);
    void Copie(Controle &v);
    void Copie(float w_x, float w_y, float w_z, float puissance);
    void Initialisation();
  
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

/*
class telecommande{
  public:
  telecommande();
  void Initialisation();
  float getThrottle_max();
  float getRoll_max();
  float getPitch_max();
  float getYaw_max();
  
  float getThrottle_min();
  float getRoll_min();
  float getPitch_min();
  float getYaw_min();
  
  private:  
  float Throttle_max;
  float Roll_max;
  float Pitch_max;
  float Yaw_max;
  
  float Throttle_min;
  float Roll_min;
  float Pitch_min;
  float Yaw_min;
  
  
};
*/


#endif /*  Class  */
