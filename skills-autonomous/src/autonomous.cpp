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

const int BIG_TIMEOUT = 100000;

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

void stopWheels() {
    leftWheelTrainMotor.setStopping(brake);
    rightWheelTrainMotor.setStopping(brake);
}

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
    stopWheels();
}

/*
 * How to write autonomous:
 *    Sean's First Law of Autonomous: 
 *        Speed is inversely proportional to Accuracy and Reliability. When the robot goes fast, the robot has more slippage,
 *        causing the robot to often be misaligned (thus reducing accuracy and reliability). On the flip side, when the robot
 *        goes slow, you cannot do as much within the time alotted. You must balance these to make the best autonomous.
 *
 *    You can adjust the drive train's motor speed. The initial drive speed is set to DRIVE_TRAIN_DRIVE_SPEED and
 *    initial turn speed is DRIVE_TRAIN_TURN_SPEED. Keep in mind that, when turning, the robot can jerk a bit more than when driving,
 *    so it is recommended to keep the robot turn speed fairly low, but not to the point that it harms the overall autonomous. EX:
 *        train.setDriveSpeed(speed, unit);
 *        train.setTurnSpeed(speed, unit);
 *
 *    Use the drivetrain instance (stored in `train`) to drive and turn
 *        train.driveFor(distance, units) - drive for a distance
 *            Use the TILE_WIDTH and TILE_DIAGONAL constants for the distance (they are in inches). These constants make developing the
 *            match and skills autonomous much more streamlined, as you can simply count the tiles on the field.
 *                ex: `train.driveFor(TILE_WIDTH/2, inches)`
 *                ex: `train.turnFor(135*SIDE, degrees)`
 *
 *        train.turnFor(angle, units) - turn to robot (use degrees here for everyone's sanity and for optimization purposes)
 *
 *    Sides:
 *        Each program has its own 'side' (defined in `side.h`). This side is the side of the board the robot starts on from the
 *        perspective of the driver. The side should NOT be changed for ANY reason. The values of the sides are as follows:
 *            1: Right
 *            0: No side (as in no autonomous, meaning only driver control)
 *            -1: Left
 *        This number is used in autonomous to change the direction the robot turns (no effect on forwards/backwards movement).
 *        To use this, multiply the turning angle by the side like so:
 *            train.turnFor(-135*SIDE, deg);
 *        If the robot is on the right side in the above example, SIDE=1, so the robot will turn to the *left* by 135 degrees. If the
 *        robot is on the left side in the above example, SIDE=-1, so the robot will turn to the *right* by 135 degrees.
 *
 *        During a match, the autonomous programs' names indicate the side the robot starts on (like autoright, and autoleft). During
 *        programming skills, the robot always starts on the right side (`skills-autonomous` program).
 *
 *    Timeouts:
 *            When the robot runs into a wall or a goal (or anything else that does not move), the wheels do not spin due to friction
 *        with the ground. This causes the encoder in the motor to not spin either (detects angular position). The drivetrain instance
 *        goes a distance based on what angular distance the motor spins. Since the motor is not spinning, the drivetrain will perpetually
 *        attempt to go the distance it was given (not good). 
 *            To fix this, set a timeout, which is the maximum amount of time the drivetrain will attempt to reach the correct
 *        destination. If the time is reached, then the drivetrain will stop.
 *            When the robot could run into a wall or goal, set a drivetrain timeout (using `train.setTimeout(int32_t time, timeUnits units)` ).
 *                Ensure this timeout is enough to allow the robot to reach the correct distance even without obstacles.
 *
 *    Turning note:
 *        When the robot turns, it does not turn about its center, but instead an axis that is a few inches towards the back.
 *        Adjust your autonomous program to accomodate for this difference (especially important when attempting to line up to a goal).
 *
 *    You cannot turn and go forwards/backwards at the same time. The drivetrain API simply does not allow that. Don't look at me, I
 *    didn't design Vex.
*/
void autonomous() {

   train.setStopping(hold);
   //train.setStopping(brake);
   train.setDriveVelocity(100, rpm);
   train.setTurnVelocity(40, rpm);
 
   //Move forward to be in line with the goal
   intakeMotors(intake);
   train.driveFor(TILE_WIDTH*1.25, inches);
   intakeMotors(stopIntake);
   pause(250);
 
   //Turn to face the first goal
   train.turnFor(SIDE*135, deg);
   pause(250);
 
   //Go towards the first goal
   train.setTimeout(2500, msec);
   train.driveFor(TILE_DIAGONAL, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
 
   //Begin to score goal and take ball out of bottom
   liftMotors(up);
   intakeMotors(intake);
   pause(500);
   intakeMotors(stopIntake);
   pause(600);
   liftMotors(stopLift);
 
   // Back from goal
   train.driveFor(reverse, TILE_DIAGONAL/4, inches);
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
   train.setTimeout(1500, msec);
   train.driveFor(reverse, TILE_WIDTH, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Go towards middle goal
   train.driveFor(TILE_WIDTH*2.75, inches);
   pause(250);
 
   //Turn towards the middle goal
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go to the middle goal
   train.setTimeout(500, msec);
   train.driveFor(TILE_WIDTH/4, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
 
   //Take out blue ball and put ball in
   intakeMotors(intake);
   liftMotors(up);
   pause(1000);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 
   //Go backwards a little bit
   train.driveFor(reverse, TILE_WIDTH/5, inches);
   pause(250);
 
   //Turn back to expel blue ball
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Expel blue ball
   intakeMotors(expel);
   liftMotors(down);
   pause(1250);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
   train.driveFor(TILE_WIDTH/4, inches);
 
   //Turn to pick up ball
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go forwards to pick up ball (put in the lift motor chamber)
   /*intakeMotors(intake);
   train.setTimeout(2500, msec);
   train.driveFor(TILE_WIDTH, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   liftMotors(up);
   pause(500);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
   pause(250);*/
 
   //Go back to the 2nd goal
   train.driveFor(reverse, TILE_WIDTH/4, inches);
   pause(250);
 
   //Turn towards the 3rd goal
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go to the wall to align itself, picking up ball at the same time, but only start intaking after the
   //robot comes in contact with the ball (this will reduce the chances of ball deflection).
   train.driveFor(2*TILE_WIDTH, inches);
   pause(250);
   intakeMotors(intake);
   train.setTimeout(2000, msec);
   train.driveFor(TILE_WIDTH, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   intakeMotors(stopIntake);
   pause(250);
 
   //Go back from wall to line up with the 3rd goal
   train.driveFor(reverse, TILE_WIDTH/2, inches);
   pause(250);
 
   //Turn towards the goal
   train.turnFor(-45*SIDE, deg);
   pause(250);
 
   //Go up to the goal
   train.setTimeout(500, msec);
   train.driveFor(TILE_DIAGONAL/2, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Score goal and take bottom ball out
   liftMotors(up);
   intakeMotors(intake);
   pause(1000);
   liftMotors(stopLift);
   intakeMotors(stopIntake);
 
   //Move back
   train.driveFor(reverse, TILE_DIAGONAL/8, inches);
   pause(250);
 
   //Turn to look at wall so can expel ball
   train.turnFor(45*SIDE, deg);
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
 
   //Go back to align on wall
   train.setTimeout(1500, msec);
   train.driveFor(reverse, TILE_WIDTH*1.5, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Go to middle line, intaking the ball on the middle line
   intakeMotors(intake);
   train.driveFor(TILE_WIDTH*2.66, inches);
   intakeMotors(stopIntake);
 
   //Turn towards goal B
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go up to goal B
   train.setTimeout(500, msec);
   train.driveFor(TILE_WIDTH/4, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Score in goal B and take blue ball out
   intakeMotors(intake);
   liftMotors(up);
   pause(1000);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 

   //Push the ball into the middle goal
   train.setTimeout(3500, msec);
   train.driveFor(reverse, TILE_WIDTH*2, inches);
   train.setTimeout(BIG_TIMEOUT, msec);

    /*
   //pick up ball
   intakeMotors(intake);
   train.driveFor(TILE_WIDTH, inches);
   intakeMotors(stopIntake);
   pause(250);

   //go back
   train.driveFor(reverse, TILE_WIDTH*0.66, inches);
 
   //Turn back towards goal C
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go towards goal c, and align on the wall, while picking up ball
   //Go forwards, running into the ball to catch it, then use the intake motors to secure it (reduce deflection)
   train.setTimeout(4000, msec);
   train.driveFor(TILE_WIDTH*2, inches);
   intakeMotors(intake);
   train.driveFor(TILE_WIDTH, inches);
   intakeMotors(stopIntake);
   train.setTimeout(BIG_TIMEOUT, msec);
 
   //Go back to be lined up with goal C
   train.driveFor(TILE_WIDTH*1.25, inches);
   pause(250);
 
   //Turn towards goal C
   train.turnFor(-45*SIDE, deg);
   pause(250);
 
   //Go up to goal C
   train.driveFor(TILE_DIAGONAL, inches);
  
   //Score ball (dont worry about getting ball out)
   intakeMotors(intake);
   liftMotors(up);
   pause(750);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 
   //
   // BEGIN REPEATED CODE (SECOND HALF OF THE FIELD)
   //
 
   //Go back from the goal
   train.driveFor(reverse, TILE_DIAGONAL/4, inches);
   pause(250);
 
   //Spit out blue ball(s)
   train.turnFor(SIDE*70, deg);
   liftMotors(down);
   intakeMotors(expel);
   pause(500);
   liftMotors(stopLift);
   intakeMotors(stopIntake);
   train.turnFor(-25*SIDE, deg);
   intakeMotors(expel);
   pause(500); //Probably too much
   intakeMotors(intake);
   pause(500); //If red ball makes it to intake, then suck back up
   intakeMotors(stopIntake);
 
   //Turn to face the middle goal
   train.turnFor(SIDE*135, deg);
   pause(250);
 
   //Go back to align on back wall
   train.setTimeout(1500, msec);
   train.driveFor(reverse, TILE_WIDTH, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Go towards middle goal
   train.driveFor(TILE_WIDTH*2.75, inches);
   pause(250);
 
   //Turn towards the middle goal
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go to the middle goal
   train.setTimeout(500, msec);
   train.driveFor(TILE_WIDTH/4, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
 
   //Take out blue ball and put ball in
   intakeMotors(intake);
   liftMotors(up);
   pause(1000);
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
   pause(1250);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 
   //Turn so can correctly align on line
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go back to the 2nd goal
   train.driveFor(reverse, TILE_WIDTH*1.25, inches);
   pause(250);
 
   //Turn towards the 3rd goal
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go to the wall to align itself, picking up ball at the same time, but only start intaking after the
   //robot comes in contact with the ball (this will reduce the chances of ball deflection).
   train.driveFor(2*TILE_WIDTH, inches);
   pause(250);
   intakeMotors(intake);
   train.setTimeout(2000, msec);
   train.driveFor(TILE_WIDTH, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   intakeMotors(stopIntake);
   pause(250);
  
   //Put the ball in the lift chamber
   intakeMotors(intake);
   liftMotors(up);
   pause(500);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 
   //Go back from wall to line up with the 3rd goal
   train.driveFor(reverse, TILE_WIDTH/2, inches);
   pause(250);
 
   //Turn towards the goal
   train.turnFor(-45*SIDE, deg);
   pause(250);
 
   //Go up to the goal
   train.setTimeout(500, msec);
   train.driveFor(TILE_DIAGONAL/2, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Score goal
   liftMotors(up);
   //intakeMotors(intake);
   pause(1000);
   liftMotors(stopLift);
   //intakeMotors(stopIntake);
 
   //Move back
   train.driveFor(reverse, TILE_DIAGONAL/6, inches);
   pause(250);
 
   //Turn to look at wall so can expel ball
   train.turnFor(45*SIDE, deg);
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
 
   //Go back to align on wall
   train.setTimeout(1500, msec);
   train.driveFor(reverse, TILE_WIDTH*1.5, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Go to middle line, intaking the ball on the middle line
   intakeMotors(intake);
   train.driveFor(TILE_WIDTH*2.75, inches);
   intakeMotors(stopIntake);
 
   //Turn towards goal B
   train.turnFor(-90*SIDE, deg);
   pause(250);
 
   //Go up to goal B
   train.setTimeout(500, msec);
   train.driveFor(TILE_WIDTH/4, inches);
   train.setTimeout(BIG_TIMEOUT, msec);
   pause(250);
 
   //Score in goal B and take blue ball out
   intakeMotors(intake);
   liftMotors(up);
   pause(750);
   intakeMotors(stopIntake);
   liftMotors(stopLift);
 
   //Back from goal B
   train.driveFor(reverse, TILE_WIDTH, inches);
   pause(250);*/

    
    /*
    leftWheelTrainMotor.setVelocity(150, rpm);
    rightWheelTrainMotor.setVelocity(150, rpm);

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
    intakeMotors(stopIntake);*/

}
