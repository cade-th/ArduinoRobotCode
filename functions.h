#ifndef _functions_h
#define _functions_h

#include "Arduino.h"

//macros
#define TimeStep_ms 0

//ultrasonic sensors
#define echoPinR 16 // attach Echo of HC-SR04
#define trigPinR 17 //attach Trig of HC-SR04

#define echoPinL 21// attach Echo of HC-SR04
#define trigPinL 20//attach Trig of HC-SR04

#define echoPinM 15// attach Echo of HC-SR04
#define trigPinM 14//attach Trig of HC-SR04

//ultrasonic global variables
extern long durationR;
extern int distanceR;

extern long durationL;
extern int distanceL;

extern long durationM;
extern int distanceM;

// LEFT and RIGHT TCS230 Color Sensor Pin Assignments

#define LS0 32
#define LS1 31
#define LS2 30
#define LS3 29
#define L_SensorOut 28

#define RS0 33
#define RS1 34
#define RS2 35
#define RS3 36
#define R_SensorOut 37

#define movSpd 100
#define rotSpd 100

//global variables to use
//L298 Motor Controller Pin Assignment
// Motor A pin connections
extern int enA;
extern int in1;
extern int in2;
// Motor B pin connections
extern int enB;
extern int in3;
extern int in4;

extern int LredFrequency;
extern int LgreenFrequency;
extern int LblueFrequency;
extern int LredColor;
extern int LgreenColor;
extern int LblueColor;
extern int LstopColor;

extern int RredFrequency;
extern int RgreenFrequency;
extern int RblueFrequency;
extern int RredColor;
extern int RgreenColor;
extern int RblueColor;
extern int RstopColor;

//L298 Motor Controller Pin Assignment

// LEFT Motor (LM) pin connections
extern int EnableLM;
extern int LM_in1;
extern int LM_in2;

// RIGHT Motor (RM) pin connections
extern int EnableRM;
extern int RM_in3;
extern int RM_in4;

extern int BRotate;

extern int Rwhite;
extern int Lwhite;
extern int Rblack;
extern int Lblack;

//functions declarations
void stop();

void movFW(int speed);

void movBW(int speed);

void movCW(int speed);

void movCCW(int speed);

void readColorSensors();

void colorInit();

void pinInit();

void movColor();

//works
void readUltraL();

//works
void readUltraR();

//works
void readUltraM();

void readUltraSensors();

void movUltra();


#endif
