#include "functions.h"

brain  Cortex;

controller Remix = controller ( primary );
controller Wild = controller ( partner );
motor LF = motor ( PORT1, ratio18_1, false );
motor LB = motor ( PORT2, ratio18_1, false );
motor RF = motor ( PORT3, ratio18_1, true );
motor RB = motor ( PORT4, ratio18_1, true );
motor Fly = motor ( PORT5, ratio6_1, false);
inertial Vigour = inertial(PORT6);
gps Pilot = gps ( PORT7, 0, 0, mm, 0, right );
optical Chroma = optical ( PORT8, true );
distance Ambit = distance ( PORT9 );

bool RemoteControlCodeEnabled = true;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void vexcodeInit ( void )
{

}