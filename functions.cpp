
#include "functions.h"
#include <Servo.h>


//L298 Motor Controller Pin Assignment

// Motor A pin connections
int enA = 1;
int in1 = 2;
int in2 = 3;
// Motor B pin connections
int enB = 5;
int in3 = 6;
int in4 = 7;

int timeT = 50;

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


int LredFrequency = 0;
int LgreenFrequency = 0;
int LblueFrequency = 0;
int LredColor = 0;
int LgreenColor = 0;
int LblueColor = 0;
int LstopColor = 0;

int RredFrequency = 0;
int RgreenFrequency = 0;
int RblueFrequency = 0;
int RredColor = 0;
int RgreenColor = 0;
int RblueColor = 0;
int RstopColor = 0;


int MredColor = 0;
int MblueColor = 0;
int MredFrequency = 0;
int MblueFrequency = 0;

int McolorDifference = 0;


//ultrasonic global variables
long durationR = 0;
int distanceR = 0;
long durationL = 0;
int distanceL = 0;

long durationM = 0;
int distanceM = 0;

int BRotate = 1;

int Rwhite = 0;
int Lwhite = 0;
int Rblack = 0;
int Lblack = 0;

int Mred = 0;
int Mblue = 0;

void stop()
{
  // move forward with 0% speed - For PWM value 0
  analogWrite(enA, 0);
  analogWrite(enB, 0); 
  // Turn off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}

// move forward
void movFW(int speed)
{
  int PWMval = 255*speed/100;
 // Serial.println(PWMval);
  // move forward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left and right wheels in clockwise direction - Move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //Serial.println("moving");
  delay(1000);
}

// move backward
void movBW(int speed)
{
  int PWMval = 255*speed/100;
  // move backward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed

  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left and right wheels in anti-clockwise direction - Move backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
  delay(1000);
}

// turn left
void movCW(int speed)
{
  int PWMval = 255*speed/100;
  // turn with 30% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left wheel clockwise and right wheel in anti-clockwise direction - Spin clockwise/Turnright
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //delay(500);
}

// turn right
void movCCW(int speed)
{
  int PWMval = 255*speed/100;
  // turn with 30% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left wheel anti-clockwise and right wheel in clockwise direction - Spin anti-clockwiseTurn left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //delay(500); // turn left for 1 second  
}

void readColorSensors()
{
  // Setting RED (R) filter photodiodes to be read
  
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,LOW);
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,LOW);
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,LOW);
  
  // Reading the output frequency
  
  RredFrequency = pulseIn(R_SensorOut, LOW,10000);
  LredFrequency = pulseIn(L_SensorOut, LOW,10000);
  MredFrequency = pulseIn(M_SensorOut, LOW,10000);
  
  // Remaping the value of the RED (R) frequency from 0 to 255
  
  RredColor = map(RredFrequency,80, 210, 255, 0);
  LredColor = map(LredFrequency,80, 210, 255, 0); 
  MredColor = map(MredFrequency,80, 210, 255, 0);
  
 
  // Setting GREEN (G) filtered photodiodes to be read
  
  digitalWrite(RS2,HIGH);
  digitalWrite(RS3,HIGH);
  digitalWrite(LS2,HIGH);
  digitalWrite(LS3,HIGH);
  //don't need for middle sensor
  
  // Reading the output frequency
  
  RgreenFrequency = pulseIn(R_SensorOut, LOW,10000);
  LgreenFrequency = pulseIn(L_SensorOut, LOW,10000);
  
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  
  RgreenColor = map(RgreenFrequency, 50, 200, 255, 0);
  LgreenColor = map(LgreenFrequency, 50, 200, 255, 0);

  // Setting BLUE (B) filtered photodiodes to be read
  
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,HIGH);
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,HIGH);
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,HIGH);
  
  // Reading the output frequency
  
  RblueFrequency = pulseIn(R_SensorOut, LOW,10000);
  LblueFrequency = pulseIn(L_SensorOut, LOW,10000);
  MblueFrequency = pulseIn(M_SensorOut, LOW);
  
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  
  RblueColor = map(RblueFrequency, 80, 250, 255, 0);
  LblueColor = map(LblueFrequency, 80, 250, 255, 0);
  MblueColor = map(MblueFrequency, 80, 250, 255, 0);
}

