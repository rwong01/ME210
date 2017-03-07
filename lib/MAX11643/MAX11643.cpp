/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX11643.cpp
  --------------------------
  Implementation of MAX11643.h
*/

#include "MAX11643.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main multiplexer.
 */
void MAX11643::init() {
  pinMode(chipSelect, OUTPUT);
  SPI.begin();
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: reset
 * -------------------
 * This function resets the multiplexer
 */
 void MAX11643::reset() {
   uint8_t resetRegisterByte = 0B00010000;
   SPI.beginTransaction(SPISettings(4800000, MSBFIRST, SPI_MODE0));
   digitalWrite(chipSelect, LOW);
   SPI.transfer(resetRegisterByte);
   SPI.endTransaction();
   digitalWrite(chipSelect, HIGH);
 }


 /*
  * Function: readValue
  * -------------------
  * This function returns the analog voltage of the specific channel.
  */
uint16_t MAX11643::readValue(uint8_t channel) {
  uint8_t settingsRegisterByte = 0B01111000;
  uint8_t converstionRegisterByte = 0B10000110 | (channel << 3);
  SPI.beginTransaction(SPISettings(4800000, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelect, LOW);
  SPI.transfer(settingsRegisterByte);
  SPI.transfer(converstionRegisterByte);
  uint8_t retByte1 = SPI.transfer(0B00000000);
  uint8_t retByte2 = SPI.transfer(0B00000000);
  uint16_t value = ((retByte1 << 4) | (retByte2 >> 4));
  value *= 4;
  SPI.endTransaction();
  digitalWrite(chipSelect, HIGH);
  return value;
}
