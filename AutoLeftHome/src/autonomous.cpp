/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       autonomous.cpp                                                  */
/*    Author:       Sean Johnson (Firehawks Robotics)                               */
/*    Created:      Sun Nov 22 2020                                                 */
/*    Description:  Autonomous Implementation                                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

//By using this, I will be able to copy the entirety of the code EXCEPT the side.h file and the autonomous.
//This will allow me to easily copy new code from other programs (the controls program) over here.
//All the side constant does is reverse directions of some things.
#include "side.h" 

#include "functionality.h"
#include "autonomous.h"

/* Using these values, all that is needed is to multiply some values by the side, thus making some negative and some positive
 * Sides:
 * -1: Left Side
 *  0: Controls (no side and no autonomous) (Wont even reach this function)
 *  1: Right Side
*/

timeUnits ms = timeUnits::msec; //Just to save a few keystrokes

/* NOTES
 * - SIDE is used to change the direction of some actions that should change based on the side of the board the robot is placed
 * - All pausing times will need to be updated
*/

void pause(int milliseconds) { wait(20, ms); }

void auton() {
    //Move NE to get in front of goal
    movement(MAX_AXIS_VALUE, SIDE*MAX_AXIS_VALUE, 0);
    pause(20);

    //Turn around
    movement(0, 0, SIDE*MAX_AXIS_VALUE);

    pause(20);

    movement(0, 0, 0); //Stop turning

    //Move forwards and intake the two balls
    movement(MAX_AXIS_VALUE, 0, 0);
    intake(IN);

    pause(20);

    movement(0, 0, 0); //Stop moving

    pause(20); //Make this just enough to get them in the intake, but not the lift

    intake(STOPINTAKE);

    //Turn Around and put preload ball in goal
    movement(0, 0, SIDE*MAX_AXIS_VALUE);

    pause(20);

    movement(0, 0, 0); //Stop turning

    lift(UP); //Now put the preload ball in the goal

    pause(20);

    lift(STOPLIFT);

    //Go score one ball in the middle goal
    movement(0, 0, -1*SIDE*MAX_AXIS_VALUE); //Fix angle

    pause(20);

    movement(-1*SIDE*MAX_AXIS_VALUE, 0, 0); //Stop turning and start moving

    pause(20);

    movement(0, 0, 0); //Stop once reached the middle goal

    lift(UP); //Put the ball in the goal

    pause(20); //stop before we put the last ball in there (we dont want that)

    lift(STOPLIFT);

    //Go to the last goal on the home row
    movement(-1*SIDE*MAX_AXIS_VALUE, MAX_AXIS_VALUE, 0); //Give wide berth to other robot so it doesnt get in the way
    
    pause(20);

    movement(-1*SIDE*MAX_AXIS_VALUE, -MAX_AXIS_VALUE, 0); //Turn around half way

    pause(20);

    movement(0, 0, 0); //Stop in front of the goal

    lift(UP); //Put the last ball in the last goal

    pause(20);

    lift(STOPLIFT); //Stop everything

    //IDEA: if there is still enough time at the end, then move somewhere that would give a strategic advantage

}