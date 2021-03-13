/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       functionality.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Sun Nov 15 2020                                                 */
/*    Description:  Change Up Motor Functionality Implementation                    */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"
#include <cmath>

using namespace vex;

#include "functionality.h"
#include "debugScreen.h"

/*
 * Using values stored in enum `motorActions`
*/
void intakeMotors(int dir) {
    if(dir == expel) { //Down
        intakeLeftMotor.spin(reverse);
        intakeRightMotor.spin(reverse);
    } else if(dir == stopIntake) { //Stop
        intakeLeftMotor.stop(hold);
        intakeRightMotor.stop(hold);
    } else if(dir == intake) { //Up
        intakeLeftMotor.spin(forward);
        intakeRightMotor.spin(forward);
    }
}

void liftMotors(int dir) {
    if(dir == down) { //Down
        liftTopMotor.spin(forward);
        liftBottomMotor.spin(forward);
    } else if(dir == stopLift) { //Stop
        liftTopMotor.stop(hold);
        liftBottomMotor.stop(hold);
    } else if(dir == up) { //Up
        liftTopMotor.spin(reverse);
        liftBottomMotor.spin(reverse);
    }
}

/*
 * Immediately stop all motors and brake them
*/
void emergencyStop() {
    train.stop(brake);
    liftTopMotor.stop(brake);
    liftTopMotor.stop(brake);
    intakeLeftMotor.stop(brake);
    intakeRightMotor.stop(brake);
}
