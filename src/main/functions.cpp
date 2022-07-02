#include "vex.h"

/*//////////////////////////////////////////////////
  Functions below for other parts of code.
*///////////////////////////////////////////////////

int LThres,                       // Sets threshold variable for the left joystick
    RThres,                       // Sets threshold variable for the right joystick
    MaxThres = 75,
    MinThres = 0;

float liftGR    = 7,
      mogoGR    = 5,
      driveGR   = 5/3,
      wheelDia  = 4,
      wheelCirc = wheelDia * M_PI;

// Locks variable from set min to set max
float Clamp ( float value, float min, float max )
{
  if ( value > max )
  { return max; }

  else if(value < min)
  { return min; }

  else
  { return value; }
}

// Uses .spin command to program timed functions and for any other scenario
void SpinDrive(int lVel, int rVel)
{
  LF.spin(fwd, lVel, rpm);
  LB.spin(fwd, lVel, rpm);

  RF.spin(fwd, rVel, rpm);
  RB.spin(fwd, rVel, rpm);
}

// Stop all motors of robot for whatever scenario
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

// Uses .spinFor command to program timed functions and for any other scenario
void SpinForDrive(float lDeg, float rDeg, int lVel, int rVel, bool next)
{
  LF.spinFor(fwd, lDeg, deg, lVel, rpm, false);
  LB.spinFor(fwd, lDeg, deg, lVel, rpm, false);

  RB.spinFor(fwd, rDeg, deg, rVel, rpm, false);
  RB.spinFor(fwd, rDeg, deg, rVel, rpm, next);
}

/*//////////////////////////////////////////////////
  Functions for auton.h based on time
*///////////////////////////////////////////////////

void TimeDrv(int Lvel, int Rvel, float milsec)
{
  SpinDrive(Lvel, Rvel);

  wait(milsec, msec);

  StopAll(true, true);
}

/*//////////////////////////////////////////////////
  Functions for auton.h based on degree changes
*///////////////////////////////////////////////////

void DegDrv(int vel, float dist, bool next)
{
  float rot = ((dist/wheelCirc) * 360) * driveGR;
  SpinForDrive(rot, rot, vel, vel, next);
}

void DegTurn();

void DegClaw();

void DegScoop();
