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

//If not driver mode, then autonomous mode
bool driverMode = true; 

double desiredAngle = 0;

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(double x, double y, double turnValue) {

    //Reset all wheel velocitys so they can be updated as we go through this function
    for(int i = 0; i<NUM_WHEELS; i++) {
        wheels[i]->velocity = 0;
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
        
        neWheel.velocity = (addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(M_PI/4-desiredAngle); 
        swWheel.velocity = -swWheel.velocity;
        nwWheel.velocity = (addedVectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(3*M_PI/4-desiredAngle);
        seWheel.velocity = -nwWheel.velocity;

    }

    //Turning (Right analog stick)
    //Simply add the velocity to the motors
    if(abs(int(turnValue)) > MIN_MOVEMENT_AXIS_DISPLACEMENT) { //Dont want tiny values to have any effect
        for(int i=0; i<NUM_WHEELS; i++) {
            wheels[i]->velocity += MAX_SPEED*(turnValue/MAX_AXIS_VALUE);
        }
    }

    //Brake if the wheel is not supposed to move (Make the motor go back if it moves)
    //Otherwise, spin
    for(int i=0; i<NUM_WHEELS; i++) {
        if(wheels[i]->velocity == 0) { wheels[i]->wheelMotor->setBrake(hold); }
        else wheels[i]->spin(forward);
    }
}

/*
 * using values stored in enum `motorActions`
*/
void intake(int dir) {
    if(dir == intakein) { //Out
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