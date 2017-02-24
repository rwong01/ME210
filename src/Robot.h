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
  returnToBase_s,
  reloadEggs_s,
  quit_s
};

class Robot {
public:
/**********************************  SETUP  ***********************************/
  void    init();
/********************************  FUNCTIONS  *********************************/
  state_t getState();
  void    exitBase();
  void    attackTower();
  void    returnToBase();
  void    reloadEggs();
  void    quit();

private:
/*********************************  HELPERS  **********************************/
  void    findLine();
  void    findStart();

  void    turnLeft();
  void    turnRight();
  void    moveForward();
  void    moveBackward();

  void    launchEgg();

  bool    detectedT();
  void    center();

/*********************************  OBJECTS  **********************************/
  state_t state;
};

#endif
