

#include "ultra.h"
#include "motors.h"
#include "colorS.h"

//ultrasonic global variables
long durationR = 0;
int distanceR = 0;
long durationL = 0;
int distanceL = 0;

long durationM = 0;
int distanceM = 0;

int BRotate = 1;

void readUltraR()
{
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH for 10 microseconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  // Reads the echoPin, returns the sound wave in microseconds
  durationL = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  distanceL = durationL * 0.034 / 2; // Speed of sound wave divided by 2 (send & receive)
}

void readUltraL()
{
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH for 10 microseconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  // Reads the echoPin, returns the sound wave in microseconds
  durationR = pulseIn(echoPinR, HIGH);
  // Calculating the distance
  distanceR = durationR * 0.034 / 2; // Speed of sound wave divided by 2 (send & receive)
}

void readUltraM()
{
  digitalWrite(trigPinM, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH for 10 microseconds
  digitalWrite(trigPinM, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinM, LOW);
  // Reads the echoPin, returns the sound wave in microseconds
  durationM = pulseIn(echoPinM, HIGH);
  // Calculating the distance
  distanceM = durationM * 0.034 / 2; // Speed of sound wave divided by 2 (send & receive)
}


void readUltraSensors()
{
  readUltraL();
  readUltraM();
  readUltraR();

  
  Serial.print("DistanceM: ");
  Serial.println(distanceM);
  if (distanceM < 15)
  {
    Serial.println("backing up");
    //movBW(movSpd);
  }
  
  Serial.print("DistanceR: ");
  Serial.println(distanceR);
  if (distanceR < 15)
  {
    Serial.println("turning Right");
    //movCCW(rotSpd);
  }
  
  Serial.print("DistanceL: ");
  Serial.println(distanceL);
  if (distanceL < 15)
  {
    Serial.println("turning left");
    //movCW(rotSpd);
  }
 
}

void movUltra() 
{
  readUltraM();
  movFW(movSpd);

  if (distanceM <15)
  {
    detectWhite();
    movCW(rotSpd);
    delay(500);
    readUltraL();
  }
  
  while (distanceL < 15 && distanceL > 10)
  {
    detectWhite();
    readUltraL();
    movFW(movSpd);
  }
 
  /*
  if (distanceL < 20)
  {
    stop();
    delay(1000);
  }

  if (distanceM < 20)
  {
    stop();
    delay(1000);
  }
  movFW(movSpd);

  */

  /*
  //white color detected right
  if (Rwhite)
  {
    movCW(rotSpd);
  }
  
  //white color detected left
  if (Lwhite)
  {
    movCCW(rotSpd);
  }
  
  else
  {
    movFW(movSpd);
  }
  */
}
