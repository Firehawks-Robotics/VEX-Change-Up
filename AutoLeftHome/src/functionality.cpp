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

/* WHEEL SELF-CORRECTION
 *    When the wheels brake, they often slip a little bit (and often change the direction of the robot).
 * What if I could prevent the slipping? Well, maybe I can.
 * 
 * Get the average wheel velocity (of each wheel) over the last 10 ticks (each tick is 20 ms, and movement() is called once each tick).
 * If the average wheel velocity is at least double (or in the opposite direction of) the current wheel velocity, then
 * the robot is either slowing or attempting to move in the opposite direction, which could cause the robot to drift.
 * Using the average wheel velocity, the robot should automatically correct for this to do more against slippage than
 * just friction. This can be thought of as anti-lock braking on your car (ABS).
 * 
 * The robot needs to change the wheels' velocity opposite of the average wheel velocity. If the robot is slowing, 
 * which happens when the robot's new speed from the analog sticks is less than half the average speed over the last
 * 10 ticks, then we need our wheel correction. Additionally, if the robot is supposed to move opposite the average velocity
 * of the last 10 ticks, then correction. Note that correction for each wheel is independent of the other wheels (dont happen together).
 *
 * Note that this will not be used during autonomous.
*/

bool movementinput = true;

/* USING LINKED LISTS (likely to use less battery)*/

int numTicks = 0;

Node *neWheelVelHead = new Node; Node *neWheelVelTail = new Node;
Node *nwWheelVelHead = new Node; Node *nwWheelVelTail = new Node;
Node *seWheelVelHead = new Node; Node *seWheelVelTail = new Node;
Node *swWheelVelHead = new Node; Node *swWheelVelTail = new Node;

int avgFromLinkedList(Node *head) {

    int sum = 0;
    int totalNodes = 0;
    Node *current = head;
    while(current->next != 0) {
        sum+=current->vel;
        current = current->next;
        totalNodes++;
    }

    return sum/totalNodes;
}

/* USING ARRAYS (Likely to use more battery) */
/*
//These are the wheel velocities over the last 10 ticks
//We will use integers here to save CPU when doing the calculations
int neWheelVel10Tick[10];
int nwWheelVel10Tick[10];
int seWheelVel10Tick[10];
int swWheelVel10Tick[10];

//Shift the wheel velocity things to the left
//This may be extremely resource intensive (rip the robot's battery)
void shiftVelArray(int velArray[10], int newVel) {
    for(int i = 0; i < 9; i++) { //Note that we dont want to modify the last index yet.
        velArray[i] = velArray[i+1];
    }
    velArray[10] = newVel;
}*/

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
            desired_angle = M_PI;
        }
        
        // Speed derived from analog stick displacement * max rpm * angle
        
        neSpeed = (added_vectors/MAX_AXIS_VALUE)*SPEED*sin(M_PI/4-desired_angle);
        swSpeed = -(added_vectors/MAX_AXIS_VALUE)*SPEED*sin(-3*M_PI/4-desired_angle);

        nwSpeed = (added_vectors/MAX_AXIS_VALUE)*SPEED*sin(3*M_PI/4-desired_angle);
        seSpeed = -(added_vectors/MAX_AXIS_VALUE)*SPEED*sin(-M_PI/4-desired_angle);

    }

    //Turning (Right analog stick)
    //Simply add the speed to the motors
    if(turnvalue < -10 || turnvalue > 10) { //Dont want tiny values to have any effect
        neSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        nwSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        seSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
        swSpeed += SPEED*(turnvalue/MAX_AXIS_VALUE);
    }

    /* BEGINNING IMPLEMENTATION FOR LINKED LIST STUFF FOR WHEEL CORRECTION */

    if(numTicks == 0) { // No ticks have passed, so we need to start the linked list
        neWheelVelHead->vel = neSpeed; neWheelVelTail = neWheelVelHead;
        nwWheelVelHead->vel = nwSpeed; nwWheelVelTail = nwWheelVelHead;
        seWheelVelHead->vel = seSpeed; seWheelVelTail = seWheelVelHead;
        swWheelVelHead->vel = swSpeed; swWheelVelTail = swWheelVelHead;

    } else {
        //We want to record the velocity before the adjustments are added so that
        //the adjustments do not have any affect on themselves next tick or later.

        //Northeast
        neWheelVelTail->next = new Node; //Add new node on end
        neWheelVelTail->next->vel = neSpeed;
        neWheelVelTail = neWheelVelTail->next;

        //Northwest
        nwWheelVelTail->next = new Node; //Add new node on end
        nwWheelVelTail->next->vel = nwSpeed;
        nwWheelVelTail = nwWheelVelTail->next;

        //Southeast
        seWheelVelTail->next = new Node; //Add new node on end
        seWheelVelTail->next->vel = seSpeed;
        seWheelVelTail = seWheelVelTail->next;

        //Southwest
        swWheelVelTail->next = new Node; //Add new node on end
        swWheelVelTail->next->vel = swSpeed;
        swWheelVelTail = swWheelVelTail->next;

        if(numTicks > 10) { //We only want to delete the old head if we have at least 10 records
            neWheelVelHead->next = neWheelVelHead->next->next; //Dispose of old head
            neWheelVelHead = neWheelVelHead->next;

            nwWheelVelHead->next = neWheelVelHead->next->next; //Dispose of old head
            nwWheelVelHead = neWheelVelHead->next;

            seWheelVelHead->next = neWheelVelHead->next->next; //Dispose of old head
            seWheelVelHead = neWheelVelHead->next;

            swWheelVelHead->next = neWheelVelHead->next->next; //Dispose of old head
            swWheelVelHead = neWheelVelHead->next;
        }

        //Now adjust for the possible drifting
        int neavg = avgFromLinkedList(neWheelVelHead); //We also want to know if they are in the opposite direction (in which case, going to drift)
        if(((neSpeed<0) != (neavg<0)) || abs(int(neSpeed)) < abs(neavg)/2) { //We are slowing or going in the opposite direction (GOING TO DRIFT)
            neSpeed -= neavg/4;
        }

        int nwavg = avgFromLinkedList(nwWheelVelHead);
        if(((nwSpeed<0) != (nwavg<0)) || abs(int(nwSpeed)) < abs(nwavg)/2) { //We are slowing or going in the opposite direction (GOING TO DRIFT)
            nwSpeed -= nwavg/4;
        }

        int seavg = avgFromLinkedList(seWheelVelHead);
        if(((seSpeed<0) != (seavg<0)) || abs(int(seSpeed)) < abs(seavg)/2) { //We are slowing or going in the opposite direction (GOING TO DRIFT)
            seSpeed -= seavg/4;
        }

        int swavg = avgFromLinkedList(swWheelVelHead);
        if(((swSpeed<0) != (swavg<0)) || abs(int(swSpeed)) < abs(swavg)/2) { //We are slowing or going in the opposite direction (GOING TO DRIFT)
            swSpeed -= swavg/4;
        }

    }

    neWheel.setVelocity(neSpeed, rpm);
    nwWheel.setVelocity(nwSpeed, rpm);
    seWheel.setVelocity(seSpeed, rpm);
    swWheel.setVelocity(swSpeed, rpm);

    //Brake if the wheel is not supposed to move (Make the motor go back if it moves)
    //Should do some testing to make sure this is actually helpful
    if(neSpeed == 0) { neWheel.setBrake(hold); }
    else neWheel.spin(forward);

    if(nwSpeed == 0) { nwWheel.setBrake(hold); }
    else nwWheel.spin(forward);

    if(seSpeed == 0) { seWheel.setBrake(hold); }
    else seWheel.spin(forward);

    if(swSpeed == 0) { swWheel.setBrake(hold); }
    else swWheel.spin(forward);

    numTicks++; //More ticks

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