#ifndef _functions_h
#define _functions_h

#include "Arduino.h"

//macros

#define ARMBOTTOM 180
#define GRIPPEROPEN 150
#define GRIPPERCLOSED 0
#define ARMTOP 75

#define ForceSen A6

#define movSpd 140
#define rotSpd 100

#define blackVal 150
#define whiteVal 200

#define boxColorRed 1
#define boxColorBlue 0

#define boxSizeBig 1
#define boxSizeSmall 0

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

extern int boxFound;
extern int boxGrabbed;
//1 for red, 0 for blue

//1 for red, 0 for blue
extern int boxColor;
//1 for big, 0 for small
extern int boxSize;

// LEFT and RIGHT TCS230 Color Sensor Pin Assignments (and now with middle)

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

#define MS0 12
#define MS1 11
#define MS2 10
#define MS3 9
#define M_SensorOut 8

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

extern int timeT;

//Force Sensor Setup
extern float M; 
extern float C;

extern int R1; 
extern int R2;
extern int R3;
extern int Vin;


extern int force;
extern float Vout;
extern float Rx;
extern float weight;


extern int PWMSignal;
extern int grip;


//Gripper Setup
//Servo Gripper;  // create servo object to control a servo
//Servo Arm;  // create servo object to control a servo

extern int PWMSignal;
extern int grip;

extern int armPosition;
extern int gripperPosition;

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

extern int McolorDifference;

extern int MredFrequency;
extern int MblueFrequency;
extern int MredColor;
extern int MblueColor;
extern int MstopColor;

extern int BRotate;

//booleans
extern int Rwhite;
extern int Lwhite;
extern int Rblack;
extern int Lblack;

extern int Mred;
extern int Mblue;


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

void testColorsFreq();

void testColorsValue();

void testColorBooleans();

void gripArmInit();

void controlGripper(int distance);

void readForce();

void controlArm(int distance);

void readMColorValues();

void readMColorBooleans();

void printWeight();

void detectBox();

void grabBox();

void findBox();
#endif
