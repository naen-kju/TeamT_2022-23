#include "vex.h"
#include "functions.h"

competition Match;

// Pre Auton code in function in auton.cpp
void pre_auton( void )
{
  PreAutonCall();
}

// Auton code in function in auton.cpp
void auton ( void )
{
  AutonCall();
}

// User code in usercontrol.cpp
void user ( void )
{
  UserCall();
}

// Program execution begins here
int main ()
{
  // Usercontrol buttons in function
  MainUserCall();

  // Initializing Robot Configuration
  vexcodeInit ();

  // Setup callbacks for auton and user control
  Match.autonomous ( auton );
  Match.drivercontrol ( user );

  // Set up callback for pre auton control
  pre_auton ();

  // While loop to prevent program from exiting
  while ( true )
  {
    wait ( 100, msec );
  }
}