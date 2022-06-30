#include "vex.h"

void pre_auton ( void ) 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit ();
  
}

void auton ( void ) 
{
  
}

void driver ( void ) 
{
  while (true) 
  {
    
    LFMtr.spin ( fwd, Controller1.Axis3.position ( pct ), pct );
    LBMtr.spin ( fwd, Controller1.Axis3.position ( pct ), pct );
    RFMtr.spin ( fwd, Controller1.Axis3.position ( pct ), pct );
    RBMtr.spin ( fwd, Controller1.Axis3.position ( pct ), pct );

    wait ( 16 + ( 2 / 3 ), msec );
  }
}

int main () 
{
  // Set up callbacks for autonomous and driver control periods.
  Comp.autonomous ( auton );
  Comp.drivercontrol ( driver );

  // Run the pre-autonomous function.
  pre_auton ();

  // Prevent main from exiting with an infinite loop.
  while ( true ) 
  {
    wait ( 100, msec );
  }
}