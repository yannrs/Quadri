#include "telecommande.h"
//#include "Variables.h"
const int LedPin = 8;
/**************************************************
 *                 Class Telecommande             *
 **************************************************/

Telecommande::Telecommande(float Throttle_max,
float Roll_max,
float Pitch_max,
float Yaw_max,
float Throttle_min,
float Roll_min,
float Pitch_min,
float Yaw_min,
float Pitch_med,
float Roll_med,
float Yaw_med)
{
  setThrottle_max(Throttle_max);
  setRoll_max(Roll_max);
  setPitch_max(Pitch_max);
  setYaw_max(Yaw_max);
  setThrottle_min(Throttle_min);
  setRoll_min(Roll_min);
  setPitch_min(Pitch_min);
  setYaw_min(Yaw_min);
  setPitch_med(Pitch_med);
  setRoll_med(Roll_med);
  setYaw_med(Yaw_med);
}


Telecommande::Telecommande(){
  Telecommande(0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void Telecommande::Initialisation(boolean b){
  if(!b){// Si on ne veut pas faire de calibration
    setThrottle_max(Max_ThrottleExp);
    setRoll_max(Max_RollExp);
    setPitch_max(Max_PitchExp);
    setYaw_max(Max_YawExp);
    
    setThrottle_min(Min_ThrottleExp);
    setRoll_min(Min_RollExp);
    setPitch_min(Min_PitchExp);
    setYaw_min(Min_YawExp);
    
    setRoll_med(Med_RollExp);
    setPitch_med(Med_PitchExp);
    setYaw_med(Med_YawExp);
    
    digitalWrite(LedPin,LOW);
    delay(50);
    digitalWrite(LedPin,HIGH);
    delay(2000);
    digitalWrite(LedPin,LOW);
    delay(50);
  }
  else{
  
  Serial.println("INIT !!");
  delay(1000);
  
  // Lit le signal PPM du recepteur
  float  Throttle = pulseIn(Pin_Throttle, HIGH,25000); // Valeur comprise entre 800 et 2200
  float  Roll = pulseIn(Pin_Roll, HIGH,25000); 
  float  Pitch = pulseIn(Pin_Pitch, HIGH,25000);
  float  Yaw = pulseIn(Pin_Yaw, HIGH,25000);


//Signal de démarrage de l'initialisation (Led)
  for(int  p=0;p<5;p++){
    digitalWrite(LedPin,HIGH);
    delay(50);
    digitalWrite(LedPin,LOW);
    delay(50);
  }

//------------------------------Recherche des Max--------------------------
//Initialisation variable
  float Throttle_max=Throttle;
  float Roll_max=Roll;
  float Pitch_max=Pitch;
  float Yaw_max=Yaw;
  
  float Throttle_prec=Throttle;
  float Roll_prec=Roll;
  float Pitch_prec=Pitch;
  float Yaw_prec=Yaw;
  
  // Phase : les commandes sont au max 

  float t = millis();
  float t_prec =t;
  
   // Phase : les moteurs sont au max
  while (t-t_prec < 1000 || Throttle <= Throttle_max - 10 || Roll <= Roll_max - 10 || Pitch <= Pitch_max - 10 || Yaw <= Yaw_max - 10){
   
    // Actualise les entrées
    t = millis();
    Throttle = pulseIn(Pin_Throttle, HIGH,25000);
    Roll = pulseIn(Pin_Roll, HIGH,25000); 
    Pitch = pulseIn(Pin_Pitch, HIGH,25000);
    Yaw = pulseIn(Pin_Yaw, HIGH,25000);
    
    // Actualise les Max
    if(Throttle_max <= Throttle){
      Throttle_max=Throttle;
    }
    if(Yaw_max <= Yaw){
      Yaw_max=Yaw;
    }
    if(Roll_max <= Roll){
      Roll_max=Roll;
    }
    if(Pitch_max <= Pitch){
      Pitch_max=Pitch;
    }
    
    // Reset si les valeurs sont trop basses
    if(Throttle <= Max_ThrottleExp-20 || Roll <=  Max_RollExp-20 || Yaw <= Max_YawExp-20  || Pitch <= Max_PitchExp-20){
      Serial.println("reset1");
      t_prec = millis();
    }
    
    //Reset si variation brusque
    if(abs(Throttle_prec - Throttle)>10 || abs(Roll_prec - Roll)>10 || abs(Pitch_prec - Pitch)>10 || abs(Yaw_prec - Yaw)>10){
      Serial.println("reset2");
      t_prec = millis();  
    }
    
    //Sauvegarde
    Throttle_prec=Throttle;
    Roll_prec=Roll;
    Pitch_prec=Pitch;
    Yaw_prec=Yaw;
    
    #ifdef Debug
    Serial.print("Throttle : "); Serial.print(Throttle); Serial.print(", "); Serial.println(Max_ThrottleExp);
    Serial.print("Roll : "); Serial.print(Roll); Serial.print(", "); Serial.println(Max_RollExp);
    Serial.print("Pitch : "); Serial.print(Pitch); Serial.print(", "); Serial.println(Max_PitchExp);
    Serial.print("Yaw : "); Serial.print(Yaw); Serial.print(", "); Serial.println(Max_YawExp);
    #endif
    
    Serial.println("boucle");
  }

// Sauvegarde profonde
  setThrottle_max(Throttle_max);
  setRoll_max(Roll_max);
  setPitch_max(Pitch_max);
  setYaw_max(Yaw_max);


  for(int  p=0;p<5;p++){
    digitalWrite(LedPin,HIGH);  
    delay(50);
    digitalWrite(LedPin,LOW);
    delay(50);
  }


//------------------------------Recherche des Min--------------------------
  t_prec = t;
  float Throttle_min=Throttle;
  float Roll_min=Roll;
  float Pitch_min=Pitch;
  float Yaw_min=Yaw;

  // Phase : les moteurs sont au min 
  while (t-t_prec < 1000 || Throttle >= Throttle_min + 10 || Roll >= Roll_min + 10 || Pitch >= Pitch_min + 10 || Yaw >= Yaw_min + 10){
     
    // Actualise les entrées
    t = millis();
    Throttle = pulseIn(Pin_Throttle, HIGH,25000);
    Roll = pulseIn(Pin_Roll, HIGH,25000); 
    Pitch = pulseIn(Pin_Pitch, HIGH,25000);
    Yaw = pulseIn(Pin_Yaw, HIGH,25000);
    
  // Actualise les Max
    if(Throttle_min >= Throttle){
      Throttle_min=Throttle;
    }
    if(Yaw_min >= Yaw){
      Yaw_min=Yaw;
    }
    if(Roll_min >= Roll){
      Roll_min=Roll;
    }
    if(Pitch_min >= Pitch){
      Pitch_min=Pitch;
    }
    
    // Reset si les valeurs sont trop basses
    if(Throttle >= Min_ThrottleExp+20 || Roll >=  Min_RollExp+20 || Yaw >= Min_YawExp+20  || Pitch >= Min_PitchExp+20){
      Serial.println("reset1");
      t_prec = millis();
    }
    //Reset si variation brusque
    if(abs(Throttle_prec - Throttle)>10 || abs(Roll_prec - Roll)>10 || abs(Pitch_prec - Pitch)>10 || abs(Yaw_prec - Yaw)>10){
      Serial.println("reset2");
      t_prec = millis();  
    }
    
    //Sauvegarde
    Throttle_prec=Throttle;
    Roll_prec=Roll;
    Pitch_prec=Pitch;
    Yaw_prec=Yaw;
    
    Serial.print("Throttle : "); Serial.print(Throttle); Serial.print(", "); Serial.println(Min_ThrottleExp);
    Serial.print("Roll : "); Serial.print(Roll); Serial.print(", "); Serial.println(Min_RollExp);
    Serial.print("Pitch : "); Serial.print(Pitch); Serial.print(", "); Serial.println(Min_PitchExp);
    Serial.print("Yaw : "); Serial.print(Yaw); Serial.print(", "); Serial.println(Min_YawExp);
  }


  for(int  p=0;p<5;p++){
    digitalWrite(LedPin,HIGH);  
    delay(50);
    digitalWrite(LedPin,LOW);
    delay(50);
  }

// Sauvegarde profonde
  setThrottle_min(Throttle_min);
  setRoll_min(Roll_min);
  setPitch_min(Pitch_min);
  setYaw_min(Yaw_min);

 delay(2000);

//------------------------------Recherche des Medianes--------------------------
  int i=0;
  // Phase : les moteurs sont au med 
  while (t-t_prec < 1000){
    t = millis();
    Roll = pulseIn(Pin_Roll, HIGH,25000); 
    Pitch = pulseIn(Pin_Pitch, HIGH,25000);
    Yaw = pulseIn(Pin_Yaw, HIGH,25000);
    
    Yaw_med+=Yaw;
    Roll_med=+Roll;
    Pitch_med=+Pitch;

    i++;
  }

  setRoll_med(Roll_med/i);
  setPitch_med(Pitch_med/i);
  setYaw_med(Yaw_med/i);
  Serial.println("SORTIE INIT");  
 }//Fin initialisation
}// Fin initialisation Télécommande




float Telecommande::getThrottle_max(){
  return  Throttle_max;
}

void Telecommande::setThrottle_max (float f){
  Throttle_max =f;
}

float Telecommande::getRoll_max(){
  return  Roll_max;
}
void Telecommande::setRoll_max (float f){
  Roll_max =f;
}


float Telecommande::getPitch_max(){
  return  Pitch_max;
}
void Telecommande::setPitch_max (float f){
  Pitch_max =f;
}


float Telecommande::getYaw_max(){
  return  Yaw_max;
}
void Telecommande::setYaw_max (float f){
  Yaw_max = f;
}


float Telecommande::getThrottle_min(){
  return  Throttle_min;
}
void Telecommande::setThrottle_min (float f){
  Throttle_min =f;
}


float Telecommande::getRoll_min(){
  return  Roll_min;
}
void Telecommande::setRoll_min (float f){
  Roll_min = f;
}


float Telecommande::getPitch_min(){
  return  Pitch_min;
}
void Telecommande::setPitch_min (float f){
  Pitch_min =f;
}


float Telecommande::getYaw_min(){
  return  Yaw_min;
}
void Telecommande::setYaw_min (float f){
  Yaw_min = f;
}




float Telecommande::getRoll_med(){
  return  Roll_med;
}
float Telecommande::getPitch_med(){
  return  Pitch_med;
}
float Telecommande::getYaw_med(){
  return  Yaw_med;
}

void Telecommande::setPitch_med(float f){
  Pitch_med = f;
}  
void Telecommande::setRoll_med(float f){
  Roll_med = f;
}
void Telecommande::setYaw_med(float f){
  Yaw_med = f;
}


