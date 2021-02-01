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

double percentOfMaxSpeed = 0.75; //default is 75%

Wheel::Wheel(motor &wheelMotor) {
    this->wheelMotor = &wheelMotor;
}

void Wheel::calculateAcceleratingVelocity() {
    //velocity > goalVelocity
    if(abs(goalVelocity-velocity) < abs(acceleration)) { //If the acceleration is close, then just go there now
        velocity = goalVelocity;
        return; 
    } else if (velocity == goalVelocity) { //Just dont bother doing anything (no acceleration needed)
        return;
    }
    
    this->acceleration = (int)ceil((this->goalVelocity - this->initialVelocity) * (1.0*ANGULAR_ACCELERATIONAL_CONSTANT));

    this->velocity = this->velocity + this->acceleration;
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
motor neWheelMotor = motor(PORT11, ratio36_1, true);
motor nwWheelMotor = motor(PORT20, ratio36_1, true);
motor seWheelMotor = motor(PORT10, ratio36_1, false);
motor swWheelMotor = motor(PORT9, ratio36_1, false);
motor intakeLeftMotor = motor(PORT1, ratio36_1, false);
motor intakeRightMotor = motor(PORT8, ratio36_1, true);
motor liftLeftMotor = motor(PORT5, ratio36_1, false);
motor liftRightMotor = motor(PORT7, ratio36_1, true);

// Wheels
Wheel neWheel = *new Wheel(neWheelMotor);
Wheel nwWheel = *new Wheel(nwWheelMotor);
Wheel seWheel = *new Wheel(seWheelMotor);
Wheel swWheel = *new Wheel(swWheelMotor);

Wheel *wheels[4] = {&neWheel, &nwWheel, &seWheel, &swWheel};

// Controls
vex::controller::axis omnidirectionalY = mainCon.Axis3;
vex::controller::axis omnidirectionalX = mainCon.Axis4;

vex::controller::axis turning = mainCon.Axis1;

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
    intakeLeftMotor.setVelocity(FUNCTION_MOTOR_SPEED, rpm);
    intakeRightMotor.setVelocity(FUNCTION_MOTOR_SPEED, rpm);

    liftLeftMotor.setVelocity(FUNCTION_MOTOR_SPEED, rpm);
    liftRightMotor.setVelocity(FUNCTION_MOTOR_SPEED, rpm);

    percentOfMaxSpeed = 0.75;

    //Create wheel objects

    debugMenuController(); //Put stuff on debug screen
}
