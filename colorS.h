#ifndef _colorS_h
#define _colorS_h


#include "Arduino.h"

//LEFT and RIGHT TCS230 Color Sensor Pin Assignments (and now with middle)

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

//booleans
extern int Rwhite;
extern int Lwhite;
extern int Rblack;
extern int Lblack;

extern int Rred;
extern int Lred;
extern int Rblue;
extern int Lblue;
extern int Lgreen;
extern int Rgreen;
extern int Lyellow;
extern int Ryellow;

extern int Mred;
extern int Mblue;
extern int Mwhite;

//other color sensor variables
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


#define blackVal 150
#define whiteVal 200


void readColorSensors();

void colorInit();

void pinInit();

void movColor();

void testColorsFreq();

void testColorsValue();

void testColorBooleans();

void readMColorValues();

void readMColorBooleans();

void detectWhite();

#endif
