/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Config.h
  --------------------------
  Global constants specific to robot.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <stdint.h>

/****************************  EDITABLE CONSTANTS  ****************************/
static const uint16_t  BLACK_THRESHOLD         =    100;
static const uint16_t  DRIVE_SPEED             =   1023;
static const uint16_t  LAUNCH_SPEED            =   1023;
static const uint16_t  LOADER_SPEED            =    255;
static const uint8_t   FOREWARD                =      1;
static const uint8_t   BACKWARD                =      0;
static const uint32_t  RUNTIME_TIMEOUT         = 130000;
static const uint32_t  ESCAPE_TIMEOUT          =   2000;
static const uint32_t  LAUNCH_TIMEOUT          =  10000;

/*****************************  TEENSY PIN OUTS  ******************************/
static const uint8_t   START_PIN               =     69;
static const uint8_t   MULTIPLEXER_CS          =     69;

static const uint8_t   BUMPER_LEFT             =     69;
static const uint8_t   BUMPER_RIGHT            =     69;

static const uint8_t   MOTOR_LEFT_DIR          =     69;
static const uint8_t   MOTOR_LEFT_SPEED        =     69;
static const uint8_t   MOTOR_RIGHT_DIR         =     69;
static const uint8_t   MOTOR_RIGHT_SPEED       =     69;
static const uint8_t   MOTOR_LOAD_DIR          =     69;
static const uint8_t   MOTOR_LOAD_SPEED        =     69;
static const uint8_t   MOTOR_FIRE_DIR          =     69;
static const uint8_t   MOTOR_FIRE_SPEED        =     69;

#endif
