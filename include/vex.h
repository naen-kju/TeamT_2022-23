#ifndef VEX_H
#define VEX_H

// Include necessary header files
#include <math.h> // For math functions such as sin and cos
#include <cstdlib> // For general C++ functions
#include <stdio.h> // For input/output functions
#include <stdlib.h> // For general C functions
#include <string.h> // For string functions
#include <string> // For C++ string class
#include <cstring> // For C-style string functions

// Include VEX V5 headers
#include "v5.h" // Main VEX V5 header
#include "v5_vcs.h" // VEX V5 hardware control and sensor functions
#include "robot-config.h" // Robot configuration file

// Define a macro for waiting until a specific condition is met
#define waitUntil(condition)\
do {\
wait(5, msec);\
} while (!(condition))

// Define a macro for repeating a block of code a certain number of times
#define repeat(iterations)\
for (int iterator = 0; iterator < iterations; iterator++)

#endif // VEX_H