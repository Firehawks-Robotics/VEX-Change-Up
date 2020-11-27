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
extern Wheel *wheels[4]; //Storage so we can use loops to easily modify all wheels without much code


//Controls
extern vex::controller::axis omnidirectionalY; //Y-axis of the omnidirectional analog stick
extern vex::controller::axis omnidirectionalX; //X-axis of the omnidirectional analog stick

extern vex::controller::axis turning; //X-axis of the turning analog stick

extern vex::controller::button intakeIn; //Intake In button
extern vex::controller::button intakeOut; //Intake out button (reverse intake)

extern vex::controller::button liftUp; //Lift/shoot button
extern vex::controller::button liftDown; //Lift/shoot button (reverse)

extern vex::controller::button toggleMode; //toggle between driver control and autonomous

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif