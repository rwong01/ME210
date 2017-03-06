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
 * Function: readValue
 * -------------------
 * This function returns the analog voltage of the specific channel.
 */
uint16_t MAX11643::readValue(uint8_t channel) {
  uint8_t settingsRegisterByte    = 0B01110100;
  uint8_t averagingRegisterByte   = 0B00100000;
  uint8_t converstionRegisterByte = 0B10000110 | (channel << 3);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelect, LOW);
  SPI.transfer(settingsRegisterByte);
  SPI.transfer(averagingRegisterByte);
  uint16_t ret = SPI.transfer(converstionRegisterByte);
  uint16_t value = (ret >> 4);
  SPI.endTransaction();
  digitalWrite(chipSelect, HIGH);
  return value;
}
