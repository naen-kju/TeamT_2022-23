using namespace vex;

// A global instance of competition
competition Comp;

extern brain Cortex;

// VEXcode devices
extern motor LFMtr;
extern motor LBMtr;
extern motor RFMtr;
extern motor RBMtr;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit ( void );