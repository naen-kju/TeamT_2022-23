#include "vex.h"

brain Cortex;

controller Con1 = controller ( primary );

motor LF = motor ( PORT19, ratio18_1, true );
motor RF = motor ( PORT11, ratio18_1, false );
motor LB = motor ( PORT9, ratio18_1, true );
motor RB = motor ( PORT3, ratio18_1, false );

motor Fly = motor ( PORT6, ratio6_1, false) ;
motor Intake = motor ( PORT4, ratio18_1, true) ;
motor Roll = motor ( PORT16, ratio18_1, false );

inertial Gyro = inertial ( PORT7 );
/*
gps Nav = gps ( PORT0, 0, 0, mm, 0, right );
optical Colour = optical ( PORT0, true );
distance Dist = distance ( PORT0 );
*/

bool RemoteControlCodeEnabled = true;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void vexcodeInit ( void )
{

}
