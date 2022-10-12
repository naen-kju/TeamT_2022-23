#include "vex.h"

brain Cortex;

controller Con1 = controller ( primary );

motor LF = motor ( PORT19, ratio6_1, false );
motor RF = motor ( PORT11, ratio6_1, true );
motor LB = motor ( PORT10, ratio6_1, false );
motor RB = motor ( PORT2, ratio6_1, true );

motor Fly = motor ( PORT4, ratio6_1, false) ;
motor Intake = motor ( PORT3, ratio18_1, true) ;
motor Roll = motor ( PORT16, ratio18_1, false );

inertial Gyro = inertial ( PORT7 );
gps Nav = gps ( PORT6, 0, 0, mm, 0, right );
optical Colour = optical ( PORT8, true );
distance Dist = distance ( PORT9 );

bool RemoteControlCodeEnabled = true;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void vexcodeInit ( void )
{

}
