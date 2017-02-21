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

class Robot {
public:
/**********************************  SETUP  ***********************************/
  Robot() :
    temp(0) {
  }
  void    init();
/********************************  FUNCTIONS  *********************************/
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
  uint8_t temp = 0;
};

#endif
