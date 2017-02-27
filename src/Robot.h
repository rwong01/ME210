/*
  ME210 | Febuary 2017
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
#include <Multiplexer.h>

class Robot {
public:
/**********************************  SETUP  ***********************************/
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

  void           checkTimer();
  void           updateSensors();
  void           printState();

  void           findLine();
  void           findStart();

  bool           attackTower();
  bool           launchEgg(bool init);

  void           turnLeft();
  void           turnRight();
  void           turnForward();
  void           turnBackward();

  bool           detectedI();
  bool           detectedT();
  void           center();

  bool           readSensor_IR(uint8_t pinNum);
  bool           readSensors_BUMP(uint8_t pinNum);

/*********************************  OBJECTS  **********************************/
  Multiplexer    PCB;
  state_tier_1_t state_1;
  state_tier_2_t state_2;
  state_tier_3_t state_3;
  uint32_t       startTime;
  uint32_t       launchTime;
  bool           frontSensorsBump[2];
  bool           leftSensorIR[3];
  bool           rightSensorIR[3];
  bool           centerSensorIR[3];
  bool           backSensorIR[3];
};

#endif
