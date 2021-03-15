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

void followLine(double dist) {
    
}

/*
 * The match autonomous
 *
*/
void autonomous() {
 //Move foward to be in line with the goal
    timedMovement(75, 0, 900);
    pause(500);

    //Turn to face the goal
    timedMovement(0, 75, 650);
    pause(500);

    //Enable intake motors and move towards the goal
    intakeMotors(intake);
    timedMovement(75, 0, 850);
    intakeMotors(stopIntake);

    //Once at goal, then enable lift to put ball in goal
    liftMotors(up);
    pause(1000);
    liftMotors(stopLift);

    //Back up and turn
    timedMovement(-50, 0, 850);
    pause(500);
    timedMovement(0, 50, 850);
    pause(500);

    //move towards second goal
    timedMovement(75, 0, 1350);
    pause(500);

    //turn to face goal
    timedMovement(0, -50, 600);
    pause(500);

    //Move forwards to goal
    timedMovement(50, 0, 350);
    pause(500);

    //Score goal
    liftMotors(up);
    intakeMotors(intake);
    pause(1500);
    liftMotors(stopLift);
    intakeMotors(stopIntake);

    //Go back from goal
    timedMovement(-50, 0, 500);
}
