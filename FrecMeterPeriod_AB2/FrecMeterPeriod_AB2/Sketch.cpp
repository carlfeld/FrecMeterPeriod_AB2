/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

/* Frec Meter Period V1.0  3.7.18

Timer1 As Avent Timer
*/
/*
ARDUINO CONNECTIONS
D0  RX
D1  TX
D2
D3   FREC/PERIOD SELECT
D4
D5
D6
D7   LOAD/CS Display (12)
D8   ICP Pin ( Frequency Input )
D9
D10  LED PIN
D11  DIN Display(1) (MOSI)
D12                 (MISO)
D13  CLK Display (13) (SCK)

MODULES:
Dbgfunc.ino Debug printouts
Defines.h definitions of constrants and systemwide  variables
Func7Seg.ino /segment display related stuff
*/
#include <SPI.h>
#include "defines.h"
#include "FrcMetPeriod.h"
#include "Display.h"
#include "Func7seg.h"
#include "FreqCounter.h"
//Beginning of Auto generated function prototypes by Atmel Studio
int Ndigs(unsigned long nr);
//End of Auto generated function prototypes by Atmel Studio




void setup()
{
	// some I/O config stuff
	//  pinModeFast(ledPin, OUTPUT);
	//  pinModeFast(ISRPin, OUTPUT);
	pinMode (ledPin, OUTPUT);
	pinMode (modePin1, INPUT_PULLUP);
	// Set 7 Segment load pin as output
	pinMode(LOAD_PIN, OUTPUT);
	// SPI CONFIG
	// Reverse the SPI transfer to send the MSB first
	SPI.setBitOrder(MSBFIRST);
	// Start SPI
	SPI.begin();
#ifdef PRINT	
	// Serial setup
	Serial.begin (115200);
#endif
	// initialize timer1
	// 7 segment stuff begins here
	//
	// Run 7 Segment LED test
	// All LED segments should light up
	maxTransfer(0x0F, 0x01);
	delay(500);
	// CLEAR LAMP TEST
	maxTransfer(0x0F, 0x00);
	// Enable mode B ( 7 segment decode )
	maxTransfer(0x09, 0xFF);
	// Use medium intensity
	maxTransfer(0x0A, 0x07);
	// Only scan maxDigits digits
	maxTransfer(0x0B, maxDigits - 1);
	// Turn on chip
	maxTransfer(0x0C, 0x01);
	// blank display
	SetAll(0xf, maxDevices, maxDigits);
	FrcMetPeriod.begin();
	delay(500);
}

// How many digits has nr ?
int Ndigs(unsigned long nr )
{
	int i = 0;
	while  ( nr > 0) {
		nr = nr / 10;
		i++;
	}
	return (i);
}

void loop()
{
	unsigned long Cval, Tval;
	FreqCounter.start(100);
	//  Serial.print (" S=");
	//  Serial.print (FrcMetPeriod.GetStats());
	//  Serial.print (" ");
	// IF Its IDDLE, Trigger a new measure
	if (FrcMetPeriod.GetStats() == IDDLE)       FrcMetPeriod.SetStats(START);
	// End of Counting or Timeout ?
	else if (FrcMetPeriod.GetStats() == EOC || FrcMetPeriod.GetStats() == TIMEOUT)
	{
		if (FrcMetPeriod.GetStats() == TIMEOUT) {
			Cval = 0;
		}
		else  {
			// convert count to microseconds
			Cval =  FrcMetPeriod.Tstop();// - FrcMetPeriod.Tstart()  ;
		}
#ifdef PRINT
		// let´s show some data at the serial port
		DebugPrint(Cval);
#endif
		// Signal print end
		init7segments();
		// depending on mode Pin Display period or frequency
		if (!digitalRead (modePin1)) {
			// Display Period in format 8.3
			display7seg ( Cval, maxDigits, 4 );
		}
		else {
			Tval = 100000000 / Cval;
			// Display frecuency in format 8.3 ( simetric rounding in the last digit )
			display7seg ( (Tval + 5) / 10, maxDigits, 2 );
		}
		// Signals a new conversion cycle
		FrcMetPeriod.SetStats(IDDLE);
		delay(200);
	}
	if (FrcMetPeriod.GetStats() == IDDLE) digitalWrite(ledPin, true);
	else digitalWrite(ledPin, false);
	delay(50);
	if ( FreqCounter.f_ready()) FreqCounter.f_freq();
}


