
#include "functions.h"

void setup()
{
  //initialize values for the pins of the teensy
  functions::pinInit();
  
  // Begins serial communication
  Serial.begin(115200);
}
//first commit
void loop() 
{  
 //read the color sensors
 functions::ReadColorSensors();
 
 //adjust the values of the color variables
 functions::colorInit();

 //move based on colors
 functions::movColor();
}
