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
 * Intake In - Right Bumper
 * Intake Out - Left Bumper
 * Lift/Shoot Up - A
 * Lift/Shoot Down - B
 * Toggle Mode - Right
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugMenuTemp.h"
#include "functionality.h"

int main() {

    vexcodeInit();

    while(1) {
        movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());

        if(intakeIn.pressing() || intakeOut.pressing()) {
            if (intakeIn.pressing()) {
                intake(1);
            } else if (intakeOut.pressing()) {
                intake(-1);
            }
        else { intake(0); }

        if(liftUp.pressing() || liftDown.pressing()) {
            if (liftUp.pressing()) {
                intake(1);
            } else if (liftDown.pressing()) {
                intake(-1);
            }
        else { intake(0); }

    }

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    //Values of all axes are needed so that wheel velocity can be modified accordingly
    /*
    omnidirectionalX.changed([](){movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());});
    omnidirectionalY.changed([](){movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());});

    turning.changed([](){movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());});

    intakeIn.pressed([](){intake(0);});
    intakeOut.pressed([](){intake(1);});
    intakeIn.released([](){intake(-1);});
    intakeOut.released([](){intake(-1);});

    liftUp.pressed([](){lift(0);});
    liftDown.pressed([](){lift(1);});
    liftUp.released([](){lift(-1);});
    liftDown.released([](){lift(-1);});

    toggleMode.pressed(modeToggled);
    */
    //The debug screen is updated on every event
}
