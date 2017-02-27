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
#include "Arduino.h"

/***********************************  DATA  ***********************************/
enum state_t {
  exitBase_s,
  attackTower1_s,
  attackTower2_s,
  hitBumper_s,
  quit_s
};

class Robot {
public:
/**********************************  SETUP  ***********************************/
  void    init();
/********************************  FUNCTIONS  *********************************/
  void    updateSensors();
  void    exitBase();
  void    attackTower1();
  void    attackTower2();
  void    hitBumper();

  void    quit();

  state_t state;
private:
/*********************************  HELPERS  **********************************/
  void    setPinModes();
  void    waitForStart();

  void    findLine();
  void    findStart();

  void    attackTower();

  void    turnLeft();
  void    turnRight();
  void    turnForward();
  void    turnBackward();

  void    launchEgg();

  bool    detectedT();
  void    center();

  bool    readSensor_IR(uint8_t sensorNum);
  bool    readSensors_BUMP(uint8_t sensorNum);
  void    checkTimer();

/*********************************  OBJECTS  **********************************/
  uint32_t startTime;
  uint32_t launchTime;
  bool     frontSensorsBump[2] = {false};
  bool     leftSensorIR[3]     = {false};
  bool     rightSensorIR[3]    = {false};
  bool     centerSensorIR[3]   = {false};
  bool     backSensorIR[3]     = {false};
};

#endif
