/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX1143.h
  --------------------------
  Library for interfacing with the MAX1143 analog multiplexer.
*/

#ifndef MAX1143_H
#define MAX1143_H

#include "Arduino.h"
#include "SPI.h"

class MAX1143 {
public:
/**********************************  SETUP  ***********************************/
  MAX1143(uint8_t cs) :
    chipSelect(cs) {
  }
  void     init();
/********************************  FUNCTIONS  *********************************/
  uint16_t readValue(uint8_t channel);

private:
/*********************************  HELPERS  **********************************/
/*********************************  OBJECTS  **********************************/
  uint8_t chipSelect;
};

#endif
