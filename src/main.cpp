#include "functions.h"

competition Match;

void pre_auton( void )
{
}

void auton ( void )
{
  MecanumMoveTheta (  90, 1, 1000 );
  MecanumMoveTheta (  180, 1, 1000 );
  MecanumMoveTheta (  270, 1, 1000 );
  MecanumMoveTheta (  0, 1, 1000 );
}

void user ( void )
{
  const int
  MaxThres { 75 };

  int 
  Y1Thres, X1Thres, R1Thres,
  Y2Thres, X2Thres, R2Thres;

  while (true) 
  {
    Y1Thres = Remix.Axis3.position ( pct ),
    X1Thres = Remix.Axis4.position ( pct ),
    R1Thres = Remix.Axis1.position ( pct );
 
    Y2Thres = Wild.Axis3.position ( pct ),
    X2Thres = Wild.Axis4.position ( pct ),
    R2Thres = Wild.Axis1.position ( pct );
  
    DriverControl ( Y1Thres, X1Thres, R1Thres, MaxThres );
    DriverControl ( Y2Thres, X2Thres, R2Thres, MaxThres );
   
    wait ( 20, msec );
  }
}

int main () 
{
  vexcodeInit ();

  Match.autonomous ( auton );
  Match.drivercontrol ( user );

  pre_auton ();

  while ( true ) 
  {
    wait ( 100, msec );
  }
}