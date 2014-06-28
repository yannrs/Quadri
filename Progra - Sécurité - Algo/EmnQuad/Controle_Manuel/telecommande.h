#ifndef TELECOMMANDE_H_
#define TELECOMMANDE_H_  

#include "Arduino.h"
#include "Pins.h"
/**************************************************
 *                 Class Telecommande
 **************************************************/

class Telecommande{
public:
  Telecommande() ;//: Telecommande(0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) {};
  Telecommande(float Throttle_max,
 				float Roll_max,
 				float Pitch_max,
 				float Yaw_max,
 
 				float Throttle_min,
 				float Roll_min,
 				float Pitch_min,
 				float Yaw_min,
 
                                float Pitch_med,
                                float Roll_med,
                                float Yaw_med
                                 );
  void Initialisation(boolean b);
  float getThrottle_max();
  float getRoll_max();
  float getPitch_max();
  float getYaw_max();

  float getThrottle_min();
  float getRoll_min();
  float getPitch_min();
  float getYaw_min();

  float getPitch_med();
  float getRoll_med();
  float getYaw_med();
  
  void setThrottle_max(float);
  void setRoll_max(float);
  void setPitch_max(float);
  void setYaw_max(float);

  void setThrottle_min(float);
  void setRoll_min(float);
  void setPitch_min(float);
  void setYaw_min(float);
  
  void setPitch_med(float);
  void setRoll_med(float);
  void setYaw_med(float);

private:  
  float Throttle_max;
  float Roll_max;
  float Pitch_max;
  float Yaw_max;

  float Throttle_min;
  float Roll_min;
  float Pitch_min;
  float Yaw_min;
  
  float Pitch_med;
  float Roll_med;
  float Yaw_med;

};

#endif

