#ifndef VARIABLES_H_
#define VARIABLES_H_ 


/*************************************************/
/*                   Librairies                  */
/*************************************************/
#include "Pins.h"
#include "controle.h" // Utilise la Télécommande pour asservir le quad
#include "moteur.h" // Contient toutes les infos sur 1 moteur
#include "quadri.h" // Contient toutes les infos sur 1 quadricoptère
#include "telecommande.h" // Contient les paramétres de la télécommande (Min, max...)
#include "Pid.h";
#include "Kalman.h" // Kalman filter library see: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
#include "Stabilisation.h";

//#include "Wire.h"

/*************************************************/
/*        Librairies - Centre à Inertie          */
/*************************************************/
#include "ADXL345.h"; // Accéleromètre 3 axes
#include "L3G4200D.h"; // Gyroscope 3 axes
 
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


// Pour le Gyroscope
//int L3G4200D_Address = 105; //I2C address of the L3G4200D
int X_gyro;
int Y_gyro;
int Z_gyro;

ADXL345 acc; // Accéléromètre
//L3G4200D gyro; // Gyroscope
#endif
