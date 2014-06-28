#ifndef PID_H_
#define PID_H_  

#include "Arduino.h"
/**************************************************
 *                 Class Quadri
 **************************************************/
class Pid{
public : 
  Pid();
  Pid(float K_P, float K_I, float K_D);
  float get_erreur_P();
  float get_erreur_I();
  float get_erreur_D();
  float get_dt(float t_actuel);
  float get_dt();
  
  void set_erreur_P(float p);
  void set_erreur_I(float i);
  void set_erreur_D(float d);
  void set_t();
  
  void reset();

private :
  float erreur_P;
  float erreur_I;
  float erreur_D;
  
  float K_P;
  float K_I;
  float K_D;
  
  float t_prec;// en s
};


#endif /*  Class  */
