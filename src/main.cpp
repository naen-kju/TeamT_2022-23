#include "functions.h"

competition Match;

void pre_auton( void )
{
}

void auton ( void )
{

}

void user ( void )
{
  const int
  MaxThres { 75 },
  MinThres { 0 };

  int 
  Y1Thres, X1Thres, R1Thres,
  Y2Thres, X2Thres, R2Thres;

  while (true) 
  {
    Remix.ButtonA.pressed ( RemixEnable );
    Wild.ButtonA.pressed ( WildEnable );

    Y1Thres = Remix.Axis3.position ( pct ),
    X1Thres = Remix.Axis4.position ( pct ),
    R1Thres = Remix.Axis1.position ( pct );
 
    Y2Thres = Wild.Axis3.position ( pct ),
    X2Thres = Wild.Axis4.position ( pct ),
    R2Thres = Wild.Axis1.position ( pct );

    if ( RemixControlEnabled () == true )
    {
      Thresholds ( Y1Thres, MaxThres, MinThres );
      Thresholds ( X1Thres, MaxThres, MinThres );
      Thresholds ( R1Thres, MaxThres, MinThres );
      MecanumSpin ( Y1Thres, X1Thres, R1Thres );
    }
    if ( WildControlEnabled () == true )
    {
      Thresholds ( Y2Thres, MaxThres, MinThres );
      Thresholds ( X2Thres, MaxThres, MinThres );
      Thresholds ( R2Thres, MaxThres, MinThres );
      MecanumSpin ( Y2Thres, X2Thres, R2Thres );
    }
   
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