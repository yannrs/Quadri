#include "Arduino.h"
#include "Instruction_moteurs.h"

// Implementation de chaques fonctions


/*
const int Pin_Throttle  = 2 ;// Accelerateur - Norme du vecteur
const int Pin_Roll      = 4 ;// Roulis - Rotation autour de l'axe Y
const int Pin_Pitch     = 5 ;// Tangage / Angle d'attaque - Rotation autour de l'axe X
const int Pin_Yaw       = 6 ;// Lacet - Rotation autour de l'axe Z
*/

/*
typedef struct Vecteur_ {
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ; // [0,100]
} Vecteur;*/
//float Pi = 3.14159;

//Vecteur v = { 0, 0 , 0, 155 };  



void Direction_commande(Vecteur v){
  
  float  Throttle = digitalRead(Pin_Throttle)*100/255; // Valeur comprise entre 0 et 255 ramené à [0,100]
  
  // Donne un angle suivant chaques axes [| 0 ; 255 |] ramené à [|-PI;PI|]
  float  Roll = (digitalRead(Pin_Roll)-126)*2*Pi/255; 
  float  Pitch = (digitalRead(Pin_Pitch)-126)*2*Pi/255; 
  float  Yaw = (digitalRead(Pin_Yaw)-126)*2*Pi/255;
  
  //Vecteur v = { w_x , w_y  , w_z , v};
  v = { Pitch , Roll , Yaw , Throttle };
  
  //return v;
  
};


