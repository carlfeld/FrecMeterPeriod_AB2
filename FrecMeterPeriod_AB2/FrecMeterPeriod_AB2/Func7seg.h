/*
 * Func7segs.h
 *
 * Created: 6/7/2018 16:46:43
 *  Author: carlos
 */ 
//#include <Arduino.h>
#include "Defines.h"

void maxTransfer(uint8_t address, uint8_t value);
void SetAll(uint8_t cmd, uint8_t Ccount, uint8_t Dcount);
void spiTransfer(int addr, volatile byte opcode, volatile byte data);
void init7segments();
void display7seg ( unsigned long Nr, char ndig, char dppos );
