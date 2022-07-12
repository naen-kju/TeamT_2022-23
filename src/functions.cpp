#include "functions.h"
#include "vision.h"

// Global Variables for functions
  const float 
    // Sets the gear ratio for the drivetrain
    driveGR { 5/3 },
    // Sets the wheels' diameter (4 inches)
    wheelDia { 4 },
    // Sets the wheels' circumfrence based on diameter
    wheelCirc = wheelDia * M_PI; 
  
  float SpinnyReading ()
  {
    return Vigour.orientation(yaw, deg);
  }

// Functions for void User
  void Thresholds ( float Variable, int Max, int Min )
  {
    if (Variable > Max)
      { Variable = 100; }
    else if (Variable < -Max)
      { Variable = -100; }
  }

  bool RemixControl = true;

  void RemixEnable ()
  {
    RemixControl = !RemixControl;
  }

  bool RemixControlEnabled ()
  {
    return RemixControl;
  }

  bool WildControl = true;

  void WildEnable ()
  {
    WildControl = !WildControl;
  }

  bool WildControlEnabled ()
  {
    return WildControl;
  }

  void MecanumSpin ( float Y, float X, float R )
  {
    LF.spin ( fwd, Y + X + R, pct );
    LB.spin ( fwd, Y - X + R, pct );
    RF.spin ( fwd, Y - X - R, pct );
    RB.spin ( fwd, Y + X - R, pct );
  }

// Functions for auton.
  float Clamp ( float value, float min, float max )
  {
    if ( value > max )
    { return max; }
    else if(value < min)
    { return min; }
    else
    { return value; }
  }

  void SpinDrive(int lVel, int rVel)
  {
    LF.spin(fwd, lVel, rpm);
    LB.spin(fwd, lVel, rpm);

    RF.spin(fwd, rVel, rpm);
    RB.spin(fwd, rVel, rpm);
  }

  void StopAll(bool LMs, bool RMs)
  {
    if(LMs == true)
    {
      LF.stop();
      LB.stop();
    }

    if(RMs == true)
    {
      RF.stop();
      RB.stop();
    }
  }

  void SpinForDrive(float lDeg, float rDeg, int lVel, int rVel, bool next)
  {
    LF.spinFor(fwd, lDeg, deg, lVel, rpm, false);
    LB.spinFor(fwd, lDeg, deg, lVel, rpm, false);

    RB.spinFor(fwd, rDeg, deg, rVel, rpm, false);
    RB.spinFor(fwd, rDeg, deg, rVel, rpm, next);
  }

  void TimeDrv(int Lvel, int Rvel, float milsec)
  {
    SpinDrive(Lvel, Rvel);

    wait(milsec, sec);

    StopAll(true, true);
  }

  void DegDrv(int vel, float dist, bool next)
  {
    float rot = ((dist/wheelCirc) * 360) * driveGR;
    SpinForDrive(rot, rot, vel, vel, next);
  }

  void DegTurn( int vel, float rotation)
  {

  }