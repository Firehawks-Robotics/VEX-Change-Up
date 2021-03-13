/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       robot-config.cpp                                                */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Configuration Implementation                              */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"
#include "debugScreen.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain vexBrain;
controller mainCon;

double percentOfMaxSpeed = 0;

// VEXcode device constructors
motor rightWheelTrainMotor = motor(PORT1, ratio18_1, true);
motor leftWheelTrainMotor = motor(PORT11, ratio18_1, false);
drivetrain train = drivetrain(leftWheelTrainMotor, rightWheelTrainMotor, WHEELTRAVEL, TRACKWIDTH, WHEELBASE, distanceUnits::mm, 1.0);
motor intakeLeftMotor = motor(PORT10, ratio36_1, true);
motor intakeRightMotor = motor(PORT6, ratio36_1, false);
motor liftTopMotor = motor(PORT5, ratio36_1, false);
motor liftBottomMotor = motor(PORT7, ratio36_1, false);

// Controls
vex::controller::axis forwardAxis = mainCon.Axis3;
vex::controller::axis turningAxis = mainCon.Axis1;

vex::controller::button speedUp = mainCon.ButtonUp;
vex::controller::button speedDown = mainCon.ButtonDown;

vex::controller::button functionUp = mainCon.ButtonL1;
vex::controller::button functionDown = mainCon.ButtonL2;
vex::controller::button functionIntake = mainCon.ButtonR1;
vex::controller::button functionExpel = mainCon.ButtonR2;

vex::controller::button stopMotors = mainCon.ButtonDown;

// VEXcode generated functions

const int FUNCTION_MOTOR_SPEED = 200; //rpm

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
    //Inititalize the default velocity for motors with unchanging velocities

    intakeLeftMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    intakeRightMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    liftTopMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    liftBottomMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);

    debugMenuController(); //Put stuff on debug screen
}
