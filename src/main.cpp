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
static const uint32_t RUNTIME_CONST = 1000 * 60 * 10;

int main(void) {
  Serial.begin(9600);
/***********************************  MAIN  ***********************************/
  while(millis() < RUNTIME_CONST) {
    Serial.println("RISKY BISCUITS");
    //exit start zone
    //trip all bariiers
    //goto 1st t
    //launch 3 balls
    //goto 2nd t
    //launch 3 balls
    //goto 3rd t
    //launch 3 balls
    //goto start
    //wait 10 seconds to load
  }
}
