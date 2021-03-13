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
 * Lift/Intake - Front Right Bumper (R1)
 * Down/Expel - Back Right Bumper (R2)
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugScreen.h"
#include "functionality.h"
#include "autonomous.h"
#include "robot-config.h"

//By using this, I will be able to copy the entirety of the code EXCEPT the side.h file and the autonomous.
//This will allow me to easily copy new code from other programs (the controls program) over here.
//All the side constant does is reverse directions of some things.
#include "side.h"

competition comp;

void pre_auton() {
    vexcodeInit();
}

constexpr double levelOnePower = 0.4;
constexpr double levelTwoPower = 0.8;
constexpr double levelThreePower = 1.4;

void updateSpeedPower(double newPower) {
    percentOfMaxSpeed = newPower;
    if(newPower == levelOnePower) {
        mainCon.rumble(".");
        mainCon.Screen.setCursor(0, 0);
        mainCon.Screen.print("1");
    } else if(newPower == levelTwoPower) {
        mainCon.rumble("..");
        mainCon.Screen.setCursor(0, 0);
        mainCon.Screen.print("2");
    } else if(newPower == levelThreePower) {
        mainCon.rumble("...");
        mainCon.Screen.setCursor(0, 0);
        mainCon.Screen.print("3");
    }
}

void controls() {

    //Using lambdas here btw (learn more: https://en.cppreference.com/w/cpp/language/lambda)
    //Values of all axes are needed so that wheel velocity can be modified accordingly
    functionUp.pressed([](){liftMotors(up);});
    functionDown.pressed([](){liftMotors(down);});
    functionUp.released([](){liftMotors(stopLift);});
    functionDown.released([](){liftMotors(stopLift);});

    functionIntake.pressed([](){intakeMotors(intake);});
    functionExpel.pressed([](){intakeMotors(expel);});
    functionIntake.released([](){intakeMotors(stopIntake);});
    functionExpel.released([](){intakeMotors(stopIntake);});

    speedUp.pressed([](){
        if(percentOfMaxSpeed == levelOnePower) {
            updateSpeedPower(levelTwoPower);
        } else if(percentOfMaxSpeed == levelTwoPower) {
            updateSpeedPower(levelThreePower);
        } else if(percentOfMaxSpeed == levelThreePower) {
            updateSpeedPower(levelThreePower);
        }
    });

    speedDown.pressed([](){
        if(percentOfMaxSpeed == levelThreePower) {
            updateSpeedPower(levelTwoPower);
        } else if(percentOfMaxSpeed == levelTwoPower) {
            updateSpeedPower(levelOnePower);
        } else if(percentOfMaxSpeed == levelOnePower) {
            updateSpeedPower(levelOnePower); //No change
        }
    });

    updateSpeedPower(levelTwoPower);

    //stopMotors.pressed(emergencyStop);

    //Movement is handled by an infinite while loop to ensure that the movement gets updated like it should
    //Sometimes the axis.changed event does not happen even if the axis value does change. Thus, our current solution.
    while(1) { //Each iteration of this loop is one tick]

        //Movement
        bool movement = false;
        if(abs(forwardAxis.value()) > MIN_MOVEMENT_AXIS_DISPLACEMENT) {
            movement = true;
            train.drive(forward, forwardAxis.value()*(percentOfMaxSpeed), rpm);
        }
        if(abs(turningAxis.value()) > MIN_TURNING_AXIS_DISPLACEMENT) {
            movement = false;
            train.turn(right, turningAxis.value(), rpm);
        }
        if(!movement) { //Make it brake if its not supposed to move
            train.stop(brake);
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
    
    /*
    vexcodeInit();
    autonomous();
    //*/

    ///*
    //If this is one of the autonomous programs, then we need to wait until something happens
    if(SIDE != 0) { 

        pre_auton();

        autonomous();
        controls();
        
        /*while(1) {
            wait(TICK_LENGTH, msec);
        }*/
        
    } else { //If this is the controls testing, then go directly to the drivercontrols
        vexcodeInit();
        controls();
    }
    //*/

}
