/*
  FrcMetperiod.cpp - Library for
  Created by Carlos Feldman July.1.2018

*/

#include "FrcMetPeriod.h"
#include "Defines.h"
// Default Constructor Class Default 5000 ms Timeout
void FrcMetPeriodClass::begin() {
  FrcMetPeriodClass::begin(500 );
}

// Alternate Constructor Class
void FrcMetPeriodClass::begin(int Timeout ) {
  _TimeoutVal = Timeout;
  _TimeoutFlag = false;
  FrcMetPeriod.SetStats(IDDLE);
  // initialize timer1
  noInterrupts();           // disable all interrupts
  // SETTINGS FOR ATMEGA 328 / ATMEGA256
  // TODO ADD ATMEGA8 ATTINY 84 & 2313
 #if defined (__AVR_ATmega168__) || defined (__AVR_ATmega48__) || defined (__AVR_ATmega88__) || defined (__AVR_ATmega328P__) || (__AVR_ATmega1280__)
  // reset controL register T1
   TCCR1A = 0;
  // reset counter 1
  TCCR1B = 0;
  TCNT1 = 0;
  _OflwCount = 0;
  // SETUP  INPUT CAPTURE MODE FILTER + POSITIVE EDGE
  TCCR1B |= (1 << ICNC1) | (1 << ICES1) ;
  // SETUP INPUT CAPTURE ISR
  /* Clear ICF1. Clear pending interrupts */
  TIFR1   |= 1 << ICF1;
  /* Enable Timer 1 Capture Event Interrupt */
  TIMSK1  |= 1 << ICIE1;
  // Not Counting
  // Start counter
  TCNT1 = 0;
  // 250 Khz
#ifdef CLOCK_64
  TCCR1B |= (1 << CS11) | (1 << CS10); // CLOCK  prescaler 64
#endif
  // 2 Mhz
#ifdef CLOCK_8
  TCCR1B |= (1 << CS10); // CLOCK  prescaler 8
#endif
  // 16 Mhz
#ifdef CLOCK_1
  TCCR1B |= (1 << CS11); // CLOCK  prescaler 1
#endif
  // watchout Timer 1 Compare interrupts ( Overflow Counter )
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
#endif

#if defined (__AVR_ATmega8__) || defined (__AVR_ATmega32__)
// TODO ADD SUPPORT FOR ATMEGA8 & ATMEGA #"
  // reset controL register T1
  TCCR1A = 0;
  // reset counter 1
  TCCR1B = 0;
  TCNT1 = 0;
  _OflwCount = 0;
  // SETUP  INPUT CAPTURE MODE FILTER + POSITIVE EDGE
  TCCR1B |= (1 << ICNC1) | (1 << ICES1) ;
  // SETUP INPUT CAPTURE ISR
  /* Clear ICF1. Clear pending interrupts */
  TIFR   |= 1 << ICF1;
  /* Enable Timer 1 Capture Event Interrupt */
  TIMSK  |= 1 << TICIE1;
  // Not Counting
  // Start counter
  TCNT1 = 0;
  // 250 Khz
  #ifdef CLOCK_64
  TCCR1B |= (1 << CS11) | (1 << CS10); // CLOCK  prescaler 64
  #endif
  // 2 Mhz
  #ifdef CLOCK_1
  TCCR1B |= (1 << CS10); // CLOCK  prescaler 8
  #endif
  // 16 Mhz
  #ifdef CLOCK_8
  TCCR1B |= (1 << CS11); // CLOCK  prescaler 1
  #endif
  // watchout Timer 1 Compare interrupts ( Overflow Counter )
  TIMSK |= (1 << OCIE1A);  // enable timer compare interrupt
#endif  
  interrupts();             // enable all interrupts
}

//
// Get Start Time in uS
unsigned long FrcMetPeriodClass::Tstart () {
  return (_Tstart * K);
}

//
// Get Stop Time in uS
unsigned long FrcMetPeriodClass::Tstop () {
  return ((_Tstop - _Tstart) * K)  ;
}

// Get Actual Time
// Time in uS
unsigned long FrcMetPeriodClass::GetT () {
  unsigned long T;
  T = (((_OflwCount << 16) + TCNT1) - _Tstart) * K;
  return (T )  ;
}

// Actual Time in mS
unsigned long FrcMetPeriodClass::GetTms () {
  unsigned long T;
  T = FrcMetPeriodClass::GetT () / 1000;
  return (T )  ;
}

// Set counter status
void FrcMetPeriodClass::SetStats (Status_t  S) {
  _CountStats = S  ;
}

// get counter status
Status_t FrcMetPeriodClass::GetStats (void ) {
  return (_CountStats) ;
}


#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega48__) || defined (__AVR_ATmega88__) || defined (__AVR_ATmega328P__) || (__AVR_ATmega1280__)
// ISR proceses Inp D4, rising edge
// Stores Start  and Stops  Edges of Timer1 & Overflows
// Changes CountStats
ISR (TIMER1_CAPT_vect) {
  // signal start of ISR
  //Start of count ? --> Start counting
  switch (FrcMetPeriod.GetStats())
  {
    case START:
      _Tstart = (_OflwCount << 16) + TCNT1 ;
      _TimeoutFlag = false;
      // signal start of counting
      FrcMetPeriod.SetStats(COUNT);
      break;
    case COUNT:
      _Tstop = (_OflwCount << 16) + TCNT1;
      // signal end of counting
      FrcMetPeriod.SetStats(EOC);
      break;
    default: ;
  }
}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  _OflwCount++;
  // Timeout detected ?
  if ( ( FrcMetPeriod.GetTms () >= _TimeoutVal   ) && (FrcMetPeriod.GetStats() == COUNT))  {
    _TimeoutFlag = true;
    FrcMetPeriod.SetStats(TIMEOUT);
  }
}
#endif

#if defined (__AVR_ATmega8__) || defined (__AVR_ATmega32__)
// TODO ADD SUPPORT FOR ATMEGA8 & ATMEGA #"
// ISR Overflow timer 1 Increases Overflow counter OfwlCount
ISR (TIMER1_CAPT_vect) {
	// signal start of ISR
	//Start of count ? --> Start counting
	switch (FrcMetPeriod.GetStats())
	{
		case START:
		_Tstart = (_OflwCount << 16) + TCNT1 ;
		_TimeoutFlag = false;
		// signal start of counting
		FrcMetPeriod.SetStats(COUNT);
		break;
		case COUNT:
		_Tstop = (_OflwCount << 16) + TCNT1;
		// signal end of counting
		FrcMetPeriod.SetStats(EOC);
		break;
		default: ;
	}
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	_OflwCount++;
	// Timeout detected ?
	if ( ( FrcMetPeriod.GetTms () >= _TimeoutVal   ) && (FrcMetPeriod.GetStats() == COUNT))  {
		_TimeoutFlag = true;
		FrcMetPeriod.SetStats(TIMEOUT);
	}
}

#endif

// Instanciate the only FrcMetPeriod object
FrcMetPeriodClass FrcMetPeriod ;
