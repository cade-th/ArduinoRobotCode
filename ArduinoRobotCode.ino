
#include "functions.h"

void setup()
{
  //initialize states for the pins of the teensy
  functions::pinInit();
  
  // Begins serial communication
  Serial.begin(115200);
}

void loop() 
{  
 //read the color sensors
 functions::ReadColorSensors();

 //adjust the values of the color booleans
 functions::colorInit();

 //move based on colors variable booleans
 functions::movColor();
}
