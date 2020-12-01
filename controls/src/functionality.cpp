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

/* WHEEL GRADUAL ACCELERATION
 *    When the robot is first supposed to move (when the analog stick is moved),
 * the robot's wheels immediately go to an extremely high velocity (upwards of
 * 200 rpm). Just like in a car, if you try to accelerate too fast, this can
 * cause a lot of sliding (we have kinetic friction but want static friction
 * between the wheels and the ground).
 *
 *    To fix this, we may be able to "gradually" accelerate to the desired speed
 * (the jerk would still be very high). We must use a linear model so that the
 * ratio between the wheel's velocity remains the same. If it does not, then
 * the robot will move in a direction we do not want.
*/

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(double x, double y, double turnValue) {

    //Reset all wheel velocitys so they can be updated as we go through this function
    for(int i = 0; i<NUM_WHEELS; i++) {
        wheels[i]->setVelocity(0);
    }

    double addedVectors = sqrt(pow(x, 2) + pow(y, 2));
    if (addedVectors >= MIN_MOVEMENT_AXIS_DISPLACEMENT) {  //We dont want to have the robot move when the analog stick is barely displaced, but really shouldnt be.

        //Omnidirectional (Left analog stick)

        //Prevent dividing by 0 (while still maintaining direction)
        if (x == 0) {
            if (y > 0) {
                desiredAngle = M_PI/2;
            } else if (y < 0) {
                desiredAngle = -M_PI/2;
            } //y cant be 0 here
        } else {
            desiredAngle = atan(y/x);
        }

        //We need to have a 360 angle
        if(x < 0 && y < 0) {
            desiredAngle = desiredAngle - M_PI;
        } else if(x < 0 && y > 0) {
            desiredAngle = desiredAngle + M_PI;
        } else if(x < 0 && y == 0) {
            desiredAngle = M_PI;
        }
        
        // Speed derived from analog stick displacement * max rpm * angle
        
        neWheel.setGoalVelocity((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((M_PI/4)-desiredAngle)); 
        swWheel.setGoalVelocity((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((3*M_PI/4)-desiredAngle));
        nwWheel.setGoalVelocity((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((-3*M_PI/4)-desiredAngle));
        //revert nwWheel goal velocity to negative if reversed
        seWheel.setGoalVelocity((addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin((-M_PI/4)-desiredAngle));

    }

    //Turning (Right analog stick)
    //Simply add the velocity to the motors
    if(turnValue < -MIN_MOVEMENT_AXIS_DISPLACEMENT || turnValue > MIN_MOVEMENT_AXIS_DISPLACEMENT) { //Dont want tiny values to have any effect
        neWheel.setGoalVelocity(neWheel.getGoalVelocity() + -MAX_SPEED*(turnValue/MAX_AXIS_VALUE));
        swWheel.setGoalVelocity(swWheel.getGoalVelocity() + MAX_SPEED*(turnValue/MAX_AXIS_VALUE));
        nwWheel.setGoalVelocity(nwWheel.getGoalVelocity() + -MAX_SPEED*(turnValue/MAX_AXIS_VALUE));
        //Revert nwWheel goal velocity back to positive if reversed
        seWheel.setGoalVelocity(seWheel.getGoalVelocity() + MAX_SPEED*(turnValue/MAX_AXIS_VALUE));
    }

    //Wheel drifting corrections
    /*
    if(driverMode) { //We only want wheel corrections to happen during driver mode
        for(int i = 0; i<NUM_WHEELS; i++) { //Iterate through all wheels to update velocity records
            Wheel *wheel = wheels[i];
            int velocity = int(wheel->velocity);
            wheel->shiftVelocityRecords(velocity); //Update velocity records (do not include the drifting correction in the velocity records)
            int avg = wheel->avgVelocity(); //We also want to know if they are in the opposite direction (in which case, going to drift)
            if(((velocity<0) != (avg<0)) || abs(int(velocity)) < abs(avg)/2) { //We are slowing or going in the opposite direction (GOING TO DRIFT)
                wheel->velocity -= avg; //remember this this happens for only about 1/5 of a second
            }
        }
    }*/

    //Brake if the wheel is not supposed to move (Make the motor go back if it moves)
    //Otherwise, spin
    for(int i=0; i<NUM_WHEELS; i++) {
        Wheel *wheel = wheels[i];
        if(wheel->getVelocity() == 0) {
            wheel->wheelMotor->stop(hold);
        } else if(wheel->getGoalVelocity() == 0) { //If goal velocity is 0, then immediately stop.
            wheel->setVelocity(0);
            wheel->wheelMotor->stop(hold);
        } else {
            wheel->spin(forward);
        }
    }
}

/*
 * using values stored in enum `motorActions`
*/
void intake(int dir) {
    if(dir == intakeout) { //Out
        intakeLeftMotor.spin(forward);
        intakeRightMotor.spin(forward);
    } else if(dir == stop) { //Stop
        intakeLeftMotor.stop(hold);
        intakeRightMotor.stop(hold);
    } else if(dir == intakein) { //In
        intakeLeftMotor.spin(reverse);
        intakeRightMotor.spin(reverse);
    }  
}

/*
 * Using values stored in enum `motorActions`
*/
void lift(int dir) {
    if(dir == liftdown) { //Down
        liftLeftMotor.spin(forward);
        liftRightMotor.spin(forward);
    } else if(dir == stop) { //Stop
        liftLeftMotor.stop(hold);
        liftRightMotor.stop(hold);
    } else if(dir == liftup) { //Up
        liftLeftMotor.spin(reverse);
        liftRightMotor.spin(reverse);
    }
}

/*
 * Immediately stop all motors and brake them
*/
void emergencyStop() {
    neWheelMotor.stop(brake);
    nwWheelMotor.stop(brake);
    seWheelMotor.stop(brake);
    swWheelMotor.stop(brake);
    liftLeftMotor.stop(brake);
    liftRightMotor.stop(brake);
    intakeLeftMotor.stop(brake);
    intakeRightMotor.stop(brake);
}