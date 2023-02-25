#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vex.h"

/*  FUNCTIONS FOR FUNCTIONS
*/
  // Function to control overall drivetrain movement
  void TankSpin ( float Y, float R )
  {
    LF.spin ( fwd, Y - R, pct );
    LB.spin ( fwd, Y - R, pct );
    RF.spin ( fwd, Y + R, pct );
    RB.spin ( fwd, Y + R, pct );
  }

  // Function to set brake type for drivetrain motors
  void SetTank ( brakeType type )
  {
    LF.setBrake ( type );
    LB.setBrake ( type );
    RF.setBrake ( type );
    RB.setBrake ( type );
  }

  // Function to clip a value between a min and max range
  float Clip( float value, float min, float max )
  {
    if(value > max)
    {   return max;   }
    else if(value < min)
    {   return min;   }
    else
    {   return value; }
  }

  // Code for PID
  double PID(double TS, double CS, double kP, double kI, double kD )
  {
    double Error, Integral, Derivative, PrevError, Output;
    Error = TS - CS;
    Integral += Error;
    Derivative = Error - PrevError;
    Output = kP*Error + kI*Integral + kD*Derivative;
    return Output;
  }

/*  FUNCTIONS FOR USERCONTROL
*/
  // Function to control intake roller in user control
  int intRollSpeed = 0;
  void IntRolling () 
  {
    while (Con1.ButtonL2.pressing())
    {
      if (intRollSpeed < 0)
      {
        intRollSpeed = 0;
      }
      else if ( intRollSpeed < 25)
      {
        intRollSpeed = 25;
      }
      else
      {
        intRollSpeed = 100;
      }
      IntRoll.spin(fwd, intRollSpeed, pct);
      wait (150, msec);
    }
    while (Con1.ButtonL1.pressing())
    {
      if (intRollSpeed > 0)
      {
        intRollSpeed = 0;
      }
      else if ( intRollSpeed > -25)
      {
        intRollSpeed = -25;
      }
      else
      {
        intRollSpeed = -100;
      }
      IntRoll.spin(fwd, intRollSpeed, pct);
      wait (150, msec);
    }
  }

  // Function to control flywheel in user control
  int flySpeed = 0;
  void FlySpinning()
  {
    while (Con1.ButtonR2.pressing())
    {
      if (flySpeed == 0)
      {
        flySpeed = 65;
      }
      else
      {
        flySpeed += 5;
      }
      FlyW.spin(fwd, flySpeed, pct);
      wait (150, msec);
    }
    while (Con1.ButtonR1.pressing())
    {
      flySpeed = 0;
      FlyW.stop();
      wait (150, msec);
    }
  }
  
  // Function to control indexer in user control
  void Indexer()
  {
    while (Con1.ButtonA.pressing())
    {
      Index.spinFor ( fwd, 180, deg, 150, rpm );
      wait(300, msec);
    }
  }

  // Function to control pneumatic expansion in user control
  void Expansion()
  {
    if ( Con1.ButtonB.pressing())
    {
      wait(1000, msec);
      if ( Con1.ButtonB.pressing() )
      {
        expand0.set(true);
        expand1.set(true);
      }
    }
  }

