/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX11329.h
  --------------------------
  Library for interfacing with the MAX11329 analog multiplexer.
*/

#ifndef MAX11329_H
#define MAX11329_H

#include "Arduino.h"
#include "SPI.h"

class MAX11329 {
public:
/**********************************  SETUP  ***********************************/
  MAX11329(uint8_t cs) :
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