void colorInit() 
{

  /*
  if(RredColor >= whiteVal && RgreenColor >= whiteVal && RblueColor >= whiteVal)
  {
  //Right sensor white
    Rwhite = 1;
  }
  else
  {
    Rwhite = 0;
  }
  if(LredColor >= whiteVal  && LgreenColor >= whiteVal && LblueColor >= whiteVal)
  {
  //Left sensor white
    Lwhite = 1;
  }
  else
  {
    Lwhite = 0;
  }
  if(RredColor <= blackVal && RgreenColor <= blackVal && RblueColor <= blackVal)
  {
  //Right sensor Black
    Rblack = 1;
  }
  else
  {
    Rblack = 0;
  }
  if(LredColor <= blackVal && LgreenColor <= blackVal && LblueColor <= blackVal)
  {
  //Left sensor Black
    Lblack = 1;
  }
  else
  {
    Lblack = 0;
  }

*/
 
  //MIDDLE COLOR BOOLEANS ---------------------------------------------------

  McolorDifference = MredColor - MblueColor;
   
  if(McolorDifference > 90)
  {
    Mred = 1;
  }
  else 
  {
    Mred = 0;
  }
  
 if(McolorDifference < -210)
  {
    Mblue = 1;
  } 
  else
  {
    Mblue = 0;
  }

/*
  //Right COLOR BOOLEANS ---------------------------------------------------

  McolorDifference = MredColor - MblueColor;
   
  if(McolorDifference > 90)
  {
    Mred = 1;
  }
  else 
  {
    Mred = 0;
  }
  
 if(McolorDifference < -200)
  {
    Mblue = 1;
  } 
  else
  {
    Mblue = 0;
  }

  */
 }

void pinInit()
{
  // Set all motor controller pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Initial state - Turn off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Port setup for LEFT color sensor pins
  
  pinMode(LS0, OUTPUT);
  pinMode(LS1, OUTPUT);
  pinMode(LS2, OUTPUT);
  pinMode(LS3, OUTPUT);
  pinMode(L_SensorOut, INPUT);
  
  // Setting LEFT sensor frequency scaling to 20%
  
  digitalWrite(LS0,HIGH);
  digitalWrite(LS1,LOW);
  
  // Port setup for RIGHT color sensor pins
  
  pinMode(RS0, OUTPUT);
  pinMode(RS1, OUTPUT);
  pinMode(RS2, OUTPUT);
  pinMode(RS3, OUTPUT);
  pinMode(R_SensorOut, INPUT);
  
  // Setting RIGHT sensor frequency scaling to 20%
  
  digitalWrite(RS0,HIGH);
  digitalWrite(RS1,LOW);

   // Port setup for MIDDLE color sensor pins
  
  pinMode(MS0, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(M_SensorOut, INPUT);
  
  // Setting RIGHT sensor frequency scaling to 20%
  
  digitalWrite(MS0,HIGH);
  digitalWrite(MS1,LOW);


  //ultrasonic pins
  pinMode(trigPinR, OUTPUT); 
  pinMode(echoPinR, INPUT);

  pinMode(trigPinL, OUTPUT); 
  pinMode(echoPinL, INPUT);

  pinMode(trigPinM, OUTPUT); 
  pinMode(echoPinM, INPUT);

  //force sensor
  //pinMode(ForceSen, OUTPUT);
  
}


//function for moving purely based on color
void movColor()
{
  //case for white
  if(Rwhite && Lwhite)
  {
    //Serial.println("Black");
    
   // movFW(movSpd); //25
    //delay(750);
    movCCW(rotSpd); //50
    delay(1100);
    
  }
  
  //case for both sensors reading black
  if(Rblack && Lblack)
  {
    //Serial.println("White");
    movFW(movSpd); //20
  }

 /*
  //else, if not black or white is detected
  else
  {
    //If the Right sensor detects a color
    if (!Rwhite && Lwhite)
    {
      
    //Serial.println("Color");
      
      delay(100);
      movCW(rotSpd); //20
      
    }
    // Left sensor detects color
    else if (!Lwhite && Rwhite )
    {
      //Serial.println("Color");
       
      delay(100);
      movCCW(movSpd); //20
      
    }
    //If both sensors detect a color
    else{

    //  Serial.println("Both are detecting color");

      
      
     // Serial.print("Color");
      //Serial.print("\n");
      movFW(movSpd); //20
      
    }
  }
  */
}

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

  if (distanceR < 20)
  {
    stop();
    //delay(1000);
    
  }

  if (distanceL < 20)
  {
    stop();
    //delay(1000);
  }

  if (distanceM < 20)
  {
    stop();
    //delay(1000);
  }
  movFW(movSpd);

  /*
  //object in front
  if (distanceM < 20)
  {
    movBW(rotSpd);
    movCW(rotSpd);
  }
  
  //object to the right
  if (distanceR < 20)
  {
    while (distanceR < 20)
    {
      movFW(movSpd);
    }
    movCW(rotSpd);
   
  }
  
  //object to the right
  if (distanceL < 20)
  {
    while (distanceL < 20)
    {
      movFW(movSpd);
    }
    movCCW(rotSpd);
  } 
  
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

/*
extern int LredFrequency;
extern int LgreenFrequency;
extern int LblueFrequency;
*/

/*
extern int RredFrequency;
extern int RgreenFrequency;
extern int RblueFrequency;
*/

void testColorsFreq()
{
  Serial.print("  LredFrequency:");
  Serial.println(LredFrequency);
  Serial.print("LgreenFrequency:");
  Serial.println(LgreenFrequency);
  Serial.print(" LblueFrequency:");
  Serial.println(LblueFrequency);
  Serial.print("  RredFrequency:");
  Serial.println(RredFrequency);
  Serial.print("RgreenFrequency:");
  Serial.println(RgreenFrequency);
  Serial.print(" RblueFrequency:");
  Serial.println(RblueFrequency);
  delay(100);
}


 void testColorsValue()
{
  Serial.print("  LredColor:");
  Serial.println(LredColor);
  Serial.print("LgreenColor:");
  Serial.println(LgreenColor);
  Serial.print(" LblueColor:");
  Serial.println(LblueColor);
  Serial.print("  RredColor:");
  Serial.println(RredColor);
  Serial.print("RgreenColor:");
  Serial.println(RgreenColor);
  Serial.print(" RblueColor:");
  Serial.println(RblueColor);
  delay(100);
}

void testColorBooleans()
{
  Serial.print("RBlack:");
  Serial.println(Rblack);
  Serial.print("RWhite:");
  Serial.println(Rwhite);
  Serial.print("LBlack:");
  Serial.println(Lblack);
  Serial.print("LWhite");
  Serial.println(Lwhite);
 delay(100);
}

void gripArmInit()
{
  //Setup Gripper
  Gripper.attach(23);  // attaches the servo on pin 22 to the servo object
  Arm.attach(22);  // attaches the servo on pin 23 to the servo object
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

void readMColorValues()
{
  Serial.print("MredColor:");
  Serial.println(MredColor);
  Serial.print("ColorDifference:");
  Serial.println(McolorDifference);
  Serial.print("MblueColor:");
  Serial.println(MblueColor);
}

void readMColorBooleans()
{
  Serial.print("Mred:");
  Serial.println(Mred);
  Serial.print("Mblue:");
  Serial.println(Mblue);
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
