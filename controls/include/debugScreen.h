/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       debugMenuTemp.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Debug Screen Header Defintions                            */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#ifndef DEBUG_HEADER_GUARD
#define DEBUG_HEADER_GUARD

#include "vex.h"

using namespace vex;

/** The temperature units used to report the temperature on the debug screen */
extern temperatureUnits u;

/**
 * Displays the current value of the axes of the left analog stick.
*/
void leftAnalogStick();

/**
 * Displays the current value of the axes of the right analog stick.
*/
void rightAnalogStick();

/**
 * Displays whether or not the A/B/X/Y buttons are being pressed.
*/
void buttons();

/**
 * Displays whether or not each arrow button is being pressed.
*/
void arrows();

/**
 * Displays whether or not each bumper is being pressed (the back/top buttons).
*/
void bumpers();

/**
 * Displays the angle relative to the positive x-axis that is created if a line
 * were drawn between the left analog stick's natural position and its current
 * position.
*/
void movementAngle();

/**
 * Displays the temperature of all motors like so:
 *
 * Motor Temperature:
 * ne : 20 | nw : 20 | se : 20 | sw : 20
 * liftleft : 20 | liftright : 20 | intakeleft : 20 | intakeright : 20
*/
void temperature();

/**
 * Wipes the debug info from the brain's screen and places the cursor at the
 * origin.
*/
void resetDebug();

/**
 * Main function for displaying all the debug information on the screen.
 * Calls the above functions.
*/
void debugMenuController();

void number(double numb);

#endif