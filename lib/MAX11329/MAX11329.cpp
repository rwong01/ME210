/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: MAX11329.cpp
  --------------------------
  Implementation of MAX11329.h
*/

#include "MAX11329.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main multiplexer.
 */
void MAX11329::init() {
  pinMode(chipSelect, OUTPUT);
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: readValue
 * -------------------
 * This function returns the analog voltage of the specific channel.
 */
uint16_t MAX11329::readValue(uint8_t channel) {
  //The MAX11329–MAX11332 operate with SCLK idling high, and thus operate with CPOL = CPHA = 1.
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(chipSelect, LOW);
  SPI.transfer(0x00);// send changel num
  // read back two bytes
  uint16_t value = analogRead(channel);
  //DOUT is a 16-bit data word containing a 4-bit channel address, followed by a 12-bit conversion result led by the MSB when CHAN_ID is set to 1 in the ADC Mode Control register (Figure 2a).
  //the 16-bit data word includes a leading zero and the 12-bit conversion result is followed by 3 trailing zeros.
  SPI.endTransaction();
  digitalWrite(chipSelect, HIGH);
  return value;
  /*
  CHSEL3 | CHSEL2 | CHSEL1 | CHSEL0 | SELECTED CHANNEL (N)
     0   |   0    |   0    |   0    | AIN0
     0   |   0    |   0    |   1    | AIN1
     0   |   0    |   1    |   0    | AIN2
     0   |   0    |   1    |   1    | AIN3
     0   |   1    |   0    |   0    | AIN4
     0   |   1    |   0    |   1    | AIN5
     0   |   1    |   1    |   0    | AIN6
     0   |   1    |   1    |   1    | AIN7
     1   |   0    |   0    |   0    | AIN8
     1   |   0    |   0    |   1    | AIN9
     1   |   0    |   1    |   0    | AIN10
     1   |   0    |   1    |   0    | AIN10
     1   |   1    |   0    |   0    | AIN12
     1   |   1    |   0    |   1    | AIN13
     1   |   1    |   0    |   1    | AIN13
     1   |   1    |   1    |   0    | AIN14
     1   |   1    |   1    |   1    | AIN15
  */
}

/*********************************  HELPERS  **********************************/
