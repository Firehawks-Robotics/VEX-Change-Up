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
 * The skills autonomous (different things to do)
*/
void autonomous() {

    //Move forward to be in line with the goal
    intakeMotors(intake);
    train.driveFor(TILE_WIDTH*1.25, inches);
    intakeMotors(stopIntake);
    pause(250);

    //Push ball back out to reduce chances of jamming
    intakeMotors(expel);
    pause(250);
    intakeMotors(stopIntake);

    //Turn to face the first goal
    train.turnFor(SIDE*135, deg);
    pause(250);

    //Go towards the first goal
    train.driveFor(TILE_DIAGONAL, inches);

    //Begin to score goal and take ball out of bottom
    liftMotors(up);
    intakeMotors(intake);
    train.driveFor(TILE_DIAGONAL/4, inches);
    pause(1000);
    liftMotors(stopLift);
    intakeMotors(stopIntake);

    // Back from goal
    train.driveFor(reverse, TILE_DIAGONAL/2, inches);
    pause(250);

    //Spit out blue ball
    train.turnFor(SIDE*45, deg);
    intakeMotors(expel);
    pause(500);
    intakeMotors(stopIntake);

    //Turn to face the middle goal
    train.turnFor(SIDE*90, deg);
    pause(250);

    //Go back to align on back wall
    train.driveFor(reverse, TILE_WIDTH, inches);
    pause(250);

    //Go towards middle goal
    train.driveFor(TILE_WIDTH*2.75, inches);
    pause(250);

    //Turn towards the middle goal
    train.turnFor(-90*SIDE, deg);
    pause(250);

    //Go to the middle goal
    train.driveFor(TILE_WIDTH/4, inches);

    //Take out blue ball and put ball in
    intakeMotors(intake);
    liftMotors(up);
    pause(750);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Go backwards a little bit
    train.driveFor(reverse, TILE_WIDTH/4, inches);
    pause(250);

    //Turn back to expel blue ball
    train.turnFor(-90*SIDE, deg);
    pause(250);

    //Expel blue ball
    intakeMotors(expel);
    liftMotors(down);
    pause(750);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Turn back to 3rd goal
    train.turnFor(-180*SIDE, deg);
    pause(250);

    //Go to the wall to align itself, picking up ball at the same time
    intakeMotors(intake);
    train.driveFor(3*TILE_WIDTH, inches);
    intakeMotors(stopIntake);

    //Go back from wall to line up with the 3rd goal
    train.driveFor(TILE_WIDTH/2, inches);
    pause(250);

    //Turn towards the goal
    train.turnFor(-45*SIDE, deg);
    pause(250);

    //Go up to the goal
    train.driveFor(TILE_DIAGONAL/2, inches);
    pause(250);

    //Score goal and take bottom ball out
    liftMotors(up);
    intakeMotors(intake);
    pause(750);
    liftMotors(stopLift);
    intakeMotors(stopIntake);

    //Move back
    train.driveFor(reverse, TILE_DIAGONAL/2, inches);
    pause(250);

    //Turn to look at wall so can expel ball
    train.turnFor(-45*SIDE, deg);
    pause(250);

    //Expel blue ball
    intakeMotors(expel);
    liftMotors(down);
    pause(500);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Turn to middle line
    train.turnFor(90*SIDE, deg);
    pause(250);

    //Go to middle line, intaking the ball on the middle line
    intakeMotors(intake);
    train.driveFor(TILE_WIDTH*2, inches);
    intakeMotors(stopIntake);

    //Turn towards goal B
    train.turnFor(-90*SIDE, deg);
    pause(250);

    //Go up to goal B
    train.driveFor(TILE_WIDTH/4, inches);
    pause(250);

    //Score in goal B and take blue ball out
    intakeMotors(intake);
    liftMotors(up);
    pause(750);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Back from goal B
    train.driveFor(reverse, TILE_WIDTH/4, inches);
    pause(250);

    //Turn back to blue ball can be expelled
    train.turnFor(-45*SIDE, deg);
    pause(250);

    //Expel blue ball
    intakeMotors(expel);
    liftMotors(down);
    pause(500);
    intakeMotors(stopIntake);
    liftMotors(stopLift);

    //Turn back towards goal C
    train.turnFor(135*SIDE, deg);
    pause(250);

  /*
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

    */

}
