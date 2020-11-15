/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       functionality.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Sun Nov 15 2020                                                 */
/*    Description:  Change Up Motor Functionality Header Definitions                */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

const int SPEED = 200; //rpm

const int MAX_AXIS_VALUE = 127;
//const int MIN_AXIS_VALUE = -127;

//If not driver mode, then autonomous mode
extern bool driverMode; 

/*
 * Moves stuff
*/
void movement(double x, double y, double turnvalue);

/*
 * Moves the liftLeft and liftRight motors according to desired direction
 * 0 = In
 * 1 = Out
*/
void intake(int inOrOut);

/*
 * Moves the liftLeft and liftRight motors according to desired direction
 * 0 = Up
 * 1 = Down
*/
void lift(int upOrDown);

/*
 * Toggles between driver and autonomous control
*/
void modeToggled();