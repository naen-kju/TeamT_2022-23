#include <vex.h>

/*//////////////////////////////////////////////////
  Functions below for other parts of code.
*///////////////////////////////////////////////////

int         LThres,                       // Sets threshold variable for the left joystick
            RThres;                       // Sets threshold variable for the right joystick

const int   MaxThres = 75,
            MinThres = 0;


const float liftGR    = 7,                // 7:1 Gear Ratio for back lift/scoop
            mogoGR    = 5,                // 5:1 Gear Ratio for front claw
            driveGR   = 5/3,              // 5:3 Gear Ratio for drive wheels
            wheelDia  = 4,                // Measurement in inches (in)
            wheelCirc = wheelDia * M_PI;  // The equation to find the circumfrence of a circle

// Locks variable from set min to set max
float Clamp(float value, float min, float max)
{
  if(value > max)
    return max;
  if(value < min) 
    return min;
  return value;
}

// Uses .spin command to program timed functions and for any other scenario
void SpinDriveMtrs(int lVel, int rVel)
{
  LFMtr.spin(fwd, lVel, rpm);
  LBMtr.spin(fwd, lVel, rpm);

  RFMtr.spin(fwd, rVel, rpm);
  RBMtr.spin(fwd, rVel, rpm);
}

// Stop all motors of robot for whatever scenario
void StopAll(bool LMtrs, bool RMtrs)
{
  if(LMtrs == true)
  { 
    LFMtr.stop();
    LBMtr.stop();
  }

  if(RMtrs == true)
  { 
    RFMtr.stop();
    RBMtr.stop();
  }
}

// Uses .spinFor command to program timed functions and for any other scenario
void SpinForDriveMtrs(float lDeg, float rDeg, int lVel, int rVel, bool next)
{
  LFMtr.spinFor(fwd, lDeg, deg, lVel, rpm, false); 
  LBMtr.spinFor(fwd, lDeg, deg, lVel, rpm, false);

  RBMtr.spinFor(fwd, rDeg, deg, rVel, rpm, false);
  RBMtr.spinFor(fwd, rDeg, deg, rVel, rpm, next);
}

/*//////////////////////////////////////////////////
  Functions for auton.h based on time
*///////////////////////////////////////////////////

void TimeDrv(int Lvel, int Rvel, float milsec)
{
  SpinDriveMtrs(Lvel, Rvel);

  wait(milsec, msec);
  
  StopAll(true, true);
}

/*//////////////////////////////////////////////////
  Functions for auton.h based on degree changes
*///////////////////////////////////////////////////

void DegDrv(int vel, float dist, bool next)
{
  float rot = ((dist/wheelCirc) * 360) * driveGR;
  SpinForDriveMtrs(rot, rot, vel, vel, next);
}

void DegTurn();

void DegClaw();

void DegScoop();