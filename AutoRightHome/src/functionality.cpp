/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       functionality.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Sun Nov 15 2020                                                 */
/*    Description:  Change Up Motor Functionality Implementation                    */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

#include "functionality.h"
#include "debugScreen.h"

//If not driver mode, then autonomous mode
bool driverMode = true; 

double desired_angle = 0;

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(double x, double y, double turnvalue) {

    //Reset all wheel velocitys so they can be updated as we go through this function
    for(int i = 0; i<4; i++) {
        wheels[i]->velocity = 0;
    }

    double added_vectors = sqrt(pow(x, 2) + pow(y, 2));
    if (added_vectors >= 10) {  //We dont want to have the robot move when the analog stick is barely displaced, but really shouldnt be.

        //Omnidirectional (Left analog stick)

        //Prevent dividing by 0 (while still maintaining direction)
        //At large numbers like 100/0.0001, arctan(x) changes very little with each decimal place
        if (x == 0) {
            if (y > 0) {
                desired_angle = M_PI/2;
            } else if (y < 0) {
                desired_angle = -M_PI/2;
            } //y cant be 0 here
        } else {
            desired_angle = atan(y/x);
        }

        //We need to have a 360 angle
        if(x < 0 && y < 0) {
            desired_angle = desired_angle - M_PI;
        } else if(x < 0 && y > 0) {
            desired_angle = desired_angle + M_PI;
        } else if(x < 0 && y == 0) {
            desired_angle = M_PI;
        }
        
        // Speed derived from analog stick displacement * max rpm * angle
        
        neWheel.velocity = (added_vectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(M_PI/4-desired_angle); 
        swWheel.velocity = -(added_vectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(-3*M_PI/4-desired_angle);
        nwWheel.velocity = (added_vectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(3*M_PI/4-desired_angle);
        seWheel.velocity = -(added_vectors/MAX_AXIS_VALUE)*MAX_SPEED*sin(-M_PI/4-desired_angle);

    }

    //Turning (Right analog stick)
    //Simply add the velocity to the motors
    if(turnvalue < -10 || turnvalue > 10) { //Dont want tiny values to have any effect
        for(int i=0; i<4; i++) {
            wheels[i]->velocity += MAX_SPEED*(turnvalue/MAX_AXIS_VALUE);
        }
    }

    //Brake if the wheel is not supposed to move (Make the motor go back if it moves)
    //Otherwise, spin
    for(int i=0; i<4; i++) {
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
    } else if(dir == 0) { //Stop
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