/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Robot.h
  --------------------------
  Primary robot code.
*/

#ifndef ROBOT_H
#define ROBOT_H

#include "Config.h"
#include "States.h"
#include "Arduino.h"
#include <MAX11643.h>
#include <DRV8825.h>

class Robot {
public:
/**********************************  SETUP  ***********************************/
  Robot() :
    stepper(MOTOR_STEP_STEPS, MOTOR_STEP_DIR, MOTOR_STEP_STEP, MOTOR_STEP_MODE0, MOTOR_STEP_MODE1, MOTOR_STEP_MODE2) {
  }
  void           init();
/********************************  FUNCTIONS  *********************************/
  state_tier_1_t getState();
  void           updateState();
  void           exitBase();
  void           attackTower1();
  void           attackTower2();
  void           hitBumper();
  void           quit();

private:
/*********************************  HELPERS  **********************************/
  void           setPinModes();
  void           waitForStart();

  void           updateSensors();
  void           printState();
  void           checkTimer();
  void           checkBumper();
  void           center();

  bool           findBack();
  bool           orientBack();
  bool           findStart();

  bool           attackTower();
  bool           launchEgg();

  void           turnLeft();
  void           turnRight();
  void           turnForward();
  void           turnBackward();

  bool           detectedI();
  bool           detectedLeft();
  bool           detectedRight();
  bool           detectedLeftOff();
  bool           detectedRightOff();
  bool           detectedS();
  bool           detectedPluss();
  bool           detectedPlussCenter();

  float          readSensor_US();
  bool           readSensor_IR(uint8_t pinNum);
  bool           readSensors_BUMP(uint8_t pinNum);

/*********************************  OBJECTS  **********************************/
  state_tier_1_t state_1;
  state_tier_2_t state_2;
  state_tier_3_t state_3;
  state_tier_4_t state_4;
  uint32_t       USTime;
  uint32_t       startTime;
  uint32_t       escapeTime;
  uint32_t       launchTime;
  uint32_t       centerTime;
  float          distance;
  float          distanceShortest = US_THRESHOLD;
  bool           frontSensorBump[2];
  bool           frontSensorIR[2];
  bool           leftSensorIR[3];
  bool           rightSensorIR[3];
  bool           centerSensorIR[3];
  bool           leftSensorIROLD[3];
  bool           rightSensorIROLD[3];
  DRV8825        stepper;
};

#endif
