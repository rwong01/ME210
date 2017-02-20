/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu
  File: main.cpp
  --------------------------
  main logic.
*/

#include "Arduino.h"

/***********************************  BOOT  ***********************************/
int main(void) {
  Serial.begin(9600);
/***********************************  MAIN  ***********************************/
  while(true) {
    Serial.println("RISKY BISCUITS");
    delay(10);
  }
}
