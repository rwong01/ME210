/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Multiplexer.h
  --------------------------
  Library for interfacing with analog multiplexer.
*/

#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "Arduino.h"
#include "SPI.h"

//10MHz

class Multiplexer {
public:
/**********************************  SETUP  ***********************************/
  void     init(uint8_t chipSelect);
/********************************  FUNCTIONS  *********************************/
  uint16_t readValue(uint8_t channel);

private:
/*********************************  HELPERS  **********************************/
/*********************************  OBJECTS  **********************************/
};

#endif
