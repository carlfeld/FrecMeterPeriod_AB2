#ifndef _Defines_
#define _Defines_
#include <Arduino.h>
//#define PRINT
/* GLOBAL DEFINES AND STORAGE */
// CLOCK FRECUENCY SETTING
//#define CLOCK_64                     /* 250 Khz Clock */
#define CLOCK_8                     /* 2 Mhz Clock */
//#define CLOCK_1                   /* 16  Mhz Clock */
// Constants Conversion Counts to uSec
// 1 prescaler
#ifdef CLOCK_1
#define K  0.5
#endif
// 8 prescaler
#ifdef CLOCK_8
#define K  .0625
#endif
// 64 prescaler
#ifdef CLOCK_64
#define K  4
#endif

//Beginning of Auto generated function prototypes by Atmel Studio
int Ndigs(unsigned long nr);
//End of Auto generated function prototypes by Atmel Studio

// What pin on the Arduino connects to the LOAD/CS pin on the MAX7219/MAX7221
#define LOAD_PIN         7
// parameters for 7 Segment
const int maxDevices = 1;
const int maxDigits = 8;
// parameters for period meter
const byte ledPin = 10;
const byte ISRPin   = 9;
const byte modePin1 = 3;

#endif