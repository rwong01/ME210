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
  while(1) {
    state_t state = BISCUIT.getState();
    switch(state) {
        case exitBase_s: {
          BISCUIT.exitBase();
          break;
        }
        case attackTower1_s: {
          BISCUIT.attackTower();
          break;
        }
        case attackTower2_s: {
          BISCUIT.attackTower();
          break;
        }
        case returnToBase_s: {
          BISCUIT.returnToBase();
          break;
        }
        case reloadEggs_s: {
          BISCUIT.reloadEggs();
          break;
        }
        case quit_s: {
          BISCUIT.quit();
          break;
        }
    }
  }
}
