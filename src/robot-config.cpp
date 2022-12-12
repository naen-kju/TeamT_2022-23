#include "vex.h"

// Initialization for brain
brain Cortex;

// Constructor for controller
controller Con1 = controller ( primary );

// Constructor for drivetrain motors
// L and R is Left and Right, F and B is Front and Back
motor LF = motor ( PORT19, ratio18_1, true );
motor RF = motor ( PORT11, ratio18_1, false );
motor LB = motor ( PORT9, ratio18_1, true );
motor RB = motor ( PORT3, ratio18_1, false );

// Constructor for flywheel motors, combined both into one
motor Fly0 = motor ( PORT5, ratio6_1, false) ;
motor Fly1 = motor ( PORT18, ratio6_1, false) ;
motor_group FlyW = motor_group (Fly0, Fly1);

// Constructor for Intake/Roller combination motor
motor IntRoll = motor ( PORT12, ratio18_1, false) ;

// Constructor for indexer
motor Index = motor ( PORT10, ratio18_1, false );

digital_out expand0 = digital_out ( Cortex.ThreeWirePort.A ) ;
digital_out expand1 = digital_out ( Cortex.ThreeWirePort.B ) ;

// Constructor for inertial sensor
inertial Gyro = inertial ( PORT7 );

// Constructor for optical sensor
// Gesture tracking is disabled
optical Colour = optical ( PORT15, false );

/* Commented out/unused material
gps Nav = gps ( PORT0, 0, 0, mm, 0, right );
distance Dist = distance ( PORT0 );
*/

bool RemoteControlCodeEnabled = true;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void vexcodeInit ( void ) { }