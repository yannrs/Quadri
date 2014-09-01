#include "Arduino.h"
#include "class.h"
#include "Pins.h"
                                                                // Implementation de chaques fonctions
                                                                
                                                   
                                                                
                                // Moteur  
  
//Constructeur
Moteur::Moteur(int pin1, int offset1){
  pin = pin1;
  offset = offset1;
  puissance_m = 100;
}
 
int Moteur::get_pin(){
  return pin;
}
int Moteur::get_offset(){
  return offset;
}

int Moteur::get_puissance_m(){
  return puissance_m;
}

void Moteur::set_puissance_m(int puis){
  if(puis < 160){  // permet d'éviter d'aller trop vite pour les testes.  A enlever après la phase de teste
    puissance_m=puis;
  }  
}
  
  
  
                                // Quadri
  
// Constructeur
/*Quadri::Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4){
  moteur_1( pin1, off1);
  moteur_2( pin2, off2);
  moteur_3( pin3, off3);
  moteur_4( pin4, off4);
}*/
Quadri::Quadri(int pin1, int off1, int pin2, int off2, int pin3, int off3, int pin4, int off4) :  moteur_1( pin1, off1),  moteur_2( pin2, off2) ,  moteur_3( pin3, off3),  moteur_4( pin4, off4)
{
}  
  
  
Moteur Quadri::get_moteur(int i){
  switch(i){
    case 1:
        return moteur_1;
        break;
    case 2:
        return moteur_2;
        break;
    case 3:
        return moteur_3;
        break;
    default: // cas i = 4
        return moteur_4;
        break;
  }
}  
                                                                
                                                                
                                                                
                                                                
                                      //Controle

//Constructeur
Controle::Controle(){
  w_x=0;
  w_y=0;
  w_z=0;
  puissance=120;
}  


Controle::Controle(float w_x1, float w_y1, float w_z1, float puissance1){
  w_x=w_x1;
  w_y=w_y1;
  w_z=w_z1;
  puissance=puissance1;
}

//Methodes
void Controle::Direction_commande_actualise(){
      float  Throttle = pulseIn(Pin_Throttle, HIGH,25000);//*100/255; // Valeur comprise entre 0 et 255 ramené à [0,100]
  
  // Donne un angle suivant chaques axes [| 0 ; 255 |] ramené à [|-PI;PI|]
     /* float  Roll = (pulseIn(Pin_Roll, HIGH,25000)-126)*2*Pi/255; 
      float  Pitch = (pulseIn(Pin_Pitch, HIGH,25000)-126)*2*Pi/255; 
      float  Yaw = (pulseIn(Pin_Yaw, HIGH,25000)-126)*2*Pi/255;*/
      float  Roll = (pulseIn(Pin_Roll, HIGH,25000)); 
      float  Pitch = (pulseIn(Pin_Pitch, HIGH,25000)); 
      float  Yaw = (pulseIn(Pin_Yaw, HIGH,25000));
  
      Serial.println("Instruction de la télecommande");
      Serial.println("Roll");
      Serial.println(Roll);
      Serial.println("Pitch");
      Serial.println(Pitch);
      Serial.println("Yaw");
      Serial.println(Yaw);
      Serial.println("Puissance");
      Serial.println(Throttle);
  
      w_x=Pitch;
      w_y=Roll;
      w_z=Yaw;
      puissance=Throttle;
}
  
  
void Controle::Instruction_moteurs(Controle &v_precedent, Quadri &quad){
  
    // Debut d'un Régulateur
    
    if( v_precedent.get_puissance() - puissance >10){
      puissance=puissance - 5;
    }
    if( puissance - v_precedent.get_puissance() >10){
      puissance=puissance + 5;
    }
    
    //On bride les moteurs 
    if(puissance > 160){
     puissance = 160; 
    }
    // Les moteurs ne tournent pas en sens inverse
    if(puissance <100){
      puissance = 100;
    }
    
  /* Positionnement des moteurs
        z                        2
        |                       /
        |                      /
        |              1 --------- 3
        -------  y          / 
      /                    /  
     /                    4 
    x
  */
  
 /*
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ; // [0,100]
*/   
    float pas_par_radian = 10/Pi;
    
  // on suppose que 1 et 3 tournent dans le sens antihoraire
    // On associe a chaques moteurs une puissance nominal que l'on va faire varier en fonction des parametres de rotation
    int puissance_moteur_1 = puissance + quad.get_moteur(1).get_offset() - w_x*pas_par_radian                        -  w_z*pas_par_radian;
    int puissance_moteur_2 = puissance + quad.get_moteur(2).get_offset() +                       w_y*pas_par_radian  +  w_z*pas_par_radian;
    int puissance_moteur_3 = puissance + quad.get_moteur(3).get_offset() + w_x*pas_par_radian                        -  w_z*pas_par_radian;
    int puissance_moteur_4 = puissance + quad.get_moteur(4).get_offset() -                       w_y*pas_par_radian  +  w_z*pas_par_radian;
    
    // Associe les puissances à chaques moteurs
    quad.get_moteur(1).set_puissance_m(puissance_moteur_1);
    quad.get_moteur(2).set_puissance_m(puissance_moteur_2);
    quad.get_moteur(3).set_puissance_m(puissance_moteur_3);
    quad.get_moteur(4).set_puissance_m(puissance_moteur_4);
    
   /* Serial.println("Puissance_moteur");
    Serial.println(puissance_moteur_1);
    Serial.println(puissance_moteur_2);
    Serial.println(puissance_moteur_3);
    Serial.println(puissance_moteur_4);
    Serial.println("Instruction telecommande");
    Serial.println("w_x");
    Serial.println(w_x);
    Serial.println("w_y");
    Serial.println(w_y);
    Serial.println("w_z");
    Serial.println(w_z);
    Serial.println("Puissance");
    Serial.println(puissance);*/
    
    //Le demarrage des moteurs commencent vers 150 sur 255 donc on travail sur une plage de 100. (avec un offset)
    
    // Sauvegarde des valeurs précedentes
    v_precedent.Copie(w_x , w_y , w_z , puissance);
    
    //Sortie
    /*analogWrite(Pin_Moteur_1, puissance_moteur_1);
    analogWrite(Pin_Moteur_2, puissance_moteur_2);
    analogWrite(Pin_Moteur_3, puissance_moteur_3);
    analogWrite(Pin_Moteur_4, puissance_moteur_4);*/
    //nouvelle version
    analogWrite(Pin_Moteur_1, quad.get_moteur(1).get_puissance_m());
    analogWrite(Pin_Moteur_2, quad.get_moteur(2).get_puissance_m());
    analogWrite(Pin_Moteur_3, quad.get_moteur(3).get_puissance_m());
    analogWrite(Pin_Moteur_4, quad.get_moteur(4).get_puissance_m());
    
    //analogWrite(Pin_Moteur_1, 2);
    
}

void Controle::Copie(float w_x1, float w_y1, float w_z1, float puissance1){
  w_x=w_x1;
  w_y=w_y1;
  w_z=w_z1;
  puissance=puissance1;
}


void Controle::Copie(Controle &c){
  w_x=c.get_w_x();
  w_y=c.get_w_y();
  w_z=c.get_w_z();
  puissance=c.get_puissance();
}

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



  
  
   
  
