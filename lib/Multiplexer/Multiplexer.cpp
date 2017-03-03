/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Multiplexer.cpp
  --------------------------
  Implementation of Multiplexer.h
*/

#include "Multiplexer.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main multiplexer.
 */
void Multiplexer::init(uint8_t chipSelect) {
  pinMode(chipSelect, OUTPUT);
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: readValue
 * -------------------
 * This function returns the analog voltage of the specific channel.
 */
uint16_t Multiplexer::readValue(uint8_t channel) {
  return analogRead(channel);
}

/*********************************  HELPERS  **********************************/
