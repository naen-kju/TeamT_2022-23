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
  void MoveFwdDeg ( float vel, float Y, float X, bool next )
  {
    const float
    driveGR = 1,
    wheelDia = 4,
    wheelCirc = wheelDia * M_PI;

    float rY = ((Y/wheelCirc)*driveGR)*360;
    float rX = ((X/wheelCirc)*driveGR)*360;
    LF.spinFor( fwd, rY + rX, deg, vel, rpm, false );
    RF.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    LB.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    RB.spinFor( fwd, rY + rX, deg, vel, rpm, next );
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
    Rolling( 30, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == red )
    {
      wait ( 5.0, msec);
    }    
    IntRoll.stop();
  }

  // Function to control intake roller in autonomous to roll to blue
  void RollingCR( float vel )
  {
    Rolling( 30, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == blue )
    {
      wait ( 5.0, msec);
    }    
    IntRoll.stop();
  }

/*  FUNCTIONS FOR MAIN.CPP
*/
  // Function to control user control tasks
  void MainUserCall()
  {
    Con1.ButtonB.pressed(Expansion);
  }

  // Function to determine which autonomous mode to run
  int ConAuton ()
  {
    int AutoNum = 0;

    while ( AutoNum == 0 )
    {
      if ( Con1.ButtonUp.pressing() ) // Match Blue Left
      {
        AutoNum = 1;
      }
      else if ( Con1.ButtonRight.pressing() ) // Match Blue Right
      {
        AutoNum = 2;
      }
      else if ( Con1.ButtonDown.pressing() ) // Match Red Left
      {
        AutoNum = 3;
      }
      else if ( Con1.ButtonLeft.pressing() ) // Match Red Right
      {
        AutoNum = 4;
      }
      else if ( Con1.ButtonX.pressing() ) // Skills Left
      {
        AutoNum = 5;
      }
      else if ( Con1.ButtonA.pressing() ) // Skills Right
      {
        AutoNum = 6;
      }
      else if ( Con1.ButtonB.pressing() ) // Testing
      {
        AutoNum = 7;
      }
      else if ( Con1.ButtonY.pressing() ) // NaN
      {
        AutoNum = 8;
      }
      wait (5.0, msec);
    }
    return AutoNum;
  }

  // Function to call autonomous tasks
  void AutonCall()
  {
    int AutoNum = ConAuton();
    if ( AutoNum == 1 ) // Match Blue Left Button Up
    {
      Colour.setLightPower(25);
      MoveFwdDeg(75, -2, 0, true );
      Rolling( 30, 500, reverse );
      RollingCB(20);
      MoveFwdDeg(75, 4, 0, true );
      TurnRDeg(50, 45);
      FlyW.spin(fwd, 60, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnLDeg(30, 80);
      MoveFwdDeg(75, 10, 0 , true );
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
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
      FlyW.spin(fwd, 60, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnRDeg(30, 70);
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
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
      FlyW.spin(fwd, 67, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnLDeg(30, 80);
      MoveFwdDeg(75, 10, 0 , true );
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
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
      TurnRDeg(30, 70);
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
      FlyW.stop();
    }

    else if ( AutoNum == 5 ) // Skills Left
    {
      // BLANK
    }

    else if ( AutoNum == 6 ) // Skills Right
    {
      // BLANK
    }

    else if ( AutoNum == 7 ) // Test code
    {
      // BLANK
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
      IntRolling();
      FlySpinning();
      Indexer();
      wait ( 5, msec );
    }
  }

  // Function to run code before autonomous tasks
  void PreAutonCall()
  {
    vexcodeInit();

    // Only allows color dection from optical
    Colour.gestureDisable();

    // Takes 3 seconds to calibrate inertial
    Gyro.calibrate();

    expand0.set(false);
    expand1.set(false);

    // Prints out auton selection on brain and enables auton selection thru controller 
    ConAuton();
  }

  