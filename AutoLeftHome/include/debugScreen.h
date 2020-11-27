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

extern brain vexBrain;

// A global instance of vex::vexBrain used for printing to the V5 vexBrain screen
//vex::brain vexBrain;

extern double d_angle;

extern temperatureUnits u;

//Controllers
extern controller mainCon;

void rightTrigger();

void leftTrigger();

void buttons();

void arrows();

void backButtons();

void resetDebug();

void movementAngle();

void temperature();

/*
    Calls all the functions in order to display
    the current values associated with the controller and motors
*/
void debugMenuController();

#endif