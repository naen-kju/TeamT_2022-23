#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// Include the vex namespace to use vex-specific functions and classes
using namespace vex;

// Declare global objects for the brain, controller, and drivetrain motors
extern brain Cortex;
extern controller Con1;
extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;

// Declare global objects for the flywheel motors and motor group
extern motor Fly0;
extern motor Fly1;
extern motor_group FlyW;

// Declare global objects for the intake roller and indexer motor
extern motor IntRoll;
extern motor Index;

// Declare global objects for the pneumatic solenoids
extern digital_out expand0;
extern digital_out expand1;

// Declare a global object for the inertial sensor
extern inertial Gyro;

// Declare a global object for the optical sensor
extern optical Colour;

/*
// Declare global objects for the GPS and distance sensor (commented out)
extern gps Nav;
extern distance Dist;
*/

// Declare a function to initialize all VEX V5 hardware and functions
void vexcodeInit ( void );

#endif // ROBOT_CONFIG_H