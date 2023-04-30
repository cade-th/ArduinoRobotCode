
#include "functions.h"
//freertos included as a zip library
//had to get a custom one to work with the teensy board

using namespace functions;

void setup()
{
  //initialize states for the pins of the teensy
  pinInit();
  
  // Begins serial communication
  Serial.begin(115200);
}

void loop() 
{  
 //read the color sensors
 ReadColorSensors();

 //adjust the values of the color booleans
 colorInit();

 //move based on colors variable booleans
 movColor();
}
