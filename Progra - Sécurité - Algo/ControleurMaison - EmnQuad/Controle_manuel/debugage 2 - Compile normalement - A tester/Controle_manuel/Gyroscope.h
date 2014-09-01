//Arduino 1.0+ only

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

#include <Arduino.h>
#include "Wire.h"
//#include "Variables.h"

void getGyroValues(int *x, int *y, int *z);
int setupL3G4200D(int scale);
void writeRegister(int deviceAddress, byte address, byte val);
int readRegister(int deviceAddress, byte address);


#endif
