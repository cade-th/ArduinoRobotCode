
#include "functions.h"

void setup()
{
  pinInit();
  
  // Begins serial communication
  Serial.begin(115200);
}

void loop()
{  
 
 //move based on ultrasonic
  readUltraSensors();
 // movUltra();
  
 // movFW(130);

 //move based on colors
 //readColorSensors();
 //colorInit();
 //movColor();

}
