/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       main.cpp                                                        */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thurs Oct 22 2020                                               */
/*    Description:  Change Up Driver Controls                                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"
#include <math.h>

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// neWheel              motor         ?              (northeast wheel)
// nwWheel              motor         ?              (northwest wheel)
// seWheel              motor         ?              (southeast wheel)
// swWheel              motor         ?              (southwest wheel)
// intakeRight          motor         ?               
// intakeLeft           motor         ?               
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

int speed = 200; //rpm

const int MAX_AXIS_VALUE = 127;
//const int MIN_AXIS_VALUE = -127;

//If not driver mode, then autonomous mode
bool driverMode = true; 

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement() {

    //Omnidirectional (Left analog stick)
    //Subtract the desired angle (relative to the origin) from each motor's
    //angle on the unit circle.
    double x = omnidirectionalX.value();
    double y = omnidirectionalY.value();
    double desired_angle = atan(y/x);
    
    double neSpeed = speed*sin(M_PI/4-desired_angle);
    double swSpeed = speed*sin(-3*M_PI/4-desired_angle);

    double nwSpeed = speed*sin(3*M_PI/4-desired_angle);
    double seSpeed = speed*sin(-M_PI/4-desired_angle);

    //Turning (Right analog stick)
    //Simply add the speed to the motors
    neSpeed += speed*(turning.value()/MAX_AXIS_VALUE);
    nwSpeed += speed*(turning.value()/MAX_AXIS_VALUE);
    seSpeed += speed*(turning.value()/MAX_AXIS_VALUE);
    swSpeed += speed*(turning.value()/MAX_AXIS_VALUE);

    neWheel.setVelocity(neSpeed, rpm);
    nwWheel.setVelocity(nwSpeed, rpm);
    seWheel.setVelocity(seSpeed, rpm);
    swWheel.setVelocity(swSpeed, rpm);

    neWheel.spin(forward);
    swWheel.spin(forward);
    nwWheel.spin(forward);
    seWheel.spin(forward);

    debugMenuController();
}

/*
 * 0 = In
 * 1 = Out
*/
void intake(int inOrOut) {
    if(inOrOut == 0) { //In
        intakeLeft.spin(forward);
        intakeRight.spin(forward);
    } else { //Out
        intakeLeft.spin(reverse);
        intakeRight.spin(reverse);
    }  
    debugMenuController();
}

/*
 * 0 = Up
 * 1 = Down
*/
void lift(int upOrDown) {
    if(upOrDown == 0) { //Up
        liftLeft.spin(forward);
        liftRight.spin(forward);
    } else { //Down
        liftLeft.spin(reverse);
        liftRight.spin(reverse);
    }
    debugMenuController();
}

void modeToggled() {
    driverMode = !driverMode;
    debugMenuController();
}

int main() {

    vexcodeInit();

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    omnidirectionalX.changed(movement);
    omnidirectionalY.changed(movement);

    turning.changed(movement);

    intakeIn.pressed([](){intake(0);});
    intakeOut.pressed([](){intake(1);});

    liftUp.pressed([](){lift(0);});
    liftUp.pressed([](){lift(1);});

    toggleMode.pressed(modeToggled);

    //The debug screen is updated on every event
}
