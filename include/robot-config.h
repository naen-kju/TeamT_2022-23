using namespace vex;

extern brain Cortex;

// VEXcode devices
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor Fly;
extern controller Remix;
extern controller Wild;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit ( void );