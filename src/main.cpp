#include "vex.h"
#include "functions.h"

competition Match;

// Pre Auton code in function in auton.cpp
void pre_auton( void )
{
  preautoncall();
}

// Auton code in function in auton.cpp
void auton ( void )
{
  autoncall();
}

// User code in usercontrol.cpp
void user ( void )
{
  usercall();
}

// Program execution begins here
int main ()
{
  // Usercontrol buttons in function
  mainusercall();

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