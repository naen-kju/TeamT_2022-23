#include "vex.h"

/*---------------------------/
Global Variables for functions
/---------------------------*/
  const float
    // Sets the gear ratio for the drivetrain
    driveGR = 1,

    // Sets the wheels' diameter (4 inches)
    wheelDia = 4,

    // Sets the wheels' circumfrence based on diameter
    wheelCirc = wheelDia * M_PI,

    // Finds the radians from degrees
    Deg2Rad = M_PI/180,

    // Finds the degrees from radians
    Rad2Deg = 180/M_PI,

    // Time for wait in msec, used to save resources between other functions
    coolDown = 5.0;

  bool
    // On/Off switch for forwards and reverse direction for intake control
    IntakeOnF = false,
    IntakeOnR = false,
    // On/Off switch for flywheel control
    FlyOnF = false,
    FlyOnS = false,
    // On/Off switch for flywheel control
    RollOnF = false,
    RollOnR = false,

    // Setup for different autons
    Auto1 = false,
    Auto2 = false,
    Auto3 = false,
    Auto4 = false;

  float
    Y1Thres,
    X1Thres,
    R1Thres;

/*----------------------/
General functions for all
/----------------------*/
  // Control for spining in mecanum directions
  void MecSpin ( float Y, float X, float R )
  {
    LF.spin ( fwd, Y + X + R, pct );
    LB.spin ( fwd, Y - X + R, pct );
    RF.spin ( fwd, Y - X - R, pct );
    RB.spin ( fwd, Y + X - R, pct );
    wait ( coolDown, msec);
  }

  // Sets the brake type for the four drivetrain motors
  void SetMec ( brakeType type )
  {
    LF.setBrake ( type );
    LB.setBrake ( type );
    RF.setBrake ( type );
    RB.setBrake ( type );
  }
  void SetFly ( brakeType type )
  {
    Fly.setBrake ( type );
  }
  void SetInt ( brakeType type )
  {
    Intake.setBrake ( type );
  }

/*--------------------/
Functions for void user
/--------------------*/
  // Switches fwd to opposite of current, and rev to off for intake spin when called
  void IntakeF ()
  {
    IntakeOnF = !IntakeOnF;
    IntakeOnR = false;
  }
  // Switches rev to opposite of current, and fwd to off for intake spin when called
  void IntakeR ()
  {
    IntakeOnR = !IntakeOnR;
    IntakeOnF = false;
  }
  // Spins intake either fwd or rev, based on variable bool value when called
  void IntakeSpin()
  {
    if ( IntakeOnF == true )
    {
      Intake.spin(fwd, 100, pct);
    }
    else if ( IntakeOnR == true )
    {
      Intake.spin(reverse, 100, pct);
    }
    else
    {
      Intake.stop();
    }
    wait ( coolDown, msec );
  }

  // Switches fwd to opposite, and rev to off for flywheel spin when called
  void FlyF ()
  {
    FlyOnF = !FlyOnF;
    FlyOnS = false;
  }
  void FlyS ()
  {
    FlyOnS = !FlyOnS;
    FlyOnF = false;
  }
  // Spins flywheel either fwd or rev, based on bool value when called
  void FlySpin()
  {
    if ( FlyOnF == true )
    {
      Fly.spin ( fwd, 100, pct );
    }
    else if ( FlyOnS == true )
    {
      Fly.spin ( fwd, 85, pct );
    }
    else
    {
      Fly.stop();
    }
    wait ( coolDown, msec );
  }

  void RollF ()
  {
    RollOnF = !RollOnF;
    RollOnR = false;
  }
  void RollR ()
  {
    RollOnR = !RollOnR;
    RollOnF = false;
  }
  void RollSpin()
  {
    if ( RollOnF == true )
    {
      Roll.spin ( fwd, 100, pct );
    }
    else if ( RollOnR == true )
    {
      Roll.spin (reverse, 100, pct );
    }
    else
    {
      Roll.stop();
    }
  }


/*---------------------/
Functions for void auton
/---------------------*/

  void MoveFwdDeg ( float vel, float Y, float X, bool next )
  {
    float rY = ((Y/wheelCirc)*driveGR)*360;
    float rX = ((X/wheelCirc)*driveGR)*360;
    LF.spinFor( fwd, rY + rX, deg, vel, rpm, false );
    RF.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    LB.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    RB.spinFor( fwd, rY + rX, deg, vel, rpm, next );
    wait ( coolDown, msec );
  }

  void TurnRDeg ( float vel, float degr )
  {
    SetMec ( hold );
    while ( Gyro.rotation( deg) - degr <= 0 )
    {
      MecSpin ( 0, 0, vel );
      wait (coolDown, msec);
    }
    MecSpin ( 0, 0, 0 );
    Gyro.resetRotation();
    wait ( coolDown, msec );
  }
  void TurnLDeg ( float vel, float degr )
  {
    SetMec ( hold );
    while ( Gyro.rotation( deg) + degr >= 0 )
    {
      MecSpin ( 0, 0, -vel );
    }
    MecSpin ( 0, 0, 0 );
    Gyro.resetRotation();
    wait ( coolDown, msec );
  }

  void Flying ( float Vel, bool Stop, float Time )
  {
    Fly.spin(fwd, Vel, rpm);
    if ( Stop == true)
    {
      wait ( Time, msec );
      Fly.stop();
    }
    wait ( coolDown, msec );
  }

  void Intaking ( float Vel, bool Stop, float Time )
  {
    Intake.spin ( fwd, Vel, rpm );
    if ( Stop == true )
    {
      wait ( Time, msec );
      Intake.stop();
    }
    wait ( coolDown, msec );
  }

  void Rolling (float Vel, bool Stop, float Time )
  {
    Roll.spin (fwd, Vel, rpm );
    if ( Stop == true )
    {
      wait ( Time, msec );
      Roll.stop();
    }
    wait ( coolDown, msec );
  }
