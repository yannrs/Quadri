#include "Arduino.h"
//#include "Controle_variateur.ino"
#include "Instruction_commande_v2.h"


// Entrée : 3 angles + puissance = vecteur
// Sortie : 4 signaux entre 0 et 255


/*
int Pin_Moteur_1 = 3 ;// Associé avec le 9
int Pin_Moteur_2 = 9 ;// Associé avec le 3
int Pin_Moteur_3 = 11 ;// Associé avec le 11
int Pin_Moteur_4 = 10 ;// Associé avec le 10*/

int offset_moteur_1 = 2;
int offset_moteur_2 = -14;
int offset_moteur_3 = 1;
int offset_moteur_4 = 30;

Vecteur v_precedent = { 0, 0 , 0, 150 };

float pas_par_radian = 20/Pi;


void instruction_moteurs(Vecteur v){
    
    // Debut d'un Régulateur
    if( v_precedent.puissance - v.puissance >10){
      v.puissance=v.puissance - 5;
    }
    if( v.puissance - v_precedent.puissance >10){
      v.puissance=v.puissance + 5;
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
struct Vecteur {
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ; // [0,100]
};*/   

  // on suppose que 1 et 3 tournent dans le sens antihoraire
    // On associe a chaques moteurs une puissance nominal que l'on va faire varier en fonction des parametres de rotation
    int puissance_moteur_1 = v.puissance + offset_moteur_1 - v.w_x*pas_par_radian                        -  v.w_z*pas_par_radian;
    int puissance_moteur_2 = v.puissance + offset_moteur_2 +                       v.w_y*pas_par_radian  +  v.w_z*pas_par_radian;
    int puissance_moteur_3 = v.puissance + offset_moteur_3 + v.w_x*pas_par_radian                        -  v.w_z*pas_par_radian;
    int puissance_moteur_4 = v.puissance + offset_moteur_4 -                       v.w_y*pas_par_radian  +  v.w_z*pas_par_radian;
    
    
    //Le demarrage des moteurs commencent vers 150 sur 255 donc on travail sur une plage de 100. (avec un offset)
    
    
    
    // Sauvegarde des valeurs précedentes
    v_precedent = v;
    //Sortie
    analogWrite(Pin_Moteur_1, puissance_moteur_1);
    analogWrite(Pin_Moteur_2, puissance_moteur_2);
    analogWrite(Pin_Moteur_3, puissance_moteur_3);
    analogWrite(Pin_Moteur_4, puissance_moteur_4);
    //analogWrite(Pin_Moteur_1, 2);
    
    
}

