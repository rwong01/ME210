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
#include <AccelStepper.h>

// /***********************************  BOOT  ***********************************/
// AccelStepper stepper(1, MOTOR_STEP_STEP, MOTOR_STEP_DIR);
// int main() {
//   Serial.begin(9600);
//   pinMode(MOTOR_FIRE_FWD,   OUTPUT);
//   pinMode(MOTOR_STEP_DIR,   OUTPUT);
//   pinMode(MOTOR_STEP_STEP,  OUTPUT);
//   // digitalWrite(MOTOR_FIRE_FWD, HIGH);
//   stepper.setMaxSpeed(LOADER_SPEED);
//   stepper.setSpeed(LOADER_SPEED);
//
// /***********************************  MAIN  ***********************************/
//   while(true) {
//     stepper.move(LOADER_STEP);
//     while(stepper.distanceToGo() != 0) {
//       stepper.runSpeedToPosition();
//       delay(BUFFER_CLEAR_TIME_STEP);
//     }
//     delay(LOADER_SLEEP);
//   }
// }
