
#ifndef _ultra_h
#define _ultra_h

#include "Arduino.h"

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

void readUltraL();

void readUltraR();

void readUltraM();

void readUltraSensors();

void movUltra();

#endif
