// Include VEX V5 header
#include "vex.h"

/* PORTS DEAD: 1
*/

// Declare global objects for the brain, controller, and drivetrain motors
brain Cortex;
controller Con1 = controller ( primary );
motor LF = motor ( PORT20, ratio18_1, true );
motor RF = motor ( PORT11, ratio18_1, false );
motor LB = motor ( PORT10, ratio18_1, true );
motor RB = motor ( PORT2, ratio18_1, false );

// Declare global objects for the flywheel motors and motor group
motor Fly0 = motor ( PORT4, ratio6_1, true) ;
motor Fly1 = motor ( PORT18, ratio6_1, true) ;
motor_group FlyW = motor_group (Fly0, Fly1);

// Declare global objects for the intake roller and indexer motor
motor IntRoll = motor ( PORT9, ratio6_1, false) ;
motor Index = motor ( PORT6, ratio18_1, false );

// Declare global objects for the pneumatic solenoids
digital_out expand0 = digital_out ( Cortex.ThreeWirePort.A ) ;
digital_out expand1 = digital_out ( Cortex.ThreeWirePort.B ) ;

// Declare a global object for the inertial sensor
inertial Gyro = inertial ( PORT8 );

// Declare a global object for the optical sensor
optical Colour = optical ( PORT14, false );

/*
// Declare global objects for the GPS and distance sensor (commented out)
gps Nav = gps ( PORT0, 0, 0, mm, 0, right );
distance Dist = distance ( PORT0 );
*/

// Flag to enable control over VEX Radio
bool RemoteControlCodeEnabled = true;

// Function to initialize code/tasks/devices added using tools in VEXcode Pro
void vexcodeInit ( void ) { }