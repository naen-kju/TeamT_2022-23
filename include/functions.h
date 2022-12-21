#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* FUNCTIONS FOR FUNCTIONS
*/
  // Function to control drivetrain movement using joystick input
  void MecSpin ( float Y, float X, float R );

  // Function to set brake type for drivetrain motors
  void SetMec ( vex::brakeType type );

  // Function to clip a value between a min and max range
  float Clip( float value, float min, float max );

/* FUNCTIONS FOR USERCONTROL
*/
  // Function to control intake roller in user control
  void IntRolling();

  // Function to control flywheel in user control
  void FlySpinning();

  // Function to control indexer in user control
  void Indexer();

  // Function to control pneumatic expansion in user control
  void Expansion();

/* FUNCTIONS FOR AUTON
*/
  // Function to move the robot forward a certain distance in degrees
  void MoveFwdDeg ( float vel, float Y, float X, bool next );

  // Function to turn the robot right a certain number of degrees
  void TurnRDeg ( float vel, float degr );

  // Function to turn the robot left a certain number of degrees
  void TurnLDeg ( float vel, float degr );

  // Function to control flywheel in autonomous
  void Flying ( float Vel, bool Stop, float Time );

  // Function to control intake in autonomous
  void Intaking ( float Vel, bool Stop, float Time );

  // Function to control intake roller in autonomous
  void Rolling( float vel, float time, vex::directionType dir );

  // Function to control intake roller in autonomous to intake cubes
  void RollingCB( float vel );

  // Function to control intake roller in autonomous to release cubes
  void RollingCR( float vel );

/* FUNCTIONS FOR MAIN.CPP
*/
  // Function to control user control tasks
  void mainusercall();

  // Function to determine which autonomous mode to run
  int conAuton ();

  // Function to call autonomous tasks
  void autoncall();

  // Function to call user control tasks
  void usercall();
  
  // Function to run code before autonomous tasks
  void preautoncall();

#endif // FUNCTIONS_H