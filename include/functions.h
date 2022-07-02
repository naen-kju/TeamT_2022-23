#include "vex.h"

void preAutoCode ();
void autonCode ();
void userCode ();

#include "vex.h"

int 
LThres,
RThres,
MaxThres = 75,
MinThres = 0;

float 
liftGR    = 7,
mogoGR    = 5,
driveGR   = 5/3,
wheelDia  = 4,
wheelCirc = wheelDia * M_PI,

Clamp ( float value, float min, float max );

void 
SpinDrive ( int lVel, int rVel ),
StopAll ( bool LMs, bool RMs ),

TimeDrv( int Lvel, int Rvel, float milsec ),

DegDrv ( int vel, float dist, bool next ),
DegTurn ();