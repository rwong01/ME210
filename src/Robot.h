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

class Robot {
public:
/**********************************  SETUP  ***********************************/
  void           init();
/********************************  FUNCTIONS  *********************************/
  state_tier_1_t getState();
  void           updateState();
  void           sleep();

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

  bool           orientBack();
  bool           findStart();
  bool           leaveStart();

  bool           attackTower();
  bool           launchEgg();

  void           turnLeft();
  void           turnRight();
  void           turnForward();

  bool           detectedLeftOff();
  bool           detectedRightOff();
  bool           detectedPluss();
  bool           detectedPlussStrict();
  bool           detectedPlussCenter();

  float          readSensor_US();
  bool           readSensor_IR(uint8_t pinNum);
  bool           readSensors_BUMP(uint8_t pinNum);

/*********************************  OBJECTS  **********************************/
  state_tier_1_t state_1;
  state_tier_2_t state_2;
  state_tier_3_t state_3;
  state_tier_4_t state_4;

  uint8_t        plus_number    = 0;
  bool           plus_prev      = false;
  bool           plus_curr      = false;
  uint8_t        goal_plus      = 0;
  uint32_t       plus_cooldown  = 100000;
  uint32_t       plus_time      = 0;

  float          distance       = 0;
  float          avgDist        = 0;
  float          avgDistOld     = 0;
  float          avgMin         = -1;
  bool           distDescending = false;
  float          alpha          = 0.01;

  uint32_t       USTime;
  uint32_t       startTime;
  uint32_t       escapeTime;
  uint32_t       leavingTime;
  uint32_t       launchTime;
  uint32_t       centerTime;
  uint32_t       LOOP_RATE = BUFFER_CLEAR_TIME_START;

  bool           frontSensorBump[2];
  bool           frontSensorIR[2];
  bool           leftSensorIR[3];
  bool           rightSensorIR[3];
  bool           centerSensorIR[3];
  bool           leftSensorIROLD[3];
  bool           rightSensorIROLD[3];
};

#endif
