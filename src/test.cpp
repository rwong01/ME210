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

#include "Robot.h"

/***********************************  BOOT  ***********************************/
Robot BISCUIT;
int main(void) {
  BISCUIT.init();
  analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_REV, 0);
/***********************************  MAIN  ***********************************/
  while(true) {
    BISCUIT.updateState();
    delay(BUFFER_CLEAR_TIME);
  }
}
