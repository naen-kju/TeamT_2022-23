#include "vex.h"

void userCode () 
{
  while (true) 
  {
    
    LF.spin ( fwd, Remix.Axis3.position ( pct ), pct );
    LB.spin ( fwd, Remix.Axis3.position ( pct ), pct );
    RF.spin ( fwd, Remix.Axis3.position ( pct ), pct );
    RB.spin ( fwd, Remix.Axis3.position ( pct ), pct );

    wait ( 16 + ( 2 / 3 ), msec );
  }
}