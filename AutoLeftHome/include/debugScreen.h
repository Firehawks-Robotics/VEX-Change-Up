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

extern temperatureUnits u;

void leftAnalogStick();

void rightAnalogStick();

void buttons();

void arrows();

void bumpers();

void resetDebug();

void movementAngle();

void temperature();

/*
    Calls all the functions in order to display
    the current values associated with the controller and motors
*/
void debugMenuController();

#endif