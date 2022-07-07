#include "functions.h"
#include "vision.h"

// Global Variables
  const float driveGR   = 5/3,
              wheelDia  = 4,
              wheelCirc = wheelDia * M_PI;

// Functions for userControl
  void Thresholds ( float Variable, int Max, int Min )
  {
    if (Variable > Max)
      { Variable = 100; }
    else if (Variable < -Max)
      { Variable = -100; }
    if (Variable < Min)
      { Variable = 0; }
    else if (Variable > -Min)
      { Variable = -0; }
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
    return RemixControl;
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

    wait(milsec, msec);

    StopAll(true, true);
  }

  void DegDrv(int vel, float dist, bool next)
  {
    float rot = ((dist/wheelCirc) * 360) * driveGR;
    SpinForDrive(rot, rot, vel, vel, next);
  }

  void DegTurn();