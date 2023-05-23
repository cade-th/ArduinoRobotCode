
#ifndef _motors_h
#define _motors_h

#include "Arduino.h"

#define movSpd 70
#define rotSpd 70

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

void stop();

void movFW(int speed);

void movBW(int speed);

void movCW(int speed);

void movCCW(int speed);

void motorTest();


#endif
