# ME210:
###The Risky Biscuits

#events States:
The robot uses an Event Driven model in order to clearly transition between states of operation.

#### States
1. Init
 - 1a. System Initialization
2. Exit base
 - 2a. Find Line
 - 2b. Center Onto Line
 - 2c. Find Start Line
3. Attack Tower 1
 - 3a. Approach Tower
 - 3b. Attack Tower
 - 3c. Retreat Back
4. Attack Tower 2
 - 4a. Approach Tower
 - 4b. Attack Tower
 - 4c. Retreat Back
5. Hit Bumper
 - 5a. Turn Around
 - 5b. Approach Pad
6. Quit
 - 6a. System Shutdown

#Code Architecture:
The robot attack software operates on a read-eval loop in order to change states and respond to its environment.

The robot attack software was written in compliance with NASA JPL's  Safety-Critical Code standards.

#### Files
`main.cpp` - Start point of robot controller.

`config.h` - Robot specific configuration values.

`states.h` - Structure of state hierarchy.

#### Classes
`Robot` - Implementation of game logic.

#Implementation Details:
Here is the current status of the code:

####Robot Critical Systems
1. IR values from 12 independent sensors.
2. Collision detection from front bumpers.
3. Robot actuation of drive train.
4. Robot actuation of firing mechanism.
3. Timer based state transitions vs hanging code.

####Useful Robot Features
1. Feedback control for line based navigation.
