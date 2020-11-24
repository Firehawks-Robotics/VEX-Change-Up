/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       functionality.h                                                 */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Sun Nov 15 2020                                                 */
/*    Description:  Change Up Motor Functionality Implementation                    */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

#include "functionality.h"
#include "debugMenuTemp.h"

//If not driver mode, then autonomous mode
bool driverMode = true; 

double desired_angle = 0;

//We're gonna have to change the velocity of all the wheels by taking
//the value of both left and right analog sticks.
void movement(double x, double y, double turnvalue) {

    double neSpeed = 0;
    double swSpeed = 0;

    double nwSpeed = 0;
    double seSpeed = 0;

    double added_vectors = sqrt(pow(x, 2) + pow(y, 2));
    if (added_vectors >= 10) {  //We dont want to have the robot move when the analog stick is barely displaced, but really shouldnt be.

        //Omnidirectional (Left analog stick)

        //Prevent dividing by 0 (while still maintaining direction)
        //At large numbers like 100/0.0001, arctan(x) changes very little with each decimal place
        if (x == 0) {
            if (y > 0) {
                desired_angle = M_PI/2;
            } else if (y < 0) {
                desired_angle = -M_PI/2;
            } //y cant be 0 here
        } else {
            desired_angle = atan(y/x);
        }

        //We need to have a 360 angle
        if(x < 0 && y < 0) {
            desired_angle = desired_angle - M_PI;
        } else if(x < 0 && y > 0) {
            desired_angle = desired_angle + M_PI;
        } else if(x < 0 && y == 0) {
            desired_angle = desired_angle + M_PI;
        }
        
        // Speed derived from analog stick displacement * max rpm * angle
        
        neSpeed = (added_vectors/MAX_AXIS_VALUE)*SPEED*sin(M_PI/4-desired_angle);
        swSpeed = -(added_vectors/MAX_AXIS_VALUE)*SPEED*sin(-3*M_PI/4-desired_angle);

        nwSpeed = (added_vectors/MAX_AXIS_VALUE)*SPEED*sin(3*M_PI/4-desired_angle);
        seSpeed = -(added_vectors/MAX_AXIS_VALUE)*SPEED*sin(-M_PI/4-desired_angle);
    }

    //Turning (Right analog stick)
    //Simply add the speed to the motors
    if(turnvalue < -10 || turnvalue > 10) {
        neSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        nwSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        seSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        swSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
    }

    neWheel.setVelocity(neSpeed, rpm);
    nwWheel.setVelocity(nwSpeed, rpm);
    seWheel.setVelocity(seSpeed, rpm);
    swWheel.setVelocity(swSpeed, rpm);

    //Brake if the wheel is not supposed to move (just have the wheel lock)
    //Should do some testing to make sure this is actually helpful
    if(neSpeed == 0) { neWheel.setBrake(hold); }
    else neWheel.spin(forward);

    if(nwSpeed == 0) { nwWheel.setBrake(hold); }
    else nwWheel.spin(forward);

    if(seSpeed == 0) { seWheel.setBrake(hold); }
    else seWheel.spin(forward);

    if(swSpeed == 0) { swWheel.setBrake(hold); }
    else swWheel.spin(forward);

    debugMenuController();
}

/*
 * -1 = Out
 * 0 = Stop
 * 1 = In
*/
void intake(int inOrOut) {
    if(inOrOut == -1) { //Out
        intakeLeft.spin(forward);
        intakeRight.spin(forward);
    } else if(inOrOut == 0) { //Stop
        intakeLeft.stop(hold);
        intakeRight.stop(hold);
    } else if(inOrOut == 1) { //In
        intakeLeft.spin(reverse);
        intakeRight.spin(reverse);
    }  
    debugMenuController();
}

/*
 * -1 = Down
 * 0 = Stop
 * 1 = Up
*/
void lift(int upOrDown) {
    if(upOrDown == -1) { //Down
        liftLeft.spin(forward);
        liftRight.spin(forward);
    } else if(upOrDown == 0) { //Stop
        liftLeft.stop(hold);
        liftRight.stop(hold);
    } else if(upOrDown == 1) { //Up
        liftLeft.spin(reverse);
        liftRight.spin(reverse);
    }
    debugMenuController();
}