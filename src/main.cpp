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
  BISCUIT.exitBase();
  while(1) {
    BISCUIT.attackTower();
    BISCUIT.attackTower();
    BISCUIT.returnToBase();
    BISCUIT.reloadEggs();
  }
  BISCUIT.quit();
}
