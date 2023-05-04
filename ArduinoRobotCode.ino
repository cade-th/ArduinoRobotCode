
#include "functions.h"

void setup()
{
  pinInit();
  
  // Begins serial communication
  Serial.begin(115200);
}

void loop() 
{  
  
 //ReadColorSensors();

 //colorInit();

 //movColor();

 movFW(120);


}
