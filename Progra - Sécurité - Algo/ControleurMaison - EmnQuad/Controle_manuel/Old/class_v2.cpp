/**
 * Fichier classes, contenant l'implementation des classes
 * Version 2 Avril 2014
 **/
#include "Arduino.h"
#include "class_v2.h"
#include "Pins.h"                                            

/**************************************************
 *                 Class Moteur
 **************************************************/
//---------------- Constructeur -------------------//
Moteur::Moteur(int pin1, int offset1){
  pin = pin1;
  offset = offset1;
  puissance2_m = 150;
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

/**************************************************
 *                 Class Controle
 **************************************************/
 
//---------------- Constructeur -------------------//
Controle::Controle(){
  w_x=0;
  w_y=0;
  w_z=0;
  puissance=120;
}

Controle::Controle(float w_x1, float w_y1, float w_z1, float puissance1){
  set_w_x(w_x1);
  set_w_y(w_y1);
  set_w_z(w_z1);
  set_puissance(puissance1);
}

//------------------ Getters ---------------------//
float Controle::get_w_x(){
  return w_x;
}
float Controle::get_w_y(){
  return w_y;
}
float Controle::get_w_z(){
  return w_z;
}
float Controle::get_puissance(){
  return puissance;
}

//------------------ Setters ---------------------//
void Controle::set_w_x(float w_xe){
  if( w_xe > -Pi && w_xe < Pi){
     w_x = w_xe; 
  }
}
void Controle::set_w_y(float w_ye){
  if( w_ye > -Pi && w_ye < Pi){
     w_y = w_ye; 
  }
}
void Controle::set_w_z(float w_ze){
  if( w_ze > -Pi && w_ze < Pi){
     w_z = w_ze; 
  }
}
void Controle::set_puissance(float puissance_e){
  if( puissance_e > 0 && puissance_e < 100){
     puissance = puissance_e; 
  }
}

//------------------ Methods ---------------------//

/**
 * Initialisation du système:
 * Objectif : Les moteurs ne peuvent tourner que si les commandes ont été pendant 1 sec aux max, puis 1 sec aux min
 */ 
void Controle::Initialisation(){
  
  float  Throttle = pulseIn(Pin_Throttle, HIGH,25000); // Valeur comprise entre 800 et 2000 ramené à [0,100]
  // Donne un angle suivant chaques axes [| 800 ; 2000 |] ramené à [|-PI;PI|]
  float  Roll = pulseIn(Pin_Roll, HIGH,25000); 
  float  Pitch = pulseIn(Pin_Pitch, HIGH,25000);
  float  Yaw = pulseIn(Pin_Yaw, HIGH,25000);
  
  float t = millis();
  float t_prec = t;
  
  float Throttle_max=Throttle;
  float Roll_max=Roll;
  float Pitch_max=Pitch;
  float Yaw_max=Yaw;
 
 // Phase : les commandes sont au max 
  while (t-t_prec < 1000 && (Throttle <= Throttle_max - 10 || Roll <= Roll_max - 10 || Pitch <= Pitch_max - 10 || Yaw >= Yaw_max - 10)){
   t = millis();
   float  Throttle = pulseIn(Pin_Throttle, HIGH,25000);
   float  Roll = pulseIn(Pin_Roll, HIGH,25000); 
   float  Pitch = pulseIn(Pin_Pitch, HIGH,25000);
   float  Yaw = pulseIn(Pin_Yaw, HIGH,25000);
     
     if(Throttle_max <= Throttle){
         Throttle_max=Throttle;
     }
         
     if(Yaw_max <= Yaw){
         Yaw_max=Yaw;
     }
       
     if(Roll_max <= Roll){
         Roll_max=Roll;
     }
     
     if(Pitch_max <= Pitch){
         Pitch_max=Pitch;
     }
  }
  
  t_prec = t;
  float Throttle_min=Throttle;
  float Roll_min=Roll;
  float Pitch_min=Pitch;
  float Yaw_min=Yaw;
  
 // Phase : les moteurs sont au min 
 while (t-t_prec < 1000 && (Throttle >= Throttle_min - 10 || Roll >= Roll_min - 10 || Pitch >= Pitch_min - 10 || Yaw >= Yaw_min - 10)){
   t = millis();
   float  Throttle = pulseIn(Pin_Throttle, HIGH,25000);
   float  Roll = pulseIn(Pin_Roll, HIGH,25000); 
   float  Pitch = pulseIn(Pin_Pitch, HIGH,25000);
   float  Yaw = pulseIn(Pin_Yaw, HIGH,25000);
     
     if(Throttle_min >= Throttle){
         Throttle_min=Throttle;
     }
         
     if(Yaw_min >= Yaw){
         Yaw_min=Yaw;
     }
       
     if(Roll_min >= Roll){
         Roll_min=Roll;
     }
     
     if(Pitch_min >= Pitch){
         Pitch_max=Pitch;
     }
  }
  
}


/**
 * Récupère les instruction de la RC
 */
void Controle::Direction_commande_actualise(){

  float  Throttle = (pulseIn(Pin_Throttle, HIGH,25000) - Min_Throttle)*100/Max_Throttle; // Valeur comprise entre 800 et 2000 ramené à [0,100]
  // Donne un angle suivant chaques axes [| 800 ; 2000 |] ramené à [|-PI;PI|]
  float  Roll = (pulseIn(Pin_Roll, HIGH,25000) - Med_Roll)*Pi/Max_Roll; 
  float  Pitch = (pulseIn(Pin_Pitch, HIGH,25000) - Med_Pitch)*Pi/Max_Pitch;
  float  Yaw = (pulseIn(Pin_Yaw, HIGH,25000) - Med_Yaw)*Pi/Max_Yaw;
  
  #ifdef Debug
    Serial.println("Instruction de la télecommande (ramené entre [|-PI;PI|] )");
    Serial.println("Roll");
    Serial.println(Roll);
    Serial.println("Pitch");
    Serial.println(Pitch);
    Serial.println("Yaw");
    Serial.println(Yaw);
    Serial.println("Puissance");
    Serial.println(Throttle);
  #endif
  
  set_w_x(Pitch);
  set_w_y(Roll);
  set_w_z(Yaw);
  set_puissance(Throttle);
}


/**
 * Controle les moteurs
 */
void Controle::Instruction_moteurs(Controle &v_precedent, Quadri &quad){
  
  // Quelques Limites
  // Cas forte diminution
  if( v_precedent.get_puissance() - get_puissance() >10){
    set_puissance(get_puissance() - 5);
  }
  // Cas forte augmentation
  if( get_puissance() - v_precedent.get_puissance() >10){
    set_puissance(puissance + 5);
  }
  //On bride les moteurs globalement
  if(get_puissance() > Max_Puissance){
   set_puissance(Max_Puissance) ; 
  }
 
  /* Positionnement des moteurs
        z                        4
        |                       /
        |                      /
        |              1 --------- 2
        -------  y          / 
      /                    /  
     /                    3
    x
  */
  
 /*
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ; // [0,100]
*/   
  float pas_par_radian = 20/Pi; // A modifier, quantifie la réactivitée du quad !
  
  // on suppose que 1 et 3 tournent dans le sens antihoraire
  // On associe a chaques moteurs une puissance nominal que l'on va faire varier en fonction des parametres de rotation
  //                            Puissance nominale                        Offesets                                     Orientation du quad
  int puissance_moteur_1 =Demarrage_Moteur + get_puissance() + (*quad.get_moteur(1)).get_offset() - w_x*pas_par_radian                        +  w_z*pas_par_radian;
  int puissance_moteur_2 =Demarrage_Moteur + get_puissance() + (*quad.get_moteur(2)).get_offset() + w_x*pas_par_radian                        +  w_z*pas_par_radian;
  int puissance_moteur_3 =Demarrage_Moteur + get_puissance() + (*quad.get_moteur(3)).get_offset() -                       w_y*pas_par_radian  -  w_z*pas_par_radian;
  int puissance_moteur_4 =Demarrage_Moteur + get_puissance() + (*quad.get_moteur(4)).get_offset() +                       w_y*pas_par_radian  -  w_z*pas_par_radian;
  
  // Associe les puissances à chaques moteurs
  (*quad.get_moteur(1)).set_puissance_m(puissance_moteur_1);
  (*quad.get_moteur(2)).set_puissance_m(puissance_moteur_2);
  (*quad.get_moteur(3)).set_puissance_m(puissance_moteur_3);
  (*quad.get_moteur(4)).set_puissance_m(puissance_moteur_4);
 
  #ifdef Debug1
    Serial.println("Puissance_moteur");
    Serial.println(puissance_moteur_1);
    Serial.println(puissance_moteur_2);
    Serial.println(puissance_moteur_3);
    Serial.println(puissance_moteur_4);
  #endif
  
  #ifdef Debug
    Serial.println("Instruction telecommande");
    Serial.println("w_x");
    Serial.println(w_x);
    Serial.println("w_y");
    Serial.println(w_y);
    Serial.println("w_z");
    Serial.println(w_z);
    Serial.println("Puissance");
    Serial.println(puissance);
  #endif
  //Le demarrage des moteurs commencent vers 150 sur 255 donc on travail sur une plage de 100. (avec un offset)
  // Sauvegarde des valeurs précedentes
  v_precedent.Copie(w_x , w_y , w_z , get_puissance());
  
  //Sortie
  analogWrite((*quad.get_moteur(1)).get_pin(), (*quad.get_moteur(1)).get_puissance_m());
  analogWrite((*quad.get_moteur(2)).get_pin(), (*quad.get_moteur(2)).get_puissance_m());
  analogWrite((*quad.get_moteur(3)).get_pin(), (*quad.get_moteur(3)).get_puissance_m());
  analogWrite((*quad.get_moteur(4)).get_pin(), (*quad.get_moteur(4)).get_puissance_m());   
}

/**
 * 
 */
void Controle::Copie(float w_x1, float w_y1, float w_z1, float puissance1){
  set_w_x(w_x1);
  set_w_y(w_y1);
  set_w_z(w_z1);
  set_puissance(puissance1);
}

/**
 * 
 */
void Controle::Copie(Controle &c){
  set_w_x(c.get_w_x());
  set_w_y(c.get_w_y());
  set_w_z(c.get_w_z());
  set_puissance(c.get_puissance());
}
