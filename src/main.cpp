// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Comp;

void pre_auton(void) 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Insert code here
}


void auton(void) 
{
  // Insert code here
}


void driver(void) 
{
  while (true) 
  {
    // Insert code here

    wait(20, msec);
  }
}


int main() 
{
  // Set up callbacks for autonomous and driver control periods.
  Comp.autonomous(auton);
  Comp.drivercontrol(driver);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}
