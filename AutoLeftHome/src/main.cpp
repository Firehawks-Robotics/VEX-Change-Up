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
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugScreen.h"
#include "functionality.h"
#include "autonomous.h"

//By using this, I will be able to copy the entirety of the code EXCEPT the side.h file and the autonomous.
//This will allow me to easily copy new code from other programs (the controls program) over here.
//All the side constant does is reverse directions of some things.
#include "side.h"

int main() {

    vexcodeInit();

    if(SIDE != 0) { //If this is the controls program, then DONT do autonomous
        auton();
    }

    //After autonomous, then we are free to go into driver control mode (and record the wheel velocities as well)

    driverMode = true;

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    //Values of all axes are needed so that wheel velocity can be modified accordingly
    intakeIn.pressed([](){intake(intakeout);});
    intakeOut.pressed([](){intake(intakein);});
    intakeIn.released([](){intake(stop);});
    intakeOut.released([](){intake(stop);});

    liftUp.pressed([](){lift(liftup);});
    liftDown.pressed([](){lift(liftdown);});
    liftUp.released([](){lift(stop);});
    liftDown.released([](){lift(stop);});

    //Movement is handled by an infinite while loop to ensure that the movement gets updated like it should
    //Sometimes the axis.changed event does not happen even if the axis value does change. Thus, our current solution.
    while(1) { //Each iteration of this loop is one tick (so each tick is about 20 ms)
        movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());
        wait(20, timeUnits::msec); //Use less battery this way
        debugMenuController(); //Debug screen is updated every tick
    }
}
