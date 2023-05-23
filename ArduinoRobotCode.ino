#include "functions.h"

void setup()
{
  pinInit();
  gripArmInit();
 
  // Begins serial communication
  Serial.begin(115200);
}

void loop()
{  
 //move based on ultrasonic
 //readUltraSensors();
 //movUltra();


 readColorSensors();
 colorInit();

 testColorBooleans();
 
 //movColor();
 
/*
  //MOTOR TEST------------------------------------------------
  movFW(movSpd);
  delay(1500); // time for move fw
  movCW(rotSpd);
  delay(1500); // time for turn left
  movCCW(rotSpd);
  delay(1500); // time for turn right
  movBW(movSpd);
  delay(1500); // time for move bw
  stop();
  delay(1000); // delay whole program for 10s
  //---------------------------------------------------------------
*/

}
