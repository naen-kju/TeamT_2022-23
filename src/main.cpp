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
  MaxThres = 75,
  MinThres = 0;

  int 
  Y1Thres = Remix.Axis3.position ( pct ),
  X1Thres = Remix.Axis4.position ( pct ),
  R1Thres = Remix.Axis2.position ( pct );

  int 
  Y2Thres = Wild.Axis3.position ( pct ),
  X2Thres = Wild.Axis4.position ( pct ),
  R2Thres = Wild.Axis2.position ( pct );

  while (true) 
  {
    Remix.ButtonA.pressed(RemixEnable);
    Wild.ButtonA.pressed(WildEnable);

    if (RemixControlEnabled() == true)
    {
      Thresholds ( Y1Thres, MaxThres, MinThres );
      Thresholds ( X1Thres, MaxThres, MinThres );
      Thresholds ( R1Thres, MaxThres, MinThres );
      LF.spin ( fwd, X1Thres + Y1Thres + R1Thres, pct );
      LB.spin ( fwd, -X1Thres - Y1Thres - R1Thres, pct );
      RF.spin ( fwd, X1Thres - Y1Thres - R1Thres, pct );
      RB.spin ( fwd, -X1Thres - Y1Thres - R1Thres, pct );
    }
    if (WildControlEnabled() == true)
    {
      Thresholds ( Y2Thres, MaxThres, MinThres );
      Thresholds ( X2Thres, MaxThres, MinThres );
      Thresholds ( R2Thres, MaxThres, MinThres );
      LF.spin ( fwd, X2Thres + Y2Thres + R2Thres, pct );
      LB.spin ( fwd, -X2Thres - Y2Thres - R2Thres, pct );
      RF.spin ( fwd, X2Thres - Y2Thres - R2Thres, pct );
      RB.spin ( fwd, -X2Thres - Y2Thres - R2Thres, pct );
    }
   
    wait ( 16 + ( 2 / 3 ), msec );
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