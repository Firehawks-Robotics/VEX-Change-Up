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
#include "autonomous.h"

/** The temperature units used to report the temperature on the debug screen. */
temperatureUnits u = temperatureUnits::celsius;

void leftAnalogStick() {
    vexBrain.Screen.print("Axis 1 | ");
    vexBrain.Screen.print(mainCon.Axis1.value());
    vexBrain.Screen.print(" | Axis 2 | ");
    vexBrain.Screen.print(mainCon.Axis2.value());
}

void rightAnalogStick() {
    vexBrain.Screen.print("Axis 4 | ");
    vexBrain.Screen.print(mainCon.Axis3.value());
    vexBrain.Screen.print(" | Axis 3 | ");
    vexBrain.Screen.print(mainCon.Axis4.value());
}

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

void temperature() {
    if(u == temperatureUnits::celsius) { vexBrain.Screen.print("Motor Temperature: (celcius)"); }
    if(u == temperatureUnits::fahrenheit) { vexBrain.Screen.print("Motor Temperature: (fahrenheit)"); }
    vexBrain.Screen.newLine();

    //Wheels
    vexBrain.Screen.print("rw : ");
    vexBrain.Screen.print(rightWheelTrainMotor.temperature(u));
    vexBrain.Screen.print(" | lw : ");
    vexBrain.Screen.print(leftWheelTrainMotor.temperature(u));
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

void print_rpm() {
    vexBrain.Screen.newLine();
    vexBrain.Screen.print("Motor RPM: ");
    vexBrain.Screen.newLine();
    vexBrain.Screen.print("rw : ");
    vexBrain.Screen.print(rightWheelTrain.getVelocity());
    vexBrain.Screen.print(" | lw : ");
    vexBrain.Screen.print(leftWheelTrain.getVelocity());
    vexBrain.Screen.newLine();
}


void resetDebug() {
    vex::task::sleep(100);
    vexBrain.Screen.clearLine();
    vexBrain.Screen.clearScreen();
    vexBrain.Screen.setOrigin(0, 0);
}


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

    print_rpm();
    vexBrain.Screen.newLine();

    temperature();
    vexBrain.Screen.newLine();
}

void number(double numb) { //Use this to get numbers
    vexBrain.Screen.clearLine();
    vexBrain.Screen.clearScreen();
    vexBrain.Screen.setOrigin(0, 0);
    vexBrain.Screen.print(numb);
    vexBrain.Screen.print(" ");
}