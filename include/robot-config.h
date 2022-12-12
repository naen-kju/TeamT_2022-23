using namespace vex;

using signature = vision::signature;
using code = vision::code;

extern brain Cortex;

extern controller Con1;

extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;

extern motor Fly0;
extern motor Fly1;
extern motor_group FlyW;

extern motor IntRoll;
extern motor Index;

extern digital_out expand0;
extern digital_out expand1;

extern inertial Gyro;
extern optical Colour;
/*
extern gps Nav;
extern distance Dist;
*/

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void  vexcodeInit ( void );
