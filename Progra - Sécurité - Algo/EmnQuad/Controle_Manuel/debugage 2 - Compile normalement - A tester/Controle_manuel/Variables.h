#ifndef VARIABLES_H_
#define VARIABLES_H_ 


 
/*************************************************/
/*                   Variables                   */
/*************************************************/

const int LedPin = 8;   // Visualisation des stades dans le programme

//offset Moteurs obtenu grâce aux tests
int offset_moteur_1 = -14;
int offset_moteur_2 = 1;
int offset_moteur_3 = 1;
int offset_moteur_4 = 30;
//test - Cause demarrage de moteur incompris
/*int offset_moteur_1 = 0;
 int offset_moteur_2 = 0;
 int offset_moteur_3 = 0;
 int offset_moteur_4 = 0;*/


/* Used for timing */
unsigned long timer;

#define STD_LOOP_TIME 10000 // Fixed time loop of 10 milliseconds
unsigned long lastLoopUsefulTime = STD_LOOP_TIME;
unsigned long loopStartTime;


/*Utilisation des objets*/
Telecommande telecommande;
Controle v_courant , v_precedent;
Quadri quad(Pin_Moteur_1,offset_moteur_1,Pin_Moteur_2,offset_moteur_2,Pin_Moteur_3,offset_moteur_3,Pin_Moteur_4,offset_moteur_4);
Kalman kalmanX, kalmanY; // Pour les angles entre X et Z et pour celui entre Y et Z




int Xg, Yg, Zg;
//ADXL345 acc; // Accéléromètre - ici, ASDXL345 n'est pas reconnu...

// Pour le Gyroscope
//int L3G4200D_Address = 105; //I2C address of the L3G4200D
int X_gyro;
int Y_gyro;
int Z_gyro;


//L3G4200D gyro; // Gyroscope


#endif
