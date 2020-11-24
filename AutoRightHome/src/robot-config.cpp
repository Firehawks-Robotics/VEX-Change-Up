/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       robot-config.cpp                                                */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Configuration Implementation                              */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"
#include "debugMenuTemp.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors (Need to update Ports)
motor neWheel = motor(PORT11, ratio36_1, true);
motor nwWheel = motor(PORT20, ratio36_1, true);
motor seWheel = motor(PORT10, ratio36_1, true);
motor swWheel = motor(PORT9, ratio36_1, true);
motor intakeLeft = motor(PORT1, ratio36_1, false);
motor intakeRight = motor(PORT8, ratio36_1, true);
motor liftLeft = motor(PORT5, ratio36_1, false);
motor liftRight = motor(PORT7, ratio36_1, true);

// Controls
vex::controller::axis omnidirectionalY = mainCon.Axis3;
vex::controller::axis omnidirectionalX = mainCon.Axis4;

vex::controller::axis turning = mainCon.Axis1;

vex::controller::button intakeIn = mainCon.ButtonR1; //Front
vex::controller::button intakeOut = mainCon.ButtonR2; //Back

vex::controller::button liftUp = mainCon.ButtonL1; //Front
vex::controller::button liftDown = mainCon.ButtonL2; //Back

vex::controller::button toggleMode = mainCon.ButtonRight;

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
    //Inititalize the default velocity for motors with unchanging velocities
    intakeLeft.setVelocity(200, rpm);
    intakeRight.setVelocity(200, rpm);

    liftLeft.setVelocity(200, rpm);
    liftRight.setVelocity(200, rpm);

    debugMenuController(); //Put stuff on debug screen
}