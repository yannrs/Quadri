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

// Valeurs Expérimentatles (min, max, moy)  des pins
#define Min_ThrottleExp   1126 //945 - Modif 22-04-2014
#define Max_ThrottleExp   1856 //1690 - Modif 22-04-2014
#define Min_RollExp       1104 //1070 - Modif 22-04-2014
#define Max_RollExp       1821 //1915  - Modif 22-04-2014
#define Med_RollExp       1480 // Médiane
#define Min_PitchExp      1030 //1145 - Modif 22-04-2014
#define Max_PitchExp      1942 //1890 - Modif 22-04-2014
#define Med_PitchExp      1525 // Médiane
#define Min_YawExp        1024 //1060 - Modif 22-04-2014
#define Max_YawExp        1936 //1920 
#define Med_YawExp        1485 // Médiane

// Pin moteurs
#define Pin_Moteur_1  9 // Associé avec le 9
#define Pin_Moteur_2  10 // Associé avec le 3
#define Pin_Moteur_3  3 // Associé avec le 11
#define Pin_Moteur_4  11 // Associé avec le 10

// Autres constantes
#define Pi 3.14159265359
#define Demarrage_Moteur 140 // Point à partir duquel les moteurs commencent à trouner
#define Max_Puissance 180

#define Debug 0 // Activer (0) / désactiver(1) le débeugage 
#define Debug1 0 // Activer (0) / désactiver(1) le débeugage avancé

#endif /*  PINS_H  */
