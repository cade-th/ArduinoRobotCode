#ifndef _functions_h
#define _functions_h

#include "Arduino.h"
#include "arduino_freertos.h"
#include "avr/pgmspace.h"

namespace functions {


//macros
#define TimeStep_ms 0
#define LOW1 arduino::LOW
#define HIGH1 arduino::HIGH
#define OUTPUT1 arduino::OUTPUT
#define INPUT1 arduino::INPUT

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

void ReadColorSensors();

void colorInit();

void pinInit();

void movColor();

}
#endif
