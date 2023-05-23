
#include "gripArm.h"
#include "motors.h"
#include "colorS.h"
#include <Servo.h>

//Force Sensor Setup
float M = 0.0000002; 
float C = 0.000006;

int R1 = 330; 
int R2 = 10000;
int R3 = 10000; 
int Vin = 3.3;

int force = 0;
float Vout = force*3.3/1023; 
float Rx = R2/(Vout/Vin + R1/(R1+R3))-R2; 
float weight = (1/Rx - C)/M;

int PWMSignal;
int grip = 150;

int armPosition = 75;
int gripperPosition = 150;

int boxFound = 0;
int boxGrabbed = 0;
int boxColor = 0;
int boxSize = 0;

//Gripper Setup
Servo Gripper;  // create servo object to control a servo
Servo Arm;  // create servo object to control a servo


void gripArmInit()
{
  //Setup Gripper
  Gripper.attach(22);  // attaches the servo on pin 22 to the servo object
  Arm.attach(23);  // attaches the servo on pin 23 to the servo object
  controlArm(ARMTOP);
  controlGripper(GRIPPEROPEN);
}

void controlGripper(int distance)
{
  int val1 = map(distance, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  Gripper.write(val1); // sets the servo position according to the scaled value
  delay(100);
}

void readForce()
{
  force = analogRead(ForceSen);

  Vout = force*3.3/1023; 
  Rx = R2/(Vout/Vin + R1/(R1+R3))-R2; 
  weight = (1/Rx - C)/M;
}

void controlArm(int distance)
{
  int val2 = map(distance, 0, 300, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  Arm.write(val2); // sets the servo position according to the scaled value
  delay(100);
}

void printWeight()
{
  Serial.print("Weight:");
  Serial.println(weight);
  delay(100);
}

void detectBox()
{

   while (!boxFound)
  {
    
    while (!Mblue)
    {
      readColorSensors();
      colorInit();
      controlArm(armPosition);
      armPosition += 2;
    }
    if (Mblue)
    {
      boxColor = boxColorBlue;
    }
    else
    {
      boxColor = boxColorRed;
    }
    
    boxFound = 1;
  }
}

void grabBox()
{
  //controlGripper(GRIPPEROPEN);
  while (!boxGrabbed)
  {
 
    while(force == 0) 
    {
      
      readForce();
      controlGripper(gripperPosition);
      gripperPosition -= 10;
    }
    if (gripperPosition < 80)
    {
      boxSize = boxSizeBig;
    }
    else
    {
      boxSize = boxSizeSmall;
    }
    boxGrabbed = 1;
   
  }
}

void findBox()
{
  detectBox();
  grabBox();
  delay(500);
  if(boxGrabbed)
  {
    controlArm(ARMTOP);
  }
}

void detectWhite()
{
  if (Rwhite || Lwhite) 
  {
    movBW(movSpd);
    delay(300);
    movCW(movSpd);
    delay(200);
  }
}
