/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: States.h
  --------------------------
  Global defenition of states
*/

#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include <stdint.h>


/***********************************  DATA  ***********************************/
enum state_tier_1_t {
  exitBase_s,
  attackTower1_s,
  attackTower2_s,
  hitBumper_s,
  quit_s
};

enum state_tier_2_t {
  approaching_s,
  attacking_s
};

enum state_tier_3_t {
  turningLeft_s,
  turningRight_s,
  turningForeward_s,
  turningBackward_s,
  launchingEggs_s
};
#endif