/*  FUNCTIONS FOR AUTON
*/
  // Function to move the robot forward a certain distance in degrees
  void MoveFwdDeg ( float vel, float Y, bool next )
  {
    float
    driveGR = 60/84,
    wheelDia = 4,
    wheelCirc = wheelDia * M_PI,

    dist = (Y / wheelCirc)*360;
    LF.spinFor( fwd, dist, degrees, vel, rpm, false );
    RF.spinFor( fwd, dist, degrees, vel, rpm, false );
    LB.spinFor( fwd, dist, degrees, vel, rpm, false );
    RB.spinFor( fwd, dist, degrees, vel, rpm, next );
  }

  // Function to turn the robot right a certain number of degrees
  void TurnRDeg ( float vel, float degr )
  {
    SetTank ( hold );
    while ( Gyro.rotation( deg) - degr <= 0 )
    {
      TankSpin ( 0, vel );
      wait (5.0, msec);
    }
    TankSpin ( 0, 0 );
    Gyro.resetRotation();
  }

  // Function to turn the robot left a certain number of degrees
  void TurnLDeg ( float vel, float degr )
  {
    SetTank ( hold );
    while ( Gyro.rotation( deg) + degr >= 0 )
    {
      TankSpin ( 0, -vel );
      wait ( 5.0, msec );
    }
    TankSpin ( 0, 0 );
    Gyro.resetRotation();
  }

  // Function to control flywheel in autonomous
  void Flying ( float Vel, bool Stop, float Time )
  {
    FlyW.spin(fwd, Vel, pct);
    if ( Stop == true)
    {
      wait ( Time, msec );
      FlyW.stop();
    }
  }

  // Function to control intake in autonomous
  void Intaking ( float Vel, bool Stop, float Time )
  {
    IntRoll.spin ( fwd, Vel, rpm );
    if ( Stop == true )
    {
      wait ( Time, msec );
      IntRoll.stop();
    }
  }

  // Function to control intake roller in autonomous
  void Rolling( float vel, float time, directionType dir )
  {
    IntRoll.spin(dir, vel, pct );
    wait ( time, msec );
    IntRoll.stop();
  }

  // Function to control intake roller in autonomous to roll to red
  void RollingCB( float vel )
  {
    Rolling( 100, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    waitUntil(Colour.color() == blue);
    IntRoll.stop();
  }

  // Function to control intake roller in autonomous to roll to blue
  void RollingCR( float vel )
  {
    Rolling( 100, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    waitUntil(Colour.color() == red);
    IntRoll.stop();
  }

/*  FUNCTIONS FOR MAIN.CPP
*/
  // Function to control user control tasks
  void MainUserCall()
  {
    Con1.ButtonB.pressed(Expansion);
    Con1.ButtonL2.pressed(IntRolling);
    Con1.ButtonL1.pressed(IntRolling);
    Con1.ButtonR2.pressed(FlySpinning);
    Con1.ButtonR1.pressed(FlySpinning);
    Con1.ButtonA.pressed(Indexer);
    Con1.ButtonB.pressed(Expansion);
  }

  // Function to determine which autonomous mode to run
  int AutoNum = 0;
  void ConAuton ()
  {
    while ( AutoNum == 0 )
    {
      if ( Con1.ButtonUp.pressing() ) // Match Blue Left
      {
        AutoNum = 1;
        Con1.Screen.print("Match Blue Left");
      }
      else if ( Con1.ButtonRight.pressing() ) // Match Blue Right
      {
        AutoNum = 2;
        Con1.Screen.print("Match Blue Right");

      }
      else if ( Con1.ButtonDown.pressing() ) // Match Red Left
      {
        AutoNum = 3;
        Con1.Screen.print("Match Red Left");
      }
      else if ( Con1.ButtonLeft.pressing() ) // Match Red Right
      {
        AutoNum = 4;
        Con1.Screen.print("Match Red Right");
      }
      else if ( Con1.ButtonX.pressing() ) // Skills Left
      {
        AutoNum = 5;
        Con1.Screen.print("Skills Left");
      }
      else if ( Con1.ButtonA.pressing() ) // Skills Right
      {
        AutoNum = 6;
        Con1.Screen.print("Skills Right");
      }
      else if ( Con1.ButtonB.pressing() ) // Testing
      {
        AutoNum = 7;
        Con1.Screen.print("Testing");
      }
      else if ( Con1.ButtonY.pressing() ) // NaN
      {
        AutoNum = 8;
        Con1.Screen.print("NaN");
      }
      wait (5.0, msec);
    }
  }

  // Function to call autonomous tasks
  void AutonCall()
  {
    if ( AutoNum == 1 ) // Match Blue Left Button Up
    {
      MoveFwdDeg(50, -3, true);
      Rolling( 20, 500, reverse );
      MoveFwdDeg(30, 3, true);
      TurnLDeg(30, 3.5);
      Flying(85, false, 0);
      wait (3500, msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(750,msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(500,msec);
      Flying(0, false, 0);
    }

    else if ( AutoNum == 2 ) // Match Blue Right Button Right
    {
      MoveFwdDeg(50, -18, true);
      TurnRDeg(30, 90);
      MoveFwdDeg(50, -5, true);
      Rolling( 20, 500, reverse );
      MoveFwdDeg(30, 3, true);
      TurnRDeg(30, 1);
      Flying(85, false, 0);
      wait (3500, msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(1000,msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(500,msec);
      Flying(0, false, 0);
    }

    else if ( AutoNum == 3 ) // Match Red Left Button Down
    {
      MoveFwdDeg(50, -3, true);
      Rolling( 20, 500, reverse );
      MoveFwdDeg(30, 3, true);
      TurnLDeg(30, 3.5);
      Flying(85, false, 0);
      wait (3500, msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(750,msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(500,msec);
      Flying(0, false, 0);
    }

    else if ( AutoNum == 4) // Match Red Right
    {
      MoveFwdDeg(50, -3, true);
      Rolling( 20, 500, reverse );
      MoveFwdDeg(30, 3, true);
      TurnLDeg(30, 3.5);
      Flying(85, false, 0);
      wait (3500, msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(750,msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(500,msec);
      Flying(0, false, 0);
    }

    else if ( AutoNum == 5 || AutoNum == 0 ) // Skills Left
    {
      MoveFwdDeg(50, -3, true);
      Rolling( 20, 500, reverse );
      MoveFwdDeg(30, 3, true);
      TurnLDeg(30, 3.5);
      Flying(85, false, 0);
      wait (3500, msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(750,msec);
      Index.spinFor(fwd, 180, deg, 200, rpm ); wait(500,msec);
      Flying(0, false, 0);
      TurnLDeg(30, 45);
      expand0.set(true);
      expand1.set(true);
    }

    else if ( AutoNum == 6 ) // Skills Right
    {
      // BLANK
    }

    else if ( AutoNum == 7 ) // Test code
    {

    }

    else if ( AutoNum == 8 ) // NaN
    {
      // BLANK
    }
  }

  // Function to call user control tasks
  void UserCall()
  {
    SetTank ( coast );
    while (true)
    {
      int 
      Y1Thres = Con1.Axis3.position ( pct ),
      R1Thres = Con1.Axis1.position ( pct )/2.5;
      TankSpin ( Y1Thres, R1Thres );
      wait ( 5, msec );
    }
  }

  // Function to run code before autonomous tasks
  void PreAutonCall()
  {
    vexcodeInit();

    // Takes 3 seconds to calibrate inertial
    Gyro.calibrate();

    expand0.set(false);
    expand1.set(false);

    // Prints out auton selection on brain and enables auton selection thru controller 
    ConAuton();
  }

#endif  // FUNCTIONS_H