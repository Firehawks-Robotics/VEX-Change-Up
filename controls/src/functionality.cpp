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

/* WHEEL GRADUAL ACCELERATION (Acceleration constant, velocity increasing to desired speed)
 *    When the robot is first supposed to move (when the analog stick is moved),
 * the robot's wheels immediately go to an extremely high velocity (upwards of
 * 200 rpm). Just like in a car, if you try to accelerate too fast, this can
 * cause unwanted drifting (more like skidding). We have kinetic friction but
 * want static friction between the wheels and the ground.
 *
 *    To fix this, we may be able to "gradually" accelerate to the desired speed
 * (the jerk would still be very high). We must use a linear model so that the
 * ratio between the wheel's velocity remains the same. If it does not, then
 * the robot will move in a direction we do not want.
*/

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(int forward, int turnValue) {

    int leftWheels = 0;
    int rightWheels = 0;

    //Begin with the forward/backward speed
    if(forward < -MIN_MOVEMENT_AXIS_DISPLACEMENT || forward > -MIN_MOVEMENT_AXIS_DISPLACEMENT) {
        leftWheels = forward;
        rightWheels = forward;
    }
  
    //Turning
    //Simply add (or subtract) the velocity to the motors
    if(turnValue < -MIN_TURNING_AXIS_DISPLACEMENT || turnValue > MIN_TURNING_AXIS_DISPLACEMENT) { //Dont want tiny values to have any effect
        leftWheels += turnValue;
        rightWheels -= turnValue;
    }
    
    leftWheelTrain.setGoalVelocity(leftWheels);
    rightWheelTrain.setGoalVelocity(rightWheels);
}

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
    rightWheelTrain.setVelocity(0);
    leftWheelTrain.setVelocity(0);
    rightWheelTrainMotor.stop(brake);
    leftWheelTrainMotor.stop(brake);
    liftTopMotor.stop(brake);
    liftTopMotor.stop(brake);
    intakeLeftMotor.stop(brake);
    intakeRightMotor.stop(brake);
}
