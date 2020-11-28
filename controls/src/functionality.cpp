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

double desired_angle = 0;

/* WHEEL SELF-CORRECTION
 *    When the wheels brake, they often slip a little bit (and often change the direction of the robot).
 * What if I could prevent the slipping? Well, maybe I can.
 * 
 * The amount of ticks that are recorded could change (see robot-config.h -> MAX_VELOCITY_RECORDS to make sure this is right)
 * Get the average wheel velocity (of each wheel) over the last 10 ticks (each tick is 20 ms, and movement() is called once each tick).
 * If the average wheel velocity is at least double (or in the opposite direction of) the current wheel velocity, then
 * the robot is either slowing or attempting to move in the opposite direction, which could cause the robot to drift.
 * Using the average wheel velocity, the robot should automatically correct for this to do more against slippage than
 * just friction. This can be thought of as anti-lock braking on your car (ABS).
 * 
 * The robot needs to change the wheels' velocity opposite of the average wheel velocity. If the robot is slowing, 
 * which happens when the robot's new velocity from the analog sticks is less than half the average velocity over the last
 * 10 ticks, then we need our wheel correction. Additionally, if the robot is supposed to move opposite the average velocity
 * of the last 10 ticks, then correction. Note that correction for each wheel is independent of the other wheels (dont happen together).
 *
 * Note that this will not be used during autonomous.
*/

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(double x, double y, double turnvalue) {

    //Reset all wheel velocitys so they can be updated as we go through this function
    for(int i = 0; i<NUM_WHEELS; i++) {
        wheels[i]->velocity = 0;
    }

    double added_vectors = sqrt(pow(x, 2) + pow(y, 2));
    if (added_vectors >= MIN_MOVEMENT_AXIS_DISPLACEMENT) {  //We dont want to have the robot move when the analog stick is barely displaced, but really shouldnt be.

        //Omnidirectional (Left analog stick)

        //Prevent dividing by 0 (while still maintaining direction)
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
    if(abs(int(turnvalue)) > MIN_MOVEMENT_AXIS_DISPLACEMENT) { //Dont want tiny values to have any effect
        for(int i=0; i<NUM_WHEELS; i++) {
            wheels[i]->velocity += MAX_SPEED*(turnvalue/MAX_AXIS_VALUE);
        }
    }

    //Wheel drifting corrections
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