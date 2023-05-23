#ifndef _gripArm_h
#define _gripArm_h

#include "Arduino.h"

#define ARMBOTTOM 180
#define GRIPPEROPEN 150
#define GRIPPERCLOSED 0
#define ARMTOP 100

#define ForceSen A6

#define boxColorRed 1
#define boxColorBlue 0

#define boxSizeBig 1
#define boxSizeSmall 0

#define TimeStep_ms 0

extern int boxFound;
extern int boxGrabbed;
//1 for red, 0 for blue

//1 for red, 0 for blue
extern int boxColor;
//1 for big, 0 for small
extern int boxSize;

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

//functions declarations

void gripArmInit();

void controlGripper(int distance);

void readForce();

void controlArm(int distance);

void printWeight();

void detectBox();

void grabBox();

void findBox();

#endif
