#include "vex.h"

using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Cortex;

// VEXcode device constructors
motor LF = motor ( PORT11, ratio18_1, false );
motor LB = motor ( PORT12, ratio18_1, false );
motor RF = motor ( PORT20, ratio18_1, true );
motor RB = motor ( PORT19, ratio18_1, true );
motor Fly = motor ( PORT5, ratio6_1, false);
controller Remix = controller ( primary );
controller Wild = controller ( partner );

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void )
{
  // nothing to initialize
}
