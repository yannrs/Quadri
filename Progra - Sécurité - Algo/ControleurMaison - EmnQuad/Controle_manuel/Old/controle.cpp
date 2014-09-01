#include "controle.h"



/**************************************************
 *                 Class Controle
 **************************************************/

//---------------- Constructeur -------------------//
Controle::Controle( ){
  w_x=0;
  w_y=0;
  w_z=0;
  puissance=120;
//  telecommande = telecommande;
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
 * Récupère les instruction de la RC
 */
void Controle::Direction_commande_actualise(Telecommande t){
  float  Throttle = (pulseIn(Pin_Throttle, HIGH,25000) - t.getThrottle_min())*100/t.getThrottle_max(); // Valeur comprise entre 800 et 2000 ramené à [0,100]
  // Donne un angle suivant chaques axes [| 800 ; 2000 |] ramené à [|-PI;PI|]
  float  Roll = (pulseIn(Pin_Roll, HIGH,25000) - t.getRoll_med())*Pi/t.getRoll_max(); 
  float  Pitch = (pulseIn(Pin_Pitch, HIGH,25000) - t.getPitch_med())*Pi/t.getPitch_max();
  float  Yaw = (pulseIn(Pin_Yaw, HIGH,25000) - t.getYaw_med())*Pi/t.getYaw_max();

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
void Controle::Conversion_en_Instruction_moteurs(Controle &v_precedent, Quadri &quad){

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
       z                          4
       |                         /
       |                        /
       |                1 --------- 2
         -------  y          / 
      /                     /  
     /                     3
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
  Serial.println("Instruction Telecommande");
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

  /* // Déplacé directement dans les objets moteurs et quadri
  //Sortie
  analogWrite((*quad.get_moteur(1)).get_pin(), (*quad.get_moteur(1)).get_puissance_m());
  analogWrite((*quad.get_moteur(2)).get_pin(), (*quad.get_moteur(2)).get_puissance_m());
  analogWrite((*quad.get_moteur(3)).get_pin(), (*quad.get_moteur(3)).get_puissance_m());
  analogWrite((*quad.get_moteur(4)).get_pin(), (*quad.get_moteur(4)).get_puissance_m());   */
}


/**
 * Copie profonde d'un objet controle
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


