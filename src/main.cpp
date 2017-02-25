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
  BISCUIT.init();
/***********************************  MAIN  ***********************************/
  while(BISCUIT.state != quit_s) {
    if      (BISCUIT.state == exitBase_s)     BISCUIT.exitBase();
    else if (BISCUIT.state == attackTower1_s) BISCUIT.attackTower1();
    else if (BISCUIT.state == attackTower2_s) BISCUIT.attackTower2();
    else if (BISCUIT.state == hitBumper_s)    BISCUIT.hitBumper();
  }
  BISCUIT.quit();
}
