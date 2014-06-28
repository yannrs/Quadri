/*
 EmnQuad V 0.1
 2013/2014
 EMN Robotics Club Team
*/

//*******************************************
//************ Serial Commands **************
//*******************************************

/**
 * Read the command received from the serial communication
 * and perform the corresponding action
 **/
void readSerialCommands() {
  // Check for serial message
  if (Serial.available()) {
    char queryType = Serial.read();
    
    switch (queryType) {
      case 'A': //
        break;
  
      case 'B': // 
        break;
    }
  }
}
