
// --- Programme Arduino ---


        // --- Que fait ce programme ? ---
            /* Teste des offsets*/

// --- Circuit à réaliser ---
// 

// --- Inclusion des librairies utilisées ---
// ...


// --- Déclaration des constantes ---
// ...

// --- constantes des broches ---
const int LedPin = 3;   

const int Commande_voie_1 = 2;
const int Commande_voie_2 = 4;
const int Commande_voie_3 = 5;
const int Commande_voie_4 = 6;


// --- Déclaration des variables globales ---
// ...

// --- Initialisation des fonctionnalités utilisées ---
// ...

//**************** FONCTION SETUP = Code d'initialisation *****
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

  void setup()   { // debut de la fonction setup()
      Serial.begin(115200);
          
      Serial.println("Debut initialisation");    
      // --- ici instructions à exécuter au démarrage ---
      //pinMode(Commande_voie_1, INPUT);
      /*pinMode(Commande_voie_2, INPUT);
      pinMode(Commande_voie_3, INPUT);
      pinMode(Commande_voie_4, INPUT);*/
      
      pinMode(LedPin, OUTPUT);  
      
      delay(5000);
      Serial.println("J'ai fini d'initialiser");

} // fin de la fonction setup()
// ********************************************************************************

//*************** FONCTION LOOP = Boucle sans fin = coeur du programme *************
// la fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension
  int buttonState = 0;
  
 // Vecteur v= { 0, 0 , 0, 155 };  
  void loop(){ // debut de la fonction loop()

    // --- ici instructions à exécuter par le programme principal ---
    
     Serial.println("Je fais un tour");
     
     digitalWrite(8,HIGH);
     delay(500);
     digitalWrite(8,LOW);
     
     
     // Arrêt moteur
    /* Serial.println("Lecture de la voie 1");
     Serial.println(" Temps à l'état Haut " );
     buttonState = pulseIn(Commande_voie_1, HIGH,25000);
     Serial.println(buttonState);
     Serial.println("Lecture de la voie 2");
     Serial.println(pulseIn(Commande_voie_2, HIGH,25000));
     Serial.println("Lecture de la voie 3");
     Serial.println(pulseIn(Commande_voie_3, HIGH,25000));
     Serial.println("Lecture de la voie 4");
     Serial.println(pulseIn(Commande_voie_4, HIGH,25000));*/
     
     //amplitude_commande(Commande_voie_1);
     //amplitude_commande(Commande_voie_2);
   //  amplitude_commande(Commande_voie_3);
     amplitude_commande(Commande_voie_4);
     
     
     
     delay(1000);
     
     

 } // fin de la fonction setup()
  // ********************************************************************************
  
 
  
void amplitude_commande( int voie){
   int mini = 5000000;
   int maxi = 0;
   int moyenne = 0;
   int courant = 0;

    for( int i = 0; i<5 ; i++){
      courant  = pulseIn(voie, HIGH,25000);
      
      mini = min(mini, courant);
      maxi = max( maxi, courant);
      moyenne += courant; 
    }
  
    moyenne = moyenne / 5;
    
    Serial.println(" Pour la voie");
    Serial.println(voie);
    Serial.println(" Min");
    Serial.println( mini);
    Serial.println(" Max");
    Serial.println(maxi);
    Serial.println(" Moyenne des 5 éléments");
    Serial.println(moyenne);
    delay(1000);    
  
 }
  
  
  // --- Fin programme ---

