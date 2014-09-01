#ifndef VARIABLES_H_
#define VARIABLES_H_ 

 
/*************************************************/
/*                   Variables                   */
/*************************************************/

const int LedPin = 8;   // Visualisation des stades dans le programme

//offset Moteurs obtenu grâce aux tests
/*int offset_moteur_1 = -14;
int offset_moteur_2 = 1;
int offset_moteur_3 = 1;
int offset_moteur_4 = 30;*/
//test - Cause demarrage de moteur incompris
int offset_moteur_1 = 0;
 int offset_moteur_2 = 0;
 int offset_moteur_3 = 0;
 int offset_moteur_4 = 0;


/* Used for timing */
unsigned long timer;

#define STD_LOOP_TIME 10000 // Fixed time loop of 10 milliseconds
unsigned long lastLoopUsefulTime = STD_LOOP_TIME;
unsigned long loopStartTime;


/*Utilisation des objets*/
Telecommande telecommande;
Controle v_courant , v_precedent;
Quadri quad(Pin_Moteur_1,offset_moteur_1,Pin_Moteur_2,offset_moteur_2,Pin_Moteur_3,offset_moteur_3,Pin_Moteur_4,offset_moteur_4);


#endif
