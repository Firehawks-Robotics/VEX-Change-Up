/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       main.cpp                                                        */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thurs Oct 22 2020                                               */
/*    Description:  Change Up Driver Controls                                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// neWheel              motor         ?              (northeast wheel)
// nwWheel              motor         ?              (northwest wheel)
// seWheel              motor         ?              (southeast wheel)
// swWheel              motor         ?              (southwest wheel)
// consumeRight         motor         ?               
// consumeLeft          motor         ?               
// liftLeft             motor         ?               
// liftRight            motor         ?               
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

int currentMode = 0;

//We're gonna have to modify the speed of all the wheels for this
/*
 * 0 = X axis
 * 1 = Y axis
*/
void omnidirectionalMovement(int axis) {

}

void turned() {


}

/*
 * 0 = In
 * 1 = Out
*/
void intake(int inOrOut) {

}

/*
 * 0 = Up
 * 1 = Down
*/
void lift(int upOrDown) {

}

int main() {

    vexcodeInit();

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    omnidirectionalX.changed([](){omnidirectionalMovement(0);});
    omnidirectionalY.changed([](){omnidirectionalMovement(1);});

    turning.changed(turned);

    intakeIn.pressed([](){intake(0);});
    intakeOut.pressed([](){intake(1);});

    liftUp.pressed([](){lift(0);});
    liftUp.pressed([](){lift(1);});

    toggleMode.pressed(
        [](){
            if(currentMode == 0){
                currentMode = 1;
            } else {
                currentMode = 0;
            }
        }
    );

    while(1) {
        debugMenuController();
    }
}
