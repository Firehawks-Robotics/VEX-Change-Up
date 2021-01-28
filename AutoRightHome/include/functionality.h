/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       functionality.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Sun Nov 15 2020                                                 */
/*    Description:  Change Up Motor Functionality Header Definitions                */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#ifndef FUNCTIONALITY_HEADER_GUARD
#define FUNCTIONALITY_HEADER_GUARD

#include "vex.h"

using namespace vex;

/**
 * The angle that the displacement along the horizontal and vertical axes make in radians.
*/
extern double desiredAngle;

/**
 * The value you get when you add the x and y vectors from the movement analog
 * stick that happened during the last tick.
*/
extern int lastAddedVectors;

/**
 * Enumerates the actions that the intake and lift motors can take. The stop
 * action is used for both lift and intake.
*/
enum motorActions {
    down = -1,
    stop = 0,
    up = 1
};

extern double num;

/**
 * int      The maximum speed, in rpm, that the robot's motors will spin.
*/
const int MAX_SPEED = 100;

/*
 * int      The maximum value that an axis of an analog stick can have.
*/
const int MAX_AXIS_VALUE = 127;

/*
 * Allows for omnidirectional movement by using the ratio between the y and x
 * axes of the left analog stick. Displacement of the analog stick is taken
 * into account when determining relative speed. Turning is dealt with here on
 * every movement of both analog sticks to allow for movement and turning simulatneously.
 * @param x            Value of the x axis of the movement analog stick. 
 * @param y            Value of the y axis of the movement analog stick. 
 * @param turnvalue    Value of the turn analog stick horizontally.
*/
void movement(double x, double y, double turnvalue);

/*
 * Moves the liftLeftMotor, liftRightMotor, intakeRightMotor, and 
 * intakeLeftMotor motors according to desired  direction.
 * @param upOrDown     Direction desired. Using values from `motorActions`.
*/
void ballFunction(int dir);


/*
 * Immediately stops all motor movement and brakes (using brakeType brake).
 *
 * An extremely rare phenomenon is that the motors don't stop moving, refuze
 * to change direction, or otherwise become unresponsive. If this were to
 * happen during a match, this could cause problems. If the robot starts to run
 * away, then hit this button to immediately stop it from moving. 
*/
void emergencyStop();

#endif