/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX1143.cpp
  --------------------------
  Implementation of MAX1143.h
*/

#include "MAX1143.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main multiplexer.
 */
void MAX1143::init() {
  pinMode(chipSelect, OUTPUT);
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: readValue
 * -------------------
 * This function returns the analog voltage of the specific channel.
 */
uint16_t MAX1143::readValue(uint8_t channel) {
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelect, LOW);
  SPI.transfer(0x00);// send changel num
  // read back two bytes
  uint16_t value = analogRead(channel);
  SPI.endTransaction();
  digitalWrite(chipSelect, HIGH);
  return value;
}

/*********************************  HELPERS  **********************************/
