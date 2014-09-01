/**
 * Fichier Pin, contenant les déclarations des constantes
 * Convention utilisé : #define Xxx_Xxx  (Première lettre d'un mot en majuscule, le reste en minuscule, si mot composé séparer par "_")
 * Version 2 Avril 2014
 **/
#ifndef PINS_H
#define PINS_H

// Pins
#define Pin_Throttle   2 // Accelerateur - Norme du vecteur
#define Pin_Roll       4 // Roulis - Rotation autour de l'axe Y
#define Pin_Pitch      5 // Tangage / Angle d'attaque - Rotation autour de l'axe X
#define Pin_Yaw        6 // Lacet - Rotation autour de l'axe Z

// Valeurs (min, max, moy)  des pins
#define Min_Throttle   945 
#define Max_Throttle   1690 
#define Min_Roll       1070 
#define Max_Roll       1915 
#define Med_Roll       1480 // Médiane
#define Min_Pitch      1145 
#define Max_Pitch      1890 
#define Med_Pitch      1525 // Médiane
#define Min_Yaw        1060 
#define Max_Yaw        1920 
#define Med_Yaw        1485 // Médiane

// Pin moteurs
#define Pin_Moteur_1  9 // Associé avec le 9
#define Pin_Moteur_2  10 // Associé avec le 3
#define Pin_Moteur_3  3 // Associé avec le 11
#define Pin_Moteur_4  11 // Associé avec le 10

// Autres constantes
#define Pi 3.14159265359
#define Demarrage_Moteur 140 // Point à partir duquel les moteurs commencent à trouner
#define Max_Puissance 100

#define Debug 0 // Activer (0) / désactiver(1) le débeugage 
#define Debug1 0 // Activer (0) / désactiver(1) le débeugage avancé

#endif /*  PINS_H  */
