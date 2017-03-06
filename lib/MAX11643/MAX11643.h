/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX11643.h
  --------------------------
  Library for interfacing with the MAX11643 analog multiplexer.
*/

#ifndef MAX11643_H
#define MAX11643_H

#include "Arduino.h"
#include "SPI.h"

class MAX11643 {
public:
/**********************************  SETUP  ***********************************/
  MAX11643(uint8_t cs) :
    chipSelect(cs) {
  }
  void     init();
/********************************  FUNCTIONS  *********************************/
  uint16_t readValue(uint8_t channel);

private:
/*********************************  OBJECTS  **********************************/
  uint8_t chipSelect;
};

#endif
