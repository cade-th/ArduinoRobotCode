
#include "colorS.h"
#include "motors.h"


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

//booleans
int Rwhite = 0;
int Lwhite = 0;
int Rblack = 0;
int Lblack = 0;

int Rred = 0;
int Lred = 0;
int Rblue = 0;
int Lblue = 0;
int Rgreen = 0;
int Lgreen = 0;
int Lyellow = 0;
int Ryellow = 0;

int Mred = 0;
int Mblue = 0;

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
  
  RredColor = map(RredFrequency,45, 150, 255, 0);
  LredColor = map(LredFrequency, 45, 210, 255, 0); 
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
  
  RgreenColor = map(RgreenFrequency, 22, 265, 255, 0);
  LgreenColor = map(LgreenFrequency, 27, 225, 255, 0);

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
  
  RblueColor = map(RblueFrequency, 21, 170, 255, 0);
  LblueColor = map(LblueFrequency, 17, 200, 255, 0);
  MblueColor = map(MblueFrequency, 80, 250, 255, 0);
}

void colorInit()
{
  //middle color booleans ----------------------------------------------
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

  //left and right booleans -----------------------------------------------
  
  if(RredColor > 220 && RgreenColor > 190 && RblueColor > 190)
  {
    Rwhite = 1;
  }
  else if(RredColor <50 && RgreenColor <120 && RblueColor <50)
  {
    Rblack = 1;
  }
  else if(RredColor > 200 && RgreenColor > 200)
  {
    Ryellow = 1;
  }
  else if(RredColor > RblueColor && RredColor > RgreenColor )
  {
    Rred = 1;
  }
  else if(RblueColor > RredColor && RblueColor > RgreenColor )
  {
    Rblue = 1;
  }
  else if(RgreenColor > RredColor && RgreenColor > RblueColor)
  {
    Rgreen = 1;
  }
  else
  {
   Serial.println("No Color Detected in Right Sensor"); 
  }


  if(LredColor > 220 && LgreenColor > 190 && LblueColor > 190)
  {
    Lwhite = 1;
  }
  else if(LredColor <70 && LgreenColor<70 && LblueColor<70)
  {
    Lblack = 1;
  }
  else if(LredColor > 190 && LgreenColor > 190)
  {
    Lyellow = 1;
  }
  else if(LredColor > LblueColor && LredColor > LgreenColor )
  {
    Lred = 1;
  }

}


//function for moving purely based on color
void movColor()
{
  /*
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
  else if (LblueColor > LredColor && LblueColor > LgreenColor )
  {
    Lblue = 1;
  }
  else if(LgreenColor > LredColor && LgreenColor > LblueColor)
  {
    Lgreen = 1;
  }
  else
  {
   Serial.println("No Color Detected in Left Sensor"); 
  }
  */
}

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
  //right black
  Serial.print("RBlack:");
  Serial.println(Rblack);

  //left black
  Serial.print("LBlack:");
  Serial.println(Lblack);

  //right white
  Serial.print("RWhite:");
  Serial.println(Rwhite);

  //left white
  Serial.print("LWhite:");
  Serial.println(Lwhite);

  //right red
  Serial.print("Rred:");
  Serial.println(Rred);

  //left red
  Serial.print("Lred:");
  Serial.println(Lred);

  //right green
  Serial.print("Rgreen:");
  Serial.println(Rgreen);

  //left green
  Serial.print("Lgreen:");
  Serial.println(Lgreen);

  //right blue
  Serial.print("Rblue:");
  Serial.println(Rblue);

  //left blue
  Serial.print("Lblue:");
  Serial.println(Lblue);

}
