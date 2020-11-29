/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       debugScreen.cpp                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Debug Screen Implementation                               */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

#include "robot-config.h"
#include "functionality.h"
#include "debugScreen.h"

/** The temperature units used to report the temperature on the debug screen */
temperatureUnits u = temperatureUnits::celsius;

/**
 * Displays the current value of the axes of the left analog stick.
*/
void leftAnalogStick() {
    vexBrain.Screen.print("Axis 1 | ");
    vexBrain.Screen.print(mainCon.Axis1.value());
    vexBrain.Screen.print(" | Axis 2 | ");
    vexBrain.Screen.print(mainCon.Axis2.value());
}

/**
 * Displays the current value of the axes of the right analog stick.
*/
void rightAnalogStick() {
    vexBrain.Screen.print("Axis 4 | ");
    vexBrain.Screen.print(mainCon.Axis3.value());
    vexBrain.Screen.print(" | Axis 3 | ");
    vexBrain.Screen.print(mainCon.Axis4.value());
}

/**
 * Displays whether or not the A/B/X/Y buttons are being pressed.
*/
void buttons() {
    vexBrain.Screen.print("A | ");
    vexBrain.Screen.print(mainCon.ButtonA.pressing());
    vexBrain.Screen.print(" | B | ");
    vexBrain.Screen.print(mainCon.ButtonB.pressing());
    vexBrain.Screen.print(" | X | ");
    vexBrain.Screen.print(mainCon.ButtonX.pressing());
    vexBrain.Screen.print(" | Y | ");
    vexBrain.Screen.print(mainCon.ButtonY.pressing());
}

/**
 * Displays whether or not each arrow button is being pressed.
*/
void arrows() {
    vexBrain.Screen.print("v | ");
    vexBrain.Screen.print(mainCon.ButtonDown.pressing());
    vexBrain.Screen.print(" | ^ | ");
    vexBrain.Screen.print(mainCon.ButtonUp.pressing());
    vexBrain.Screen.print(" | > | ");
    vexBrain.Screen.print(mainCon.ButtonRight.pressing());
    vexBrain.Screen.print(" | < | ");
    vexBrain.Screen.print(mainCon.ButtonLeft.pressing());
}

/**
 * Displays whether or not each bumper is being pressed (the back/top buttons).
*/
void bumpers() {
    vexBrain.Screen.print("L1 | ");
    vexBrain.Screen.print(mainCon.ButtonL1.pressing());
    vexBrain.Screen.print(" | L2 | ");
    vexBrain.Screen.print(mainCon.ButtonL2.pressing());
    vexBrain.Screen.print(" | R1 | ");
    vexBrain.Screen.print(mainCon.ButtonR1.pressing());
    vexBrain.Screen.print(" | R2 | ");
    vexBrain.Screen.print(mainCon.ButtonR2.pressing());
}

/**
 * Displays the angle relative to the positive x-axis that is created if a line
 * were drawn between the left analog stick's natural position and its current
 * position.
*/
void movementAngle() {
    vexBrain.Screen.print(" | Angle | ");
    vexBrain.Screen.print(desiredAngle); //from functionality.h
}

/**
 * Displays the temperature of all motors like so:
 *
 * Motor Temperature:
 * ne : 20 | nw : 20 | se : 20 | sw : 20
 * liftleft : 20 | liftright : 20 | intakeleft : 20 | intakeright : 20
*/
void temperature() {
    vexBrain.Screen.print("Motor Temperature:");
    vexBrain.Screen.newLine();

    //Wheels
    vexBrain.Screen.print("ne : ");
    vexBrain.Screen.print(neWheelMotor.temperature(u));
    vexBrain.Screen.print(" | nw : ");
    vexBrain.Screen.print(nwWheelMotor.temperature(u));
    vexBrain.Screen.print(" | se | ");
    vexBrain.Screen.print(seWheelMotor.temperature(u));
    vexBrain.Screen.print(" | sw : ");
    vexBrain.Screen.print(swWheelMotor.temperature(u));
    vexBrain.Screen.newLine();

    //Function motors
    vexBrain.Screen.print("liftleft | ");
    vexBrain.Screen.print(liftLeftMotor.temperature(u));
    vexBrain.Screen.print("| liftright | ");
    vexBrain.Screen.print(liftRightMotor.temperature(u));
    vexBrain.Screen.newLine();
    vexBrain.Screen.print("| intakeleft | ");
    vexBrain.Screen.print(intakeLeftMotor.temperature(u));
    vexBrain.Screen.print("| intakeright | ");
    vexBrain.Screen.print(intakeRightMotor.temperature(u));
}

/**
 * Wipes the debug info from the brain's screen and places the cursor at the
 * origin.
*/
void resetDebug() {
    vex::task::sleep(100);
    vexBrain.Screen.clearLine();
    vexBrain.Screen.clearScreen();
    vexBrain.Screen.setOrigin(0, 0);
}

/**
 * Main function for displaying all the debug information on the screen.
 * Calls the above functions.
*/
void debugMenuController(){
    resetDebug();

    leftAnalogStick();
    vexBrain.Screen.newLine();

    rightAnalogStick();
    vexBrain.Screen.newLine();
    
    buttons();
    vexBrain.Screen.newLine();

    arrows();
    vexBrain.Screen.newLine();

    bumpers();
    vexBrain.Screen.newLine();

    movementAngle();
    vexBrain.Screen.newLine();

    temperature();
    vexBrain.Screen.newLine();
}