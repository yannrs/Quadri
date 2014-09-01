#ifndef INSTRUCTION_COMMANDE_V2_H_
#define INSTRUCTION_COMMANDE_V2_H_   // Uniquement le nom des fonctions


typedef struct Vecteur_ {
  float w_x ; // [|-PI;PI|]
  float w_y ; // [|-PI;PI|]
  float w_z ; // [|-PI;PI|]
  float puissance ; // [0,100]
} Vecteur;



void Direction_commande(Vecteurs v);


#endif /*  INSTRUCTION_COMMANDE_V2_H_  */
