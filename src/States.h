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
static const char* states_teir_1_names[] = {
  "exitBase_s",
  "attackTower1_s",
  "attackTower2_s",
  "hitBumper_s",
  "quit_s"
};

enum state_tier_2_t {
  orienting_s,
  finding_s,
  leaving_s,
  approaching_s,
  loading_s,
  attacking_s
};
static const char* states_teir_2_names[] = {
  "orienting_s",
  "finding_s",
  "leaving_s",
  "approaching_s",
  "loading_s",
  "attacking_s"
};

enum state_tier_3_t {
  turningLeftOne_s,
  turningLeftTwo_s,
  turningRightOne_s,
  turningRightTwo_s,
  turningForeward_s,
  turningBackward_s,
  ignoringPluss_s,
  centeringPluss_s,
  launchingEggs_s,
};
static const char* states_teir_3_names[] = {
  "turningLeftOne_s",
  "turningLeftTwo_s",
  "turningRightOne_s",
  "turningRightTwo_s",
  "turningForeward_s",
  "turningBackward_s",
  "ignoringPluss_s",
  "centeringPluss_s",
  "launchingEggs_s",
};

enum state_tier_4_t {
  inchLeft_s,
  inchRight_s,
  noLine_s
};
static const char* states_teir_4_names[] = {
  "inchLeft_s",
  "inchRight_s",
  "noLine_s"
};

#endif
