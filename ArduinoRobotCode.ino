#include "mane.h"

void setup()
{
  pinInit();
  gripArmInit();
 
  // Begins serial communication
  Serial.begin(115200);
}

void loop()
{  
 
findBox();

//controlArm(ARMTOP);

}
