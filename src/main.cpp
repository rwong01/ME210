/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: main.cpp
  --------------------------
  Main logic.
*/

#include "Robot.h"

/***********************************  BOOT  ***********************************/
Robot BISCUIT;
int main(void) {
  state_t state;
  BISCUIT.init();
  state = BISCUIT.getState();
/***********************************  MAIN  ***********************************/
  while(state != quit_s) {
    if      (state == exitBase_s)     BISCUIT.exitBase();
    else if (state == attackTower1_s) BISCUIT.attackTower1();
    else if (state == attackTower2_s) BISCUIT.attackTower2();
    else if (state == hitBumper_s)    BISCUIT.hitBumper();
    state = BISCUIT.getState();
  }
  BISCUIT.quit();
}
