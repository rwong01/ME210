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
//   uint16_t LOADER_SPEED = 280;
//   Serial.begin(9600);
//   pinMode(MOTOR_FIRE_FWD,   OUTPUT);
//   pinMode(MOTOR_STEP_DIR,   OUTPUT);
//   pinMode(MOTOR_STEP_STEP,  OUTPUT);
//   digitalWrite(MOTOR_FIRE_FWD, HIGH);
//   stepper.setMaxSpeed(LOADER_SPEED);
//   stepper.setSpeed(LOADER_SPEED);
//   uint32_t start = millis();
//   uint32_t startt;
//
// /***********************************  MAIN  ***********************************/
//   Serial.print("warming up...");
//   while ((millis() - start) <= 5000);
//   startt = millis();
//   for(int i = 0; i < 13; i++) {
//     while ((millis() - startt) <= LAUNCH_TIMEOUT) {
//       stepper.runSpeed();
//       delay(BUFFER_CLEAR_TIME_STEP);
//     }
//     stepper.setSpeed(LOADER_SPEED);
//     delay(LOAD_TIMEOUT);
//     startt = millis();
//   }
// }
