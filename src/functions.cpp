#include "functions.h"
#include "vision.h"

// Global Variables for functions
  const float 
    // Sets the gear ratio for the drivetrain
    driveGR { 5/3 },
    // Sets the wheels' diameter (4 inches)
    wheelDia { 4 },
    // Sets the wheels' circumfrence based on diameter
    wheelCirc = wheelDia * M_PI,
    // Finds the radians from degrees
    Deg2Rad = M_PI/180,
    // Finds the degrees from radians
    Rad2Deg = 180/M_PI,
    // Time for wait in msec
    coolDown = 3.0;

// Functions for all.
  void MecanumSpin ( float Y, float X, float R )
  {
    LF.spin ( fwd, Y + X + R, pct );
    LB.spin ( fwd, Y - X + R, pct );
    RF.spin ( fwd, Y - X - R, pct );
    RB.spin ( fwd, Y + X - R, pct );
  }

  void StopAll(bool LFM, bool RFM, bool LBM, bool RBM)
  {
    if ( LFM == true )
    {
      LF.stop();
    }
    if ( RFM == true )
    {
      RF.stop();
    }
    if ( LBM == true )
    {
      LB.stop();
    }
    if ( RBM == true) 
    {
      RB.stop();
    }
  }

// Functions for user.
  void Thresholds ( float Variable, int Max )
  {
    if (Variable > Max)
      { Variable = 100; }
    else if (Variable < -Max)
      { Variable = -100; }
  }

  void DriverControl ( int Y, int X, int R, int Max )
  {
    Thresholds ( Y, Max );
    Thresholds ( X, Max );
    Thresholds ( R, Max );
    MecanumSpin ( Y, X, R );
  }

// Functions for auto.
  void MecanumMoveTheta ( float theta, float power, float stop)
  {
    float Y = sin(theta);
    float X = cos(theta);

    LF.spin ( fwd, (Y + X) * power, pct );
    RF.spin ( fwd, (Y - X) * power, pct );
    LB.spin ( fwd, (Y - X) * power, pct );
    RB.spin ( fwd, (Y + X) * power, pct );

    wait ( coolDown, msec);

    StopAll(true, true, true, true);

    wait ( coolDown,msec );
  }
