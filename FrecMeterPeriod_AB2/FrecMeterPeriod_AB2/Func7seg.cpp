/***********************************************
   Transfers data to a MAX7219/MAX7221 register.

   @param address The register to load data into
   @param value   Value to store in the register
************************************************/
#include "Func7seg.h"
#include<SPI.h>

void maxTransfer(uint8_t address, uint8_t value) {

  // Ensure LOAD/CS is LOW
  digitalWrite(LOAD_PIN, LOW);
  // Send the register address
  SPI.transfer(address);
  // Send the value
  SPI.transfer(value);
  // Tell chip to load in data
  digitalWrite(LOAD_PIN, HIGH);
}

void SetAll(uint8_t cmd, uint8_t Ccount, uint8_t Dcount) {

  for ( int i = 1; i <= Dcount; i++) {
    // Ensure LOAD/CS is LOW
    digitalWrite(LOAD_PIN, LOW);
    for ( int j = 0; j < Ccount; j++) {
      //  while (count--) { // Send the register address
      SPI.transfer(i);
      SPI.transfer(cmd);
    }
    // Tell chip to load in data
    digitalWrite(LOAD_PIN, HIGH);
  }
}

void spiTransfer(int addr, volatile byte opcode, volatile byte data) {
  /* The array for shifting the data to the devices */
  byte spidata[16];
  //Create an array with the data to shift out
  int offset = addr * 2;
  int maxbytes = maxDevices * 2;
  // clear buffer
  for (int i = 0; i < maxbytes; i++)
    spidata[i] = (byte)0;
  //put our device data into the array
  spidata[offset + 1] = opcode;
  spidata[offset] = data;
  // Ensure LOAD/CS is LOW
  digitalWrite(LOAD_PIN, LOW);
  //Now shift out the data
  for (int i = maxbytes; i > 0; i--)   SPI.transfer(spidata[i - 1]);
  //latch the data onto the display
  digitalWrite(LOAD_PIN, HIGH);
  /*
#ifdef DEBUG
  for (int i = maxbytes; i > 0; i--)   {
    print_hex((int)spidata[i - 1], 8);
    Serial.print (" ");

  }
  Serial.println (" ");
#endif
*/
}
void init7segments()
{
  // REINIT DRIVERS, IF THEY HANGED UP
  maxTransfer(0x0F, 0x00);
  maxTransfer(0x00, 0x00);
  maxTransfer(0x0C, 0x01);
  maxTransfer(0x00, 0x00);

}

void display7seg ( unsigned long Nr, char ndig, char dppos )
{
  // Display Period in format 8.3
  for ( int i = 1; i <= ndig ; i = i + 1)
  { 
    // get las digit
    char s = Nr % 10;
    Nr /= 10;
    // Leading zero shown as  " "
    if ( i > dppos && s == 0  && Nr == 0) s = 0xf;
    // Digpoint?
    if (i == dppos) s |= 0x80;
    // send digit 
    spiTransfer(0, i, s  ) ;
  }
}

