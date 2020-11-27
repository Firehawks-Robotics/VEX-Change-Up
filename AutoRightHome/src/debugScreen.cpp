/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       debugScreen.cpp                                               */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Debug Screen Implementation                               */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
brain vexBrain;

#include "robot-config.h"
#include "functionality.h"
#include "debugScreen.h"

temperatureUnits u = temperatureUnits::celsius;

//Controllers
controller mainCon;

void rightTrigger(){
    vexBrain.Screen.print("Axis 1 | ");
    vexBrain.Screen.print(mainCon.Axis1.value());
    vexBrain.Screen.print(" | Axis 2 | ");
    vexBrain.Screen.print(mainCon.Axis2.value());
}

void leftTrigger(){
    vexBrain.Screen.print("Axis 4 | ");
    vexBrain.Screen.print(mainCon.Axis3.value());
    vexBrain.Screen.print(" | Axis 3 | ");
    vexBrain.Screen.print(mainCon.Axis4.value());
}

void buttons(){
    vexBrain.Screen.print("A | ");
    vexBrain.Screen.print(mainCon.ButtonA.pressing());
    vexBrain.Screen.print(" | B | ");
    vexBrain.Screen.print(mainCon.ButtonB.pressing());
    vexBrain.Screen.print(" | X | ");
    vexBrain.Screen.print(mainCon.ButtonX.pressing());
    vexBrain.Screen.print(" | Y | ");
    vexBrain.Screen.print(mainCon.ButtonY.pressing());
}

void arrows(){
    vexBrain.Screen.print("v | ");
    vexBrain.Screen.print(mainCon.ButtonDown.pressing());
    vexBrain.Screen.print(" | ^ | ");
    vexBrain.Screen.print(mainCon.ButtonUp.pressing());
    vexBrain.Screen.print(" | > | ");
    vexBrain.Screen.print(mainCon.ButtonRight.pressing());
    vexBrain.Screen.print(" | < | ");
    vexBrain.Screen.print(mainCon.ButtonLeft.pressing());
}

void backButtons(){
    vexBrain.Screen.print("L1 | ");
    vexBrain.Screen.print(mainCon.ButtonL1.pressing());
    vexBrain.Screen.print(" | L2 | ");
    vexBrain.Screen.print(mainCon.ButtonL2.pressing());
    vexBrain.Screen.print(" | R1 | ");
    vexBrain.Screen.print(mainCon.ButtonR1.pressing());
    vexBrain.Screen.print(" | R2 | ");
    vexBrain.Screen.print(mainCon.ButtonR2.pressing());
}

void movementAngle() {
    vexBrain.Screen.print(" | Angle | ");
    vexBrain.Screen.print(desired_angle); //from functionality.h
}

//Temperature of all the motors
void temperature() {
    vexBrain.Screen.print("Motor Temperature:");
    vexBrain.Screen.newLine();

    //Wheels
    vexBrain.Screen.print("nw | ");
    vexBrain.Screen.print(nwWheelMotor.temperature(u));
    vexBrain.Screen.print(" | ne | ");
    vexBrain.Screen.print(nwWheelMotor.temperature(u));
    vexBrain.Screen.print(" | sw | ");
    vexBrain.Screen.print(nwWheelMotor.temperature(u));
    vexBrain.Screen.print(" | sw | ");
    vexBrain.Screen.print(nwWheelMotor.temperature(u));

    //Function motors
    vexBrain.Screen.print("liftleft | ");
    vexBrain.Screen.print(liftLeftMotor.temperature(u));
    vexBrain.Screen.print("| liftright | ");
    vexBrain.Screen.print(liftRightMotor.temperature(u));
    vexBrain.Screen.print("| intakeleft | ");
    vexBrain.Screen.print(intakeLeftMotor.temperature(u));
    vexBrain.Screen.print("| intakeright | ");
    vexBrain.Screen.print(intakeRightMotor.temperature(u));
}

void resetDebug() {
    vex::task::sleep(100);
    vexBrain.Screen.clearLine();
    vexBrain.Screen.clearScreen();
    vexBrain.Screen.setOrigin(0, 0);
}

void debugMenuController(){
    resetDebug();

    rightTrigger();
    vexBrain.Screen.newLine();

    leftTrigger();
    vexBrain.Screen.newLine();
    
    buttons();
    vexBrain.Screen.newLine();

    arrows();
    vexBrain.Screen.newLine();

    backButtons();
    vexBrain.Screen.newLine();

    movementAngle();
    vexBrain.Screen.newLine();

    temperature();
    vexBrain.Screen.newLine();
}