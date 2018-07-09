/*
* FreqCounter.h
*
* Created: 8/7/2018 12:14:49
* Author: carlos
*/


#ifndef __FREQCOUNTER_H__
#define __FREQCOUNTER_H__

//class FreqCounter
//{
////variables
//public:
//protected:
//private:
//
////functions
//public:
//FreqCounter();
//~FreqCounter();
//protected:
//private:
//FreqCounter( const FreqCounter &c );
//FreqCounter& operator=( const FreqCounter &c );
//
//}; //FreqCounter


/*
FreqCounter.h - Library for a Frequency Counter c.
Created by Martin Nawrath, KHM Lab3, Dec. 2008
Released into the public domain.
*/





#include <avr/interrupt.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif

// Global variables for interrupt
static unsigned long          _f_freq;
static volatile unsigned char _f_ready;
static volatile unsigned char _f_mlt;
static volatile unsigned int  _f_tics;
static volatile unsigned int  _f_period;
static volatile unsigned int  _f_comp;

class FreqCounterClass
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
	static void start(int ms);
    static bool f_ready();
    static unsigned long f_freq();
}; //FreqCounter

extern FreqCounterClass FreqCounter;
#//endif

#endif //__FREQCOUNTER_H__
