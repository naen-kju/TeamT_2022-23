#ifndef robot_config_h
#define robot_config_h

using namespace vex;

using signature = vision::signature;
using code = vision::code;

extern brain Cortex;

extern controller Remix;
extern controller Wild;
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor Fly;
extern inertial Vigour;
extern gps Pilot;
extern optical Chroma;
extern distance Ambit;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void  vexcodeInit ( void );

#endif