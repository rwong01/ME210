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

/***********************************  BOOT  ***********************************/
AccelStepper stepper(1, MOTOR_STEP_STEP, MOTOR_STEP_DIR);
int main() {
  Serial.begin(9600);
  pinMode(MOTOR_STEP_DIR, OUTPUT);
  pinMode(MOTOR_STEP_STEP, OUTPUT);
  stepper.setMaxSpeed(LAUNCH_SPEED);
  stepper.setSpeed(LAUNCH_SPEED);
/***********************************  MAIN  ***********************************/
  while(true) {
    stepper.runSpeed();
    delay(BUFFER_CLEAR_TIME);
  }
}
