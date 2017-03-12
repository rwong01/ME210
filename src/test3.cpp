/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: test.cpp
  --------------------------
  Unit test suite.
*/

#include "Config.h"

/***********************************  BOOT  ***********************************/
int main() {
  Serial.begin(BAUD_RATE);
  pinMode(BEACKON_PIN, INPUT);
/***********************************  MAIN  ***********************************/
  Serial.print("Beackon is :");
  uint16_t value = analogRead(BEACKON_PIN);
  Serial.print(value);
  Serial.print('\n');
  delay(BUFFER_CLEAR_TIME_NORM);
}
