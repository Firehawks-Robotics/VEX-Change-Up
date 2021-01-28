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

double desiredAngle = 0;

int lastAddedVectors = 0;

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

double num = 0;

//Defined constants with reduced decimals in hopes of reducing the power usage
constexpr double PI = 3.14;
constexpr double PI_2 = 1.57;
constexpr double PI_4 = 0.79;
constexpr double THREE_PI_4 = 2.37;

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(int x, int y, int turnValue) {

    int addedVectors = (int)floor(sqrt(pow(x, 2) + pow(y, 2)));
    if (addedVectors >= MIN_MOVEMENT_AXIS_DISPLACEMENT) {  //We dont want to have the robot move when the analog stick is barely displaced, but really shouldnt be.

        //Omnidirectional (Left analog stick)

        //Prevent dividing by 0 (while still maintaining direction)
        if (x == 0) {
            if (y > 0) {
                desiredAngle = PI_2;
            } else if (y < 0) {
                desiredAngle = -PI/2;
            } //y cant be 0 here
        } else {
            desiredAngle = round(atan(y/x));
        }

        //We need to have a 360 angle
        if(x < 0 && y < 0) {
            desiredAngle = desiredAngle - PI;
        } else if(x < 0 && y > 0) {
            desiredAngle = desiredAngle + PI;
        } else if(x < 0 && y == 0) {
            desiredAngle = PI;
        }
        
        // Speed derived from analog stick displacement * max rpm * angle
        int nwsw = (int)floor((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((-THREE_PI_4)-desiredAngle));
        int nese = (int)floor((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((-PI_4)-desiredAngle));
        neWheel.setGoalVelocity(nese); 
        swWheel.setGoalVelocity(nwsw);
        nwWheel.setGoalVelocity(nwsw);
        seWheel.setGoalVelocity(nese);

    } else {
        for(int i=0; i<NUM_WHEELS; i++) {
            wheels[i]->setGoalVelocity(0);
        }
    }
  
    //Turning (Right analog stick)
    //Simply add the velocity to the motors
    if(turnValue < -MIN_TURNING_AXIS_DISPLACEMENT || turnValue > MIN_TURNING_AXIS_DISPLACEMENT) { //Dont want tiny values to have any effect
        int speed = (int)floor(MAX_SPEED*(turnValue/MAX_AXIS_VALUE));
        neWheel.setGoalVelocity(neWheel.getGoalVelocity() + -speed);
        swWheel.setGoalVelocity(swWheel.getGoalVelocity() + speed);
        nwWheel.setGoalVelocity(nwWheel.getGoalVelocity() + -speed);
        seWheel.setGoalVelocity(seWheel.getGoalVelocity() + speed);
    }

    //Brake if the wheel is not supposed to move (Make the motor go back if it moves)
    //Otherwise, spin
    for(int i=0; i<NUM_WHEELS; i++) {
        Wheel *wheel = wheels[i];
        if(wheel->getVelocity() == 0) {
            wheel->wheelMotor->stop(coast);
        } else {
            wheel->spin(forward);
        }
    }

    //Update the initial velocity of the wheels for the acceleration if necessary
    if (addedVectors != lastAddedVectors) { //Means that the driver now wants to move in a different direction.
        for(int i=0; i<NUM_WHEELS; i++) { //Now the thing should start accounting for new goal (new acceleration as well).
            wheels[i]->setInitialVelocity(wheels[i]->getVelocity());
        }
    }

    //Update the lastAddedVectors to the new value for the latest tick.
    lastAddedVectors = addedVectors;
}

/*
 * Using values stored in enum `motorActions`
*/
void ballFunction(int dir) {
    if(dir == down) { //Down
        liftLeftMotor.spin(forward);
        liftRightMotor.spin(forward);
        intakeLeftMotor.spin(reverse);
        intakeRightMotor.spin(reverse);
    } else if(dir == stop) { //Stop
        liftLeftMotor.stop(hold);
        liftRightMotor.stop(hold);
        intakeLeftMotor.stop(hold);
        intakeRightMotor.stop(hold);
    } else if(dir == up) { //Up
        liftLeftMotor.spin(reverse);
        liftRightMotor.spin(reverse);
        intakeLeftMotor.spin(forward);
        intakeRightMotor.spin(forward);
    }
}

/*
 * Immediately stop all motors and brake them
*/
void emergencyStop() {
    neWheelMotor.stop(brake);
    neWheel.setVelocity(0);
    nwWheelMotor.stop(brake);
    nwWheel.setVelocity(0);
    seWheelMotor.stop(brake);
    seWheel.setVelocity(0);
    swWheelMotor.stop(brake);
    swWheel.setVelocity(0);
    liftLeftMotor.stop(brake);
    liftRightMotor.stop(brake);
    intakeLeftMotor.stop(brake);
    intakeRightMotor.stop(brake);
}
