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
#include <AccelStepper.h>

class Robot {
public:
/**********************************  SETUP  ***********************************/
  Robot() :
    stepper(1, MOTOR_STEP_STEP, MOTOR_STEP_DIR) {
  }
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
  void           center();

  bool           orientBack();
  bool           findStart();
  bool           leaveStart();

  bool           attackTower(uint16_t stepperTime01, uint16_t stepperTime02, uint16_t stepperTime03, uint16_t stepperTime04, uint16_t stepperTime05, uint16_t stepperTime06);
  bool           launchEgg(uint16_t stepperSpeed);

  void           turnLeft();
  void           turnRight();
  void           turnForward();

  bool           detectedPluss();
  bool           detectedPlussCenter();

  float          readSensor_US();
  bool           readSensor_IR(uint8_t pinNum);
  bool           readSensors_BUMP(uint8_t pinNum);

/*********************************  OBJECTS  **********************************/
  AccelStepper stepper;
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
  float          minDist        = 8;
  bool           distDescending = false;
  float          alpha          = 0.01;
  float          beta           = 0.75;

  uint32_t       USTime;
  uint32_t       startTime;
  uint32_t       escapeTime;
  uint32_t       leavingTime;
  uint32_t       launchTime;
  uint32_t       loadTime;
  uint32_t       centerTime;
  uint32_t       plussTIme;
  uint32_t       LOOP_RATE = BUFFER_CLEAR_TIME_NORM;

  bool           frontSensorBump[2];
  bool           frontSensorIR[2];
  bool           leftSensorIR[3];
  bool           rightSensorIR[3];
  bool           centerSensorIR[3];
  bool           leftSensorIROLD[3];
  bool           rightSensorIROLD[3];
};

#endif
