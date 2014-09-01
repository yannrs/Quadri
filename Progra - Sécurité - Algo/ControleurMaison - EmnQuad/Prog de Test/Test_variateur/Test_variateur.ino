        // --- Que fait ce programme ? ---
/****************************************************************/
/*    Permet de trouver les éventuelles Offsets des variateurs  */
/****************************************************************/
    // PS : Pour les variateurs de M*** Chinois


// --- Déclaration des constantes ---
int pas = 1;

// --- constantes des broches ---
const int LedPin = 8;   

const int Variateur_1 = 9;
const int Variateur_2 = 10;
const int Variateur_3 = 3;
const int Variateur_4 = 11;


//**************** FONCTION SETUP = Code d'initialisation *****
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

  void setup()   { // debut de la fonction setup()
      Serial.begin(115200);          
      Serial.println("Debut initialisation");    
      
      // --- ici instructions à exécuter au démarrage ---
      pinMode(Variateur_1, OUTPUT);
      pinMode(Variateur_2, OUTPUT);
      pinMode(Variateur_3, OUTPUT);
      pinMode(Variateur_4, OUTPUT);
      
      pinMode(LedPin, OUTPUT);  
      
      //On test ici quand les moteurs s'initialisent
      /*for(int i=120; i< 140; i=i+2){
          analogWrite(Variateur_1, i);
          analogWrite(Variateur_2, i);
          analogWrite(Variateur_3, i);
          analogWrite(Variateur_4, i);
          Serial.println( i);
          delay(500);
      }*/
      delay(2000);
      
      // Initialisation des Moteurs/Variateurs
      analogWrite(Variateur_1, 127);
      analogWrite(Variateur_2, 127);
      analogWrite(Variateur_3, 127);
      analogWrite(Variateur_4, 127);
      delay(5000);
      Serial.println("J'ai fini d'initialiser");

} // fin de la fonction setup()
// ********************************************************************************

//*************** FONCTION LOOP = Boucle sans fin = coeur du programme *************
// la fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension
  int i =0 ;
  void loop(){ // debut de la fonction loop()
    
     Serial.println("Je fais un tour");
     digitalWrite(8,HIGH);
     delay(500);
     digitalWrite(8,LOW);
     
     
     i=0;
      while (i<12 )//&& buttonState == HIGH)
     {
 
            Serial.println(i);
            digitalWrite(8,HIGH);
            delay(500);
            digitalWrite(8,LOW);
            
            analogWrite(Variateur_1, 150 + 0 + i*1);
            analogWrite(Variateur_2, 150 + 0 + i*1);
            analogWrite(Variateur_3, 150 + 0 + i*1);
            analogWrite(Variateur_4, 150 + 0 + i*1);
            delay(1500);
            i=i+1;
            
     }
     // Arrêt moteur
     digitalWrite(Variateur_1, 127);
     digitalWrite(Variateur_2, 127);
     digitalWrite(Variateur_3, 127);
     digitalWrite(Variateur_4, 127);

 } // fin de la fonction setup()
  // ********************************************************************************
  
  // --- Fin programme ---
