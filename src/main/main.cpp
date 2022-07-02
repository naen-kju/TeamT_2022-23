#include "functions.h"

competition Match;

void pre_auton( void )
{
  preAutoCode();
}

void auton ( void )
{
  autonCode();
}

void user ( void )
{
  userCode();
}

int main () 
{
  // Set up callbacks for autonomous and driver control periods.
  Match.autonomous ( auton );
  Match.drivercontrol ( user );

  // Run the pre-autonomous function.
  pre_auton ();

  // Prevent main from exiting with an infinite loop.
  while ( true ) 
  {
    wait ( 100, msec );
  }
}