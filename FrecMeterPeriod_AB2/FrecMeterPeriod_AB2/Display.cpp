//Beginning of Auto generated function prototypes by Atmel Studio
#include<Arduino.h>
#include "Display.h"
#include "Defines.h"
//int Ndigs(unsigned long nr);
//End of Auto generated function prototypes by Atmel Studio
#ifdef PRINT  
void DebugPrint(long Cval){
	
	// print value using mseconds & 3 digits
	Serial.print (Cval / 1000.0, 3  );
	Serial.print (" ms [" );
	Serial.print ( Ndigs(Cval) );
	Serial.print ("] " );
	
	Serial.print ( 1000000.0 / Cval, 3  );
	Serial.println (" Hz" );
}

// Simetric rounding
unsigned long Sround ( unsigned long p )
{
	// Simetric rounding of last digit
	if ((p % 10) >= 5 ) return ((p / 10) * 10 + 10);
	else     return ((p / 10) * 10);

}
#endif

