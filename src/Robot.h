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
  state_t getState();

  void    exitBase();
  void    attackTower1();
  void    attackTower2();
  void    hitBumper();

  void    quit();

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

  void    checkTimer();

/*********************************  OBJECTS  **********************************/
  state_t state;
  uint32_t startTime;
  uint32_t launchTime;
};

#endif
