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
 * The 'right' parameter determines how quickly the robot will move on the left/right axis (in rpm) following acceleration.
 *      Negative values: move left.
 * The 'forward' parameter determines how quickly the robot will move on the forward/backward axis (in rpm) following acceleration.
 *      Negative values: move backwards.
 * The 'turnValue' parameter determines how quickly the robot will turn. Positive values will result in turning right. Negative
 *          values will result in turning left.
 * The 'ms' parameter determines how long the robot will be moving in this fashion, in milliseconds.
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

/*
 * How to write autonomous:
 * 
 * Each autonomous program has its own "side". The side is defined as -1, 0, or 1 in the SIDE constant in the side.h file.
 * THIS VALUE SHOULD NOT BE CHANGED. The left side is -1, the user control is 0, and the right side is 1. If the SIDE is 0,
 * then we wont even be going to autonomous (purely user control, such as for testing and skills, but NOT for the main competition).
 * The SIDE is intended to be used through multiplication for reversing movement.
 *
 * For example:
 *      timedMovement(0, MAX_AXIS_VALUE*SIDE, 0, 1000)
 *
 * The above line will cause the robot to move left or right depending on the SIDE of the board the robot starts on.
 * If the robot starts on the right side, then the SIDE value will be 1, and the horizontal motion argument ("right")
 * of timedMovement will be positive. If on the left side, meaning SIDE is -1, then the horizontal motion argument will instead
 * be a negative value. 
 *
 * This is typically used on horizontal motion because that is usually what is reversed, however reversing forward/backward
 * motion may be necessary or desired. The SIDE variable can be used in other ways as well (however you want to, just treat it as 
 * reversing a number's sign).
 *
 * BUGS:
 *      Currently, the *first* timedFunction call will cause the robot to move once the robot is supposed to STOP moving (working on fixing it).
 *          To fix this, make a call to timedFunction with a sufficiently large value (like 100) in both the right and forward parameters,
 *                  for a very short period of time (not 0, although that might work. I havent tested that yet).
 *          Example: 1. timedFunction(100, 100, 0, 1); //1 ms is a good amount of time to ensure that the rest of your autonomous is not messed up.
 *
 * Functions you will likely need to use: (see the respective indepth documentation above the function's declaration in the header file)
 *      timedMovement(double right, double forward, double turnValue, int ms)
 *          Located in the autonomous.h file.
 *          This will cause the robot to move in the desired direction ('right' and 'forward') for an amount of time ('ms').
 *              Make right a negative value to move left and forward a negative value to move backwards.
 *          Keep in mind that the time that passes in this function should also be accounted for in the autonomous function.
 *              For example, the following lines will run for 1500 milliseconds (1000 + 500 = 1500):
 *                  1. timedMovement(100, 100, 0, 1000);
 *                  2. pause(500);
 *              If you want the robot to start moving the lift and intake motors while the robot is moving, then you must split the movement
 *                      into multiple function calls.
 *                    For example, the following lines causes the robot to start moving, then half a second in, start moving the ball function motors
 *                          (then stop moving half a second later):
 *                      1. timedMovement(100, 100, 0, 500); //this timedMovement call was split in two so that the ball function motors could move after half a second
 *                      2. ballFunction(up); 
 *                      3. timedMovement(100, 100, 0, 500);
 *
 *      ballFunction(int direction)
 *          Located in the functionality.h file.
 *          This will cause the robot's 'lift' and 'intake' mechanisms to move in the desired direction. Direction values are defined 
 *                  in `motorAction` (in the functionality.h file), which are just `up`, `down`, and `stop`.
 *
 *      pause(int ms)
 *          Located in the autonomous.h file.
 *          Pause this thread for the given number of milliseconds (just wait).
 *
*/
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
