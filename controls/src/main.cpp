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


/* CONTROLS MAPPING: (Currently all mapped to button A)
 * Forwards - Button A
 * Backwards - Button A
 * Pull In - Button A
 * Push Out - Button A
 * Lift Up - Button A
 * Lift Down - Button A
 * Turn Right - Button A
 * Turn Left - Button A
*/

/* Notes:
 * 1. Some of the motors are configured to be in reverse
*/

#include "debugMenuTemp.h"

int currentMode = 0;
 
//Why does this exist? idk. I guess I should ask luke
void ChangeModeControl(){
    if(currentMode == 0){
        if(mainCon.ButtonRight.pressing()){
            currentMode = 1;
        }
    } else { //Not really sure why this is necessary but ok
        if(mainCon.ButtonRight.pressing()){
            currentMode = 0;
        }
    }
}
 
void controlInput(){
    debugMenuController();
    ChangeModeControl();
       
    //Omni-directional Movement maintaining orientation

    if(mainCon.)
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

    //Consume the VEX balls
    if(mainCon.ButtonA.pressing()) { //Pull in
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(forward);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(forward);
    } else if(mainCon.ButtonA.pressing()) { //Push out
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(reverse);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(reverse);
    } else {
        consumeLeft.stop();
        consumeRight.stop();
    }

    //Lift the balls
    if(mainCon.ButtonA.pressing()) {  //Lift up
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(forward);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(forward);
    } else if(mainCon.ButtonA.pressing()) {  //Lift down
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(reverse);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(reverse);
    } else {
        consumeLeft.stop();
        consumeRight.stop();
    }
        
    //Arrows move center platform
    if(mainCon.ButtonUp.pressing()) {
        liftLeft.setVelocity(100, vex::velocityUnits::rpm);
        liftLeft.spin(forward);
        liftRight.setVelocity(-100, vex::velocityUnits::rpm);
        liftRight.spin(forward);
    } else if(mainCon.ButtonDown.pressing()) {
        liftRight.setVelocity(-100, vex::velocityUnits::rpm);
        liftRight.spin(forward);
        liftLeft.setVelocity(100, vex::velocityUnits::rpm);
        liftLeft.spin(forward);
    } else {
        liftRight.stop();
        liftLeft.stop();
    }

    vexBrain.Screen.print(currentMode);
    resetDebug();
}

int main() {
    vexcodeInit();
    while(1) {
        controlInput();
    }
}
