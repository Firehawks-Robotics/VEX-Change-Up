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

#include "debugMenuTemp.h"

int currentMode = 0;
 
void snagMode(){
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

//NOTE: Currently, all the controls are mapped to button A

/* CONTROLS MAPPING: (Currently all mapped to button A)
 * Forwards - Button A
 * Backwards - Button A
 * Suck In - Button A
 * Suck Out - Button A
 * Lift Up - Button A
 * Lift Down - Button A
 * Turn Right - Button A
 * Turn Left - Button A
*/
 
void controlInput(){
    debugMenuController();
    snagMode();
       
    //Movement
    if(mainCon.ButtonA.pressing()) { //Forwards
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(forward);

        nwWheel.setVelocity((mainCon.Axis2.value() + 70) * -1, vex::velocityUnits::rpm);
        nwWheel.spin(forward);
    } else if(mainCon.ButtonA.pressing()) { //Backwards
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(reverse);

        nwWheel.setVelocity((mainCon.Axis2.value() + 70) * -1, vex::velocityUnits::rpm);
        nwWheel.spin(reverse);
    } 
    
    if(mainCon.ButtonA.pressing()) { //Turn Right
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(forward);

        nwWheel.setVelocity((mainCon.Axis2.value() + 70) * -1, vex::velocityUnits::rpm);
        nwWheel.spin(forward);
    } else if(mainCon.ButtonA.pressing()) { //Turn Left
        neWheel.setVelocity(mainCon.Axis3.value() + 70, vex::velocityUnits::rpm);
        neWheel.spin(reverse);

        nwWheel.setVelocity((mainCon.Axis2.value() + 70) * -1, vex::velocityUnits::rpm);
        nwWheel.spin(reverse);
    } 

    //Consume the balls
    if(mainCon.ButtonA.pressing()) { //Suck in
        consumeLeft.setVelocity(200, vex::velocityUnits::rpm);
        consumeLeft.spin(forward);

        consumeRight.setVelocity(200, vex::velocityUnits::rpm);
        consumeRight.spin(forward);
    } else if(mainCon.ButtonA.pressing()) { // Suck out
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