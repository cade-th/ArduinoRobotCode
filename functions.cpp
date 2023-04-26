
#include "functions.h"

namespace functions {

//variable assignments
int enA = 1;
int in1 = 2;
int in2 = 3;
// Motor B pin connections
int enB = 5;
int in3 = 6;
int in4 = 7;

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

//L298 Motor Controller Pin Assignment

// LEFT Motor (LM) pin connections
int EnableLM = 1;
int LM_in1 = 2;
int LM_in2 = 3;

// RIGHT Motor (RM) pin connections
int EnableRM = 5;
int RM_in3 = 6;
int RM_in4 = 7;

int BRotate = 1;

int Rwhite = 0;
int Lwhite = 0;
int Rblack = 0;
int Lblack = 0;

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
  // move forward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left and right wheels in clockwise direction - Move forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
};

// move backward
void movBW(int speed)
{
  int PWMval = 255*speed/100;
  // move backward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed

  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left and right wheels in anti-clockwise direction - Move backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

// turn left
void movCW(int speed)
{
  int PWMval = 255*speed/100;
  // turn with 30% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, PWMval);
  analogWrite(enB, PWMval);
  // Rotate left wheel clockwise and right wheel in anti-clockwise direction - Spin clockwise/Turnright
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
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
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //delay(500); // turn left for 1 second  
}

void ReadColorSensors()
{
  // Setting RED (R) filter photodiodes to be read
  
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,LOW);
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,LOW);
  
  // Reading the output frequency
  
  RredFrequency = pulseIn(R_SensorOut, LOW,10000);
  LredFrequency = pulseIn(L_SensorOut, LOW,10000);
  
  // Remaping the value of the RED (R) frequency from 0 to 255
  
  RredColor = map(RredFrequency, 23, 190, 255, 0);
  LredColor = map(LredFrequency, 18, 136, 255, 0); 
 
  // Setting GREEN (G) filtered photodiodes to be read
  
  digitalWrite(RS2,HIGH);
  digitalWrite(RS3,HIGH);
  digitalWrite(LS2,HIGH);
  digitalWrite(LS3,HIGH);
  
  // Reading the output frequency
  
  RgreenFrequency = pulseIn(R_SensorOut, LOW,10000);
  LgreenFrequency = pulseIn(L_SensorOut, LOW,10000);
  
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  
  RgreenColor = map(RgreenFrequency, 24, 225, 255, 0);
  LgreenColor = map(LgreenFrequency, 20, 215, 255, 0);

  // Setting BLUE (B) filtered photodiodes to be read
  
  digitalWrite(RS2,LOW);
  digitalWrite(RS3,HIGH);
  digitalWrite(LS2,LOW);
  digitalWrite(LS3,HIGH);
  
  // Reading the output frequency
  
  RblueFrequency = pulseIn(R_SensorOut, LOW,10000);
  LblueFrequency = pulseIn(L_SensorOut, LOW,10000);
  
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  
  RblueColor = map(RblueFrequency, 21, 200, 255, 0);
  LblueColor = map(LblueFrequency, 17, 200, 255, 0);
}

void colorInit() 
{
  if(RredColor>200 && RgreenColor>200 && RblueColor>200)
  {
  //Right sensor white
    Rwhite = 1;
  }
  else
  {
    Rwhite = 0;
  }
  if(LredColor>200 && LgreenColor>200 && LblueColor>200)
  {
  //Left sensor white
    Lwhite = 1;
  }
  else
  {
    Lwhite = 0;
  }
  if(RredColor<70 && RgreenColor<90 && RblueColor<90)
  {
  //Right sensor Black
    Rblack = 1;
  }
  else
  {
    Rblack = 0;
  }
  if(LredColor<70 && LgreenColor<90 && LblueColor<90)
  {
  //Left sensor Black
    Lblack = 1;
  }
  else
  {
    Lblack = 0;
  }
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

  // Set all motor controller pins as outputs
  
  pinMode(EnableLM, OUTPUT);
  pinMode(EnableRM, OUTPUT);
  pinMode(LM_in1, OUTPUT);
  pinMode(LM_in2, OUTPUT);
  pinMode(RM_in3, OUTPUT);
  pinMode(RM_in4, OUTPUT);
  
  // Initial state - Turn off all the motors
  
  digitalWrite(LM_in1, LOW);
  digitalWrite(LM_in2, LOW);
  digitalWrite(RM_in3, LOW);
  digitalWrite(RM_in4, LOW);

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
  
}

//function for moving purely based on color
void movColor()
{
  //case for black
  if(Rblack && Lblack)
  {
    //Serial.print("Black");
    //Serial.print("\n");
    movFW(25);
    delay(750);
    movCCW(50);
    delay(1100);
     
  }
  
  //case for both sensors reading white
  else if(Rwhite && Lwhite)
  {
    movFW(20);
  }
 
  //else, if not black or white is detected
  else
  {
    //If the Right sensor detects a color
    if (!Rwhite && Lwhite)
    {
      delay(100);
      movCW(20);
    }
    // Left sensor detects color
    else if (!Lwhite && Rwhite )
    {
      delay(100);
      movCCW(20);
    }
    //If both sensors detect a color
    else{
      movFW(20);
    }
  }
}
}
//namespace
