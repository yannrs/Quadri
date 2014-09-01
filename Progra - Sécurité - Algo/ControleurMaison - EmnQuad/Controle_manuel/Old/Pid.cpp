#include "Pid.h"


/**************************************************
 *                 Class Pid
 **************************************************/
 
 // Sauvegarde des erreurs
 
//---------------- Constructeur -------------------//

Pid::Pid(float K_P, float K_I, float K_D){  
  K_P = K_P;
  K_I = K_I;
  K_D = K_D;
  erreur_P=0;
  erreur_I=0;
  erreur_D=0;
  t_prec = millis() * 0.001;  
}

Pid::Pid(){
  Pid(5,0.1,0.1);  
}


//------------------ Getters ---------------------//
float Pid::get_erreur_P(){
  return erreur_P;  
}

float Pid::get_erreur_I(){
  return erreur_P;  
}

float Pid::get_erreur_D(){
  return erreur_P;  
}

float Pid::get_dt(float t_actuel){
  float dt = t_actuel-t_prec; 
  set_t();
  return dt;  
}

float Pid::get_dt(){
  float dt = millis()*0.001-t_prec; 
  set_t();
  return dt;  
}

//------------------ Setters ---------------------//
void Pid::set_erreur_P(float p){
  erreur_P=p;
};

void Pid::set_erreur_I(float i){
  erreur_I=i;
};

void Pid::set_erreur_D(float d){
  erreur_D=d;
};

void Pid::set_t(){
  t_prec = millis()*0.001;
}


//------------------ Methodes ---------------------//

void Pid::reset(){
  erreur_P=0;
  erreur_I=0;
  erreur_D=0;
  t_prec = millis() * 0.001; 
}




