/*
*/

#ifndef __FrcMetperiod_h_
#define __FrcMetperiod_h_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif
#include <inttypes.h>
// General definitions

// CLOCK FRECUENCY SETTING
//#define CLOCK_64                     /* 250 Khz Clock */
//#define CLOCK_8                     /* 2 Mhz Clock */
#define CLOCK_1                   /* 16  Mhz Clock */
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
#define K  4.0
#endif


// STATUS FOR THE COUNTER
typedef    enum  { IDDLE, START, COUNT, TIMEOUT, EOC } Status_t ;

// Global stuff used by ISR
static volatile unsigned long  _OflwCount = 0;   // Overflow counter
static volatile unsigned long _Tstart = 0;      // Start Time
static volatile unsigned long _Tstop = 0;       // Stop Time
static volatile Status_t _CountStats = IDDLE ; // Counter Status
static volatile unsigned long _TimeoutVal;  // ( in ms )
static volatile bool          _TimeoutFlag=false;



class FrcMetPeriodClass {
  public:
    static  void begin ();
    static  void begin (int Timeout);
    static  unsigned long Tstart ();
    static  unsigned long Tstop ();
    static  unsigned long GetT ();
    static  unsigned long GetTms ();
    static  bool          Timeout ();
    static  void SetStats (Status_t S);
    static  Status_t GetStats (void );
    static  Status_t CountStats_ ;

};

// Refer to the only instanced FrcMetPeriodClass object
extern FrcMetPeriodClass FrcMetPeriod ;
#endif
