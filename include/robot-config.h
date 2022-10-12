using namespace vex;

using signature = vision::signature;
using code = vision::code;

extern brain Cortex;

extern controller Con1;

extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;

extern motor Fly;
extern motor Intake;
extern motor Roll;

extern inertial Gyro;
extern gps Nav;
extern optical Colour;
extern distance Dist;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void  vexcodeInit ( void );
