using namespace vex;

using signature = vision::signature;
using code = vision::code;

extern brain Cortex;

extern controller Remix;
extern controller Wild;

extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;

extern motor Fly;
extern motor Intake;
extern motor Angle;

extern inertial Vigour;
extern gps Pilot;
extern optical Chroma;
extern distance Ambit;

// Used to initialize code/tasks/devices added using tools in VEXcode Pro.
void  vexcodeInit ( void );
