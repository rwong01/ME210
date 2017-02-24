/*
  ME210 | Febuary 2017
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
static const uint16_t  BLACK_THRESHOLD         =    420;
static const uint8_t   DRIVE_SPEED             =    255;
static const uint8_t   LAUNCHER_SPEED          =    255;
static const uint8_t   LOADER_SPEED            =    255;
static const uint32_t  RUNTIME_TIMEOUT         = 130000;
static const uint32_t  TRAPPED_TIMEOUT         =  10000;
static const uint32_t  LAUNCH_TIMEOUT          =  10000;
static const uint32_t  RELOAD_TIMEOUT          =  10000;

/*****************************  TEENSY PIN OUTS  ******************************/
static const uint8_t   START_PIN               =     13;
static const uint8_t   MULTIPLEXER_CS          =     10;

static const uint8_t   IR_IN_01                =     26;
static const uint8_t   IR_IN_02                =     26;
static const uint8_t   IR_IN_03                =     26;
static const uint8_t   IR_IN_04                =     26;
static const uint8_t   IR_IN_05                =     26;
static const uint8_t   IR_IN_06                =     26;
static const uint8_t   IR_IN_07                =     26;
static const uint8_t   IR_IN_08                =     26;
static const uint8_t   IR_IN_09                =     26;
static const uint8_t   IR_IN_10                =     26;
static const uint8_t   IR_IN_11                =     26;
static const uint8_t   IR_IN_12                =     26;

static const uint8_t   MOTOR_LOAD_A            =      9;
static const uint8_t   MOTOR_LOAD_B            =      9;
static const uint8_t   MOTOR_FIRE_A            =      9;
static const uint8_t   MOTOR_FIRE_B            =      9;
static const uint8_t   MOTOR_RIGHT_A           =      9;
static const uint8_t   MOTOR_RIGHT_B           =      9;
static const uint8_t   MOTOR_LEFT_A            =      9;
static const uint8_t   MOTOR_LEFT_B            =      9;

#endif
