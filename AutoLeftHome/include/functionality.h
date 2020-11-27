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

extern double desired_angle;

/* FOR WHEEL CORRECTION LINKED LIST IMPLEMENTATION */

//Motor intake and lift actions
enum motorActions {
    intakein = 1,
    intakeout = 2,
    stop = 3,
    liftup = 4,
    liftdown = 5,
};

const int MAX_SPEED = 200; //rpm

const int MAX_AXIS_VALUE = 127;

//If not driver mode, then autonomous mode
extern bool driverMode; 

/*
 * Gets the average of the values of all the nodes
 * @param head         The first node in this linked list
 * @return int         The average of the values
*/
int avgFromLinkedList(Node *head);

/*
 * Allows for omnidirectional movement by using the ratio between the y and x axes of the left analog stick.
 * Displacement of the analog stick is taken into account when determining relative speed.
 * Turning is dealt with here on every movement of both analog sticks to allow for movement and turning simulatneously.
 * @param x            Value of the x axis of the movement analog stick. Can be aribitary value when used for autonomous.
 * @param y            Value of the y axis of the movement analog stick. Can be aribitary value when used for autonomous.
 * @param turnvalue    Value of the turn analog stick. Can be arbitrary value when used for autonomous.
*/
void movement(double x, double y, double turnvalue);

/*
 * Moves the liftLeft and liftRight motors according to desired direction.
 * @param upOrDown     Direction desired. 0 = In, 1 = Out.
*/
void intake(int inOrOut);

/*
 * Moves the liftLeft and liftRight motors according to desired direction.
 * @param upOrDown     Direction desired. 0 = Up, 1 = Down.
*/
void lift(int upOrDown);

#endif