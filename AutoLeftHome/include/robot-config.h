/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       robot-config.h                                                  */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Configuration Header Definitions                          */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#ifndef CONFIG_HEADER_GUARD
#define CONFIG_HEADER_GUARD

using namespace vex;

extern brain Brain;

extern controller mainCon;

class Node {
    public:
        int vel = -201; //Cannot be less than -200 (means uninitialized)
    Node * next;
};

/*
 * A wrapper for motor class that implements drift correction.
 * Drift correction includes velocity records for the last 10 ticks (approximately 1/5 of a second)
 * Note the use of 'velocity' instead of 'speed' because direction is also important.
*/
class Wheel {
    protected:
        Node *velRecordsHead;
        Node *velRecordsTail; //The head and the tail should be the same node at first
        int totalVelocityRecords = 0; //When at 10, then we should start deleting the head when new are added

    public:
        Wheel(motor &wheelMotor);
        
        /*
         * double   The velocity at which the motor will be turning (not necessarily at this moment) (measured in rpm)
        */
        double velocity = 0;

        /*
         * motor    The motor that this wheel is controlled by.
        */
        motor *wheelMotor;

        /*
         * Calculates the average velocity over the last 10 ticks using the velocity records
         * The velocity records and the average velocity do not include the velocity modifications made for the
         * drift correction.
         * @returns int   The average velocity of this wheel over the last 10 ticks (about 1/5 of a second)
        */
        int avgVelocity(void);

        /*
         * Adds a velocity record to the end of the linked list. If there are already 10 velocity records, then
         * Remove the head as wheel (that is no longer needed because that was 11 ticks ago).
         * @param int newVelocity  The velocity to be added to the records
        */
        void shiftVelocityRecords(int newVelocity);

        /*
=======
>>>>>>> develop
         * Spins the motor that controls this wheel at the velocity stored in `Wheel#velocity` (measured in rpm)
         * @param directionType dir   The direction defined by vex that you want (forward or backward)
        */
        void spin(directionType dir);

        /*
         * Spins the motor that controls this wheel at a custom velocity (measured in rpm)
         * @param double velocity        The velocity at which this wheel should be spinning (measured in rpm)
         *                            Used for having a different velocity than the one stored in `Wheel#velocity`
         * @param directionType dir   The direction defined by vex that you want (forward or backward)
        */
        void spin(double velocity, directionType dir);
};

// VEXcode devices
extern motor neWheelMotor;
extern motor nwWheelMotor;
extern motor seWheelMotor;
extern motor swWheelMotor;
extern motor intakeLeftMotor;
extern motor intakeRightMotor;
extern motor liftLeftMotor;
extern motor liftRightMotor;

//Wheels
extern Wheel neWheel;
extern Wheel nwWheel;
extern Wheel seWheel;
extern Wheel swWheel;

//Note that I am using pointers here to reference the wheels
const int NUM_WHEELS = 4;
extern Wheel *wheels[NUM_WHEELS]; //Storage so we can use loops to easily modify all wheels without much code

const int MIN_MOVEMENT_AXIS_DISPLACEMENT = 10; //The value the axis needs to be (+ or -) the x and y movement axes need to be (combined) in order to move the robot
//Same value for requirement to turn

//How long each tick lasts
//movement is called each tick during the driver control period
//ticks have no effect during the autonomous period
const int TICK_LENGTH = 20; //ms

//Controls
extern vex::controller::axis omnidirectionalY; //Y-axis of the omnidirectional analog stick
extern vex::controller::axis omnidirectionalX; //X-axis of the omnidirectional analog stick

extern vex::controller::axis turning; //X-axis of the turning analog stick

extern vex::controller::button intakeIn; //Intake In button
extern vex::controller::button intakeOut; //Intake out button (reverse intake)

extern vex::controller::button liftUp; //Lift/shoot button
extern vex::controller::button liftDown; //Lift/shoot button (reverse)

extern vex::controller::button stopMotors; //Stop all motors and brake

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif