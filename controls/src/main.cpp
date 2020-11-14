/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       main.cpp                                                        */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thurs Oct 22 2020                                               */
/*    Description:  Change Up Driver Controls                                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// neWheel              motor         ?              (northeast wheel)
// nwWheel              motor         ?              (northwest wheel)
// seWheel              motor         ?              (southeast wheel)
// swWheel              motor         ?              (southwest wheel)
// consumeRight         motor         ?               
// consumeLeft          motor         ?               
// liftLeft             motor         ?               
// liftRight            motor         ?               
// ---- END VEXCODE CONFIGURED DEVICES ----


/* CONTROLS MAPPING:
 * Omnidirectional Movement - Left Analog Stick
 * Turn Left/Right - Right Analog Stick
 * Intake In - Right Bumper
 * Intake Out - Left Bumper
 * Lift/Shoot Up - A
 * Lift/Shoot Down - B
 * Toggle Mode - Right
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugMenuTemp.h"

int currentMode = 0;
 
void ChangeModeControl(){
    if(mainCon.ButtonRight.pressing()){
        if(currentMode == 0){
            currentMode = 1;
        } else {
            currentMode = 0;
        }
    }
}
 
void controlInput(){
    debugMenuController();
    ChangeModeControl();
       
    //Omni-directional Movement maintaining orientation

    /*if(mainCon.ButtonA.pressing()) { //Forwards
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(forward);

        nwWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        nwWheel.spin(forward);

        seWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        seWheel.spin(reverse);

        seWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        seWheel.spin(reverse);
    } else if(mainCon.ButtonA.pressing()) { //Backwards
        seWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        seWheel.spin(reverse);

        swWheel.setVelocity((mainCon.Axis2.value() + 70) * -1, vex::velocityUnits::rpm);
        swWheel.spin(reverse);

        neWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(forward);

        nwWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        nwWheel.spin(forward);
    } else if(mainCon.ButtonA.pressing()) { //Turn Right
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(forward);

        nwWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        nwWheel.spin(forward);

        swWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        swWheel.spin(forward);

        seWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        seWheel.spin(forward);

    } else if(mainCon.ButtonA.pressing()) { //Turn Left
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(reverse);

        nwWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        nwWheel.spin(reverse);

        swWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        swWheel.spin(reverse);

        seWheel.setVelocity(mainCon.Axis2.value() + 70, vex::velocityUnits::rpm);
        seWheel.spin(reverse);
    }*/

    //Ball Intake
    if(intakeIn.pressing()) { //Intake - in
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(forward);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(forward);
    } else if(intakeOut.pressing()) { //Intake - out
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(reverse);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(reverse);
    } else {
        consumeLeft.stop();
        consumeRight.stop();
    }

    //Lift/shoot
    if(liftUp.pressing()) {  //Lift - up
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(forward);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(forward);
    } else if(liftDown.pressing()) {  //Lift - down
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(reverse);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(reverse);
    } else {
        consumeLeft.stop();
        consumeRight.stop();
    }
        
}

int main() {
    vexcodeInit();
    while(1) {
        controlInput();
    }
}
