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

double percentOfMaxSpeed = 0.66; //default is 75%

double angular_accelerational_constant = 0.5;

Wheel::Wheel(motor &wheelMotor) {
    this->wheelMotor = &wheelMotor;
}

void Wheel::calculateAcceleratingVelocity() {
    if(abs(goalVelocity-velocity) < abs(acceleration)) { //If the acceleration is close, then just go there now
        velocity = goalVelocity;
    } else if (velocity != goalVelocity) { //Accelerate
        this->acceleration = (int)((this->goalVelocity - this->initialVelocity) * (angular_accelerational_constant));
        this->velocity = this->velocity + this->acceleration;
    }

    if(getVelocity() == 0) {
        wheelMotor->stop(coast);
    } else {
        spin(forward);
    }
}

void Wheel::spin(directionType dir) {
    this->wheelMotor->setVelocity(this->velocity, rpm);
    this->wheelMotor->spin(dir);
}

void Wheel::spin(int velocity, directionType dir) {
    this->wheelMotor->setVelocity(velocity, rpm);
    this->wheelMotor->spin(dir);
}

// VEXcode device constructors
motor rightWheelTrainMotor = motor(PORT11, ratio36_1, false);
motor leftWheelTrainMotor = motor(PORT11, ratio36_1, false);
motor intakeLeftMotor = motor(PORT1, ratio36_1, false);
motor intakeRightMotor = motor(PORT8, ratio36_1, true);
motor liftLeftMotor = motor(PORT5, ratio36_1, false);
motor liftRightMotor = motor(PORT7, ratio36_1, true);

// Wheels
Wheel rightWheelTrain = *new Wheel(rightWheelTrainMotor);
Wheel leftWheelTrain = *new Wheel(leftWheelTrainMotor);

Wheel *wheelTrains[NUM_WHEEL_TRAINS] = {&rightWheelTrain, &leftWheelTrain};

// Controls
vex::controller::axis forwardAxis = mainCon.Axis3;
vex::controller::axis turningAxis = mainCon.Axis4;

vex::controller::button speedUp = mainCon.ButtonL1;
vex::controller::button speedDown = mainCon.ButtonL2;

vex::controller::button functionUp = mainCon.ButtonR1; //Front
vex::controller::button functionDown = mainCon.ButtonR2; //Back

vex::controller::button stopMotors = mainCon.ButtonDown;

// VEXcode generated functions

const int FUNCTION_MOTOR_SPEED = 100; //rpm

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
    //Inititalize the default velocity for motors with unchanging velocities

    intakeLeftMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    intakeRightMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    liftLeftMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);
    liftRightMotor.setVelocity(FUNCTION_MOTOR_SPEED, velocityUnits::rpm);

    debugMenuController(); //Put stuff on debug screen
}
