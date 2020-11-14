/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       robot-config.cpp                                                */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Configuration Implementation                              */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors (Need to update Ports)
motor neWheel = motor(PORT1, ratio36_1, false);
motor nwWheel = motor(PORT1, ratio36_1, true);
motor seWheel = motor(PORT1, ratio36_1, false);
motor swWheel = motor(PORT1, ratio36_1, true);
motor consumeLeft = motor(PORT1, ratio36_1, false);
motor consumeRight = motor(PORT1, ratio36_1, true);
motor liftLeft = motor(PORT1, ratio36_1, false);
motor liftRight = motor(PORT1, ratio36_1, true);

// Controls
vex::controller::axis omnidirectionalY = mainCon.Axis3;
vex::controller::axis omnidirectionalX = mainCon.Axis2;

vex::controller::axis turning = mainCon.Axis1;

vex::controller::button intakeIn = mainCon.ButtonR1;
vex::controller::button intakeOut = mainCon.ButtonL1;

vex::controller::button liftUp = mainCon.ButtonA;
vex::controller::button liftDown = mainCon.ButtonB;

vex::controller::button toggleMode = mainCon.ButtonRight;

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}