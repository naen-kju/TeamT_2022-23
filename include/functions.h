#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* FUNCTIONS FOR FUNCTIONS
*/
  // Function to control overall drivetrain movement
  void TankSpin ( float Y, float R );

  // Function to set brake type for drivetrain motors
  void SetTank ( vex::brakeType type );

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
  void MoveFwdDeg ( float vel, float Y );

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

  // Function to control intake roller in autonomous to roll to red
  void RollingCB( float vel );

  // Function to control intake roller in autonomous to roll to red
  void RollingCR( float vel );

/* FUNCTIONS FOR MAIN.CPP
*/
  // Function to control user control tasks
  void MainUserCall();

  // Function to determine which autonomous mode to run
  void ConAuton ();

  // Function to call autonomous tasks
  void AutonCall();

  // Function to call user control tasks
  void UserCall();
  
  // Function to run code before autonomous tasks
  void PreAutonCall();

#endif // FUNCTIONS_H