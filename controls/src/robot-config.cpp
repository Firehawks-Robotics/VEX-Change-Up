#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors (Need to update Ports)
motor neWheel = motor(PORT10, ratio18_1, false);
motor nwWheel = motor(PORT2, ratio36_1, false);
motor seWheel = motor(PORT3, ratio36_1, false);
motor swWheel = motor(PORT4, ratio36_1, false);
motor consumeLeft = motor(PORT5, ratio36_1, false);
motor consumeRight = motor(PORT6, ratio36_1, false);
motor liftLeft = motor(PORT7, ratio36_1, false);
motor liftRight = motor(PORT8, ratio36_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}