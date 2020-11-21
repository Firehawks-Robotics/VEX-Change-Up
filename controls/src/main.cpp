/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       main.cpp                                                        */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thurs Oct 22 2020                                               */
/*    Description:  Change Up Main                                                  */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"
#include <math.h>

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// neWheel              motor         11             (northeast wheel)
// nwWheel              motor         20             (northwest wheel)
// seWheel              motor         10             (southeast wheel)
// swWheel              motor         9              (southwest wheel)
// intakeRight          motor         1               
// intakeLeft           motor         8               
// liftLeft             motor         5               
// liftRight            motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----


/* CONTROLS MAPPING:
 * Omnidirectional Movement - Left Analog Stick
 * Turn Left/Right - Right Analog Stick
 * Intake In - Front Right Bumper (R1)
 * Intake Out - Back Right Bumper (R2)
 * Lift/Shoot Up - Front Left Bumper (L1)
 * Lift/Shoot Down - Back Left Bumper (L2)
 * Toggle Mode - Right
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugMenuTemp.h"
#include "functionality.h"

int main() {

    vexcodeInit();

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    //Values of all axes are needed so that wheel velocity can be modified accordingly
    intakeIn.pressed([](){intake(-1);});
    intakeOut.pressed([](){intake(1);});
    intakeIn.released([](){intake(0);});
    intakeOut.released([](){intake(0);});

    liftUp.pressed([](){lift(1);});
    liftDown.pressed([](){lift(-1);});
    liftUp.released([](){lift(0);});
    liftDown.released([](){lift(0);});

    toggleMode.pressed(modeToggled);

    //Movement is handled by an infinite while loop to ensure that the movement gets updated like it should
    //Sometimes the axis.changed event does not happen even if the axis value does change. Thus, our current solution:
    while(1) { 
        movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());
    }

    //The debug screen is updated on every event
}
