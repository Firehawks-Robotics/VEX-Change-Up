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

competition comp;

void pre_auton() {
    vexcodeInit();
}

void usercontrol() {

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

    stopMotors.pressed(emergencyStop);

    //Movement is handled by an infinite while loop to ensure that the movement gets updated like it should
    //Sometimes the axis.changed event does not happen even if the axis value does change. Thus, our current solution.
    while(1) { //Each iteration of this loop is one tick
        movement(omnidirectionalX.value(), omnidirectionalY.value(), turning.value());
        //Now account for initial skidding by gradually increasing velocity with a constant acceleration
        //until the desired velocity is reached.
        for(int i=0; i<NUM_WHEELS; i++) {
            wheels[i]->calculateAcceleratingVelocity();
        }
        wait(TICK_LENGTH, msec); //Use less battery this way
        debugMenuController(); //Debug screen is updated every tick
    }

}

int main() {

    /*
     * If testing autonomous, then uncomment the below lines and comment out
     * the rest of the code in this function
    */
    //vexcodeInit();
    //autonomous();

    //If this is one of the autonomous programs, then we need to wait until something happens
    if(SIDE != 0) { 

        pre_auton();

        comp.autonomous(autonomous);
        comp.drivercontrol(usercontrol);

        /*
         * prevent main from exiting with an infinite
         * loop while we wait for instructions from the field switch
         *
         * Additionally, when in autonomous, we want the wheels to not skid,
         * so we need to account for that every tick.
        */
        while(1) {
            wait(20, msec);
        }
        
    } else { //If this is the controls testing, then go directly to the drivercontrols
        vexcodeInit();
        usercontrol();
    }

}
