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
#include "debugScreen.h"

/* Using these values, all that is needed is to multiply some values by the side, thus making some negative and some positive
 * Sides:
 * -1: Left Side
 *  0: Controls (no side and no autonomous) (Wont even reach this function)
 *  1: Right Side
*/

/* NOTES
 * - SIDE is used to change the direction of some actions that should change based on the side of the board the robot is placed
 * - All pausing/moving times will need to be updated
*/

//1000 milliseconds = 1 second
void pause(int milliseconds) { wait(milliseconds, timeUnits::msec); }

/*
 * Adjusts for acceleration every tick. Automatically stops moving at end.
*/
void timedMovement(double right, double forward, double turnValue, int ms) {

    movement(right, forward, turnValue);

    while(ms > 0) { //Break if time is up

        for(int i=0; i<NUM_WHEELS; i++) {
            wheels[i]->calculateAcceleratingVelocity();
        }
        
        pause(TICK_LENGTH);
        ms = ms - TICK_LENGTH;
    }

    //We want the robot to stop moving now
    movement(0,0,0);
}

//At prototype, this should take 7 seconds (lmao, yeah right)
void autonomous() {
    //KEEP THE FIRST timedMovement CALL HERE
    //THIS MAKES IT WORK BY CALLING THE movement FUNCTION AT ONCE BEFORE EVERYTHING ELSE
    timedMovement(101, 101, 101, 1); 
    //Move NE to get in front of goal
    timedMovement(MAX_AXIS_VALUE, SIDE*MAX_AXIS_VALUE, 0, 1000);

    //Turn around
    timedMovement(0, 0, SIDE*MAX_AXIS_VALUE, 500);

    //Move forwards and intake the two balls
    ballFunction(up); //Will continue for an entire second (Account for the 500 ms in timedMovement() as well)
    timedMovement(MAX_AXIS_VALUE, 0, 0, 500);

    pause(500); //Intake balls and score preload at the same time

    ballFunction(stop);

    //Go score one ball in the middle goal
    timedMovement(0, 0, SIDE*MAX_AXIS_VALUE, 200); //Fix angle

    timedMovement(SIDE*MAX_AXIS_VALUE, 0, 0, 2000);
    //Stop once reaches goal

    ballFunction(up); //Put the ball in the goal

    pause(250); //stop before we put the last ball in there (we dont want that)

    ballFunction(stop);

    //Go to the last goal on the home row
    timedMovement(SIDE*MAX_AXIS_VALUE, MAX_AXIS_VALUE, 0, 1500); //Give wide berth to other robot so it doesnt get in the way (going out)

    timedMovement(SIDE*MAX_AXIS_VALUE, -MAX_AXIS_VALUE, 0, 1500); //Give wide berth to other robot so it doesnt get in the way (going towards goal)

    ballFunction(up); //Put the last ball in the last goal

    pause(500);

    ballFunction(stop); //Stop everything

    //IDEA: if there is still enough time at the end, then move somewhere that would give a strategic advantage

}