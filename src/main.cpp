#include "functions.h"

competition Match;

// Code for robot setup
void pre_auton( void )
{
  vexcodeInit();

  // Only allows color dection from optical
  Colour.gestureDisable();

  // Takes 3 seconds to calibrate inertial
  Gyro.calibrate();

  // Prints out auton selection on brain and enables auton selection thru controller 
  while ( program == false)
  {
    conWaitAuton();
    wait ( coolDown, msec );
  }
}

// Code for Autonomous Control period
void auton ( void )
{
  if ( AutoNum == 1 ) // Match Blue Left Button Up
  {
    Colour.setLightPower(25);
    MoveFwdDeg(75, -2, 0, true );
    Rolling( 30, 500, reverse );
    RollingCB(20);
    MoveFwdDeg(75, 4, 0, true );
    TurnRDeg(50, 45);
    FlyW.spin(fwd, 67, pct);
    MoveFwdDeg(125, 50, 0 , true );
    TurnLDeg(30, 75);
    wait ( 2000, msec );
    Indexer1(); wait( 1250, msec );
    Indexer1(); wait( 1000, msec );
    FlyW.stop();

  }

  else if ( AutoNum == 2 ) // Match Blue Right Button Right
  {
    Colour.setLightPower(25);
    MoveFwdDeg ( 50, 0, 29, true);
    MoveFwdDeg(75, -8, 0, true );
    Rolling( 30, 500, reverse );
    RollingCB(20);
    MoveFwdDeg(75, 4, 0, true );
    TurnLDeg(50, 45);
    FlyW.spin(fwd, 67, pct);
    MoveFwdDeg(125, 50, 0 , true );
    TurnRDeg(30, 75);
    wait ( 2000, msec );
    Indexer1(); wait( 2000, msec );
    Indexer1(); wait( 1000, msec );
    FlyW.stop();
  }

  else if ( AutoNum == 3 ) // Match Red Left Button Down
  {
    Colour.setLightPower(25);
    MoveFwdDeg(75, -2, 0, true );
    Rolling( 30, 500, reverse );
    RollingCR(20);
    MoveFwdDeg(75, 4, 0, true );
    TurnRDeg(50, 45);
    FlyW.spin(fwd, 65, pct);
    MoveFwdDeg(125, 50, 0 , true );
    TurnLDeg(30, 73);
    wait ( 2000, msec );
    Indexer1(); wait( 2000, msec );
    Indexer1(); wait( 1000, msec );
    FlyW.stop();
  }

  else if ( AutoNum == 4) // Match Red Right
  {
    Colour.setLightPower(25);
    MoveFwdDeg ( 50, 0, 29, true);
    MoveFwdDeg(75, -8, 0, true );
    Rolling( 30, 500, reverse );
    RollingCR(20);
    MoveFwdDeg(75, 4, 0, true );
    TurnLDeg(50, 45);
    FlyW.spin(fwd, 67, pct);
    MoveFwdDeg(125, 50, 0 , true );
    TurnRDeg(30, 75);
    wait ( 2000, msec );
    Indexer1(); wait( 2000, msec );
    Indexer1(); wait( 1000, msec );
    FlyW.stop();
  }

  else if ( AutoNum == 5) // Skills Left
  {
    // BLANK
  }

  else if ( AutoNum == 6) // Skills Right
  {
    // BLANK
  }

  else if ( AutoNum == 7) // Test code
  {
    // BLANK
  }

  else if ( AutoNum == 8) // NaN
  {
    // BLANK
  }
}

// Code for User Control period
void user ( void )
{
  SetMec ( coast );

  // Loop to prevent driver control from exiting
  while (true)
  {
    // Enables Basic Drivetrain control
    Y1Thres = Con1.Axis3.position ( pct ),
    X1Thres = Con1.Axis4.position ( pct ),
    R1Thres = Con1.Axis1.position ( pct );
    MecSpin ( Y1Thres, X1Thres, R1Thres );

    // Enables Intake Control
    IntRollSpin();

    // Enables FlyWheel Control
    FlySpin();

    // Roller w/ Optical
 //   RollColourSpin();


    // Used to save resources
    wait ( coolDown, msec );
  }
}

// Execution starting point
int main ()
{
  // Button presses callback functions for driver control

  // Increases Intake speed by 50% when pressed once or held down
  Con1.ButtonL2.pressed(IntRollF);

  // Opposite Intake control will stop and do the same
  Con1.ButtonL1.pressed(IntRollR);

  // Increases Flywheel speed by 20% when pressed once or held down
  Con1.ButtonR2.pressed(FlyF);

  // Opposite flywheel control stops
  Con1.ButtonR1.pressed(FlyS);

  // Experimental roller control through optical sensor, stops when team color is seen
  Con1.ButtonUp.pressed(RollerControl);

  // Extends indexer once when pressed once 
  Con1.ButtonA.pressed(Indexer1);

  // Extends indexer trice when pressed once
  Con1.ButtonLeft.pressed(Indexer3);

  Con1.ButtonB.pressed(Expansion);

  // Initializing Robot Configuration
  vexcodeInit ();

  // Setup callbacks for auton and user control
  Match.autonomous ( auton );
  Match.drivercontrol ( user );

  // Set up callback for pre auton control
  pre_auton ();

  // While loop to prevent program from exiting
  while ( true )
  {
    wait ( 100, msec );
  }
}
