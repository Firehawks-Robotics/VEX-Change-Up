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
 * The 'forward' parameter determines how quickly the robot will move on the forward/backward axis (in rpm) following acceleration.
 *      Negative values: move backwards.
 * The 'turnValue' parameter determines how quickly the robot will turn. Positive values will result in turning right. Negative
 *          values will result in turning left.
 * The 'ms' parameter determines how long the robot will be moving in this fashion, in milliseconds.
*/
void timedMovement(int forward, int turnValue, int ms) {

    movement(forward, turnValue*SIDE);

    while(ms > 0) { //Break if time is up

        /*for(int i=0; i<NUM_WHEEL_TRAINS; i++) {
            wheelTrains[i]->calculateAcceleratingVelocity();
        }*/
        
        pause(TICK_LENGTH);
        ms = ms - TICK_LENGTH;
    }

    //We want the robot to stop moving now
    movement(0,0);
}

/*
 * Programming skills autonomous.
*/
void autonomous() {
    //Move foward to be in line with the goal
    intakeMotors(intake);
    timedMovement(75, 0, 900);
    intakeMotors(stopIntake);
    pause(500);
    
    //Push ball back out to reduce chances of jamming
    liftMotors(down);
    intakeMotors(expel);
    pause(400);
    intakeMotors(stopIntake);
    liftMotors(stopLift); 

    //Turn to face the goal
    timedMovement(0, 75, 700);
    pause(500);

    //Go to goal
    timedMovement(75, 0, 850);
    
    //Score goal and get ball out of bottom
    liftMotors(up);
    pause(300);
    intakeMotors(intake);
    pause(700);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Go back and turn
    timedMovement(-50, 0, 400);
    pause(500);
    timedMovement(0, 50, 300);
    pause(500);

    //Throw ball
    intakeMotors(expel);
    pause(500);
    intakeMotors(stopIntake);

    //Turn to go back into wall
    timedMovement(0, 50, 650);
    pause(700);

    //Corrrectly align using the wall
    timedMovement(-50, 0, 1250);
    pause(500);

    //Go towards the second goal
    timedMovement(75, 0, 2100);
    pause(500);

    //Turn towards the goal
    timedMovement(0, -50, 650);
    pause(600);

    //Go towards the goal
    timedMovement(50, 0, 500);

    //Put ball in the second goal
    liftMotors(up);
    pause(1000);
    liftMotors(stopLift);

    //Disengage from second goal
    timedMovement(-50, 0, 400);
    pause(300);

    //Turn towards third goal
    timedMovement(0, 50, 600);
    pause(300);

    //Go towards 3rd goal, pick up ball, align with wall.
    intakeMotors(intake);
    timedMovement(75, 0, 2750);
    pause(750);
    liftMotors(up);
    intakeMotors(stopIntake);
    pause(500);
    liftMotors(stopLift);

    //Pull back from the wall
    timedMovement(-75, 0, 450);
    pause(500);

    //Turn towards the 3rd goal
    timedMovement(0, -50, 450);
    pause(250);

    //Go up to the 3rd goal;
    timedMovement(50, 0, 1000);
    pause(250);

    //shoot the ball in the goal;
    liftMotors(up);
    intakeMotors(intake);
    pause(1250);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Go backwards
    timedMovement(-50, 0, 666);
    pause(250);

    //Turn towards the 4th goal
    timedMovement(0, 50, 333);
    pause(250);

    //Throw blue ball possibly picked up
    intakeMotors(expel);
    pause(500);
    intakeMotors(stopIntake);

    //Turn towards the 4th goal
    timedMovement(0, 50, 666);
    pause(250);

    //Go align on back wall
    timedMovement(-50, 0, 2000);
    pause(250);

    //Go towards the 4th goal, while intaking
    intakeMotors(intake);
    timedMovement(50, 0, 3150);
    liftMotors(up);
    pause(300);
    liftMotors(stopLift);
    intakeMotors(stopIntake);

    //Turn towards the 4th goal
    timedMovement(0, -50, 666);
    pause(250);

    //Go towards the 4th goal
    timedMovement(50, 0, 500);
    pause(250);

    //put ball in goal
    intakeMotors(intake);
    liftMotors(up);
    pause(1000);
    liftMotors(stopLift);
    intakeMotors(stopIntake);

    /*

    //Go to be near 4th goal, and get ball on middle line
    timedMovement(50, 0, 1000);
    pause(250);
    intakeMotors(intake);
    liftMotors(up);
    pause(450);
    intakeMotors(stopIntake);
    pause(1250);
    liftMotors(stopLift);

    //Pull back then release any garbage orbs.
    timedMovement(-50, 0, 750);
    pause(250);
    liftMotors(down);
    intakeMotors(expel);
    pause(750);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Become sentient
    timedMovement(0, 50, 800);
    pause(500);
    intakeMotors(intake);
    liftMotors(up);
    timedMovement(75, 0, 1600);
    pause(250);
    intakeMotors(stopIntake);
    liftMotors(stopLift);
    timedMovement(0, -50, 610);
    pause(250);
    timedMovement(50, 0, 550);

    // H U R T
    liftMotors(up);
    intakeMotors(intake);
    timedMovement(-50, 0, 50);
    pause(750);
    intakeMotors(stopIntake);
    liftMotors(stopLift);*/


}
