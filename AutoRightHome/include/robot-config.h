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

/** The brain of our VEX Robot. */
extern brain vexBrain;

/** The one controller we have connected. */
extern controller mainCon;

/**
 * The net displacement (x and y combined using vector addition) from the
 * initial analog position required to have the robot move. Also used for the
 * turning analog stick.
 * 
 * Sometimes, when the driver was not touching the movement analog stick, the
 * robot would move anyway. This is because, despite the fact that it should be
 * at its natural position, the analog stick is moved slightly, so the combined
 * axis values would be something small like 1 or 2. We solve this issue by
 * requiring the analog stick to be a small distance away from its natural
 * position, however big enough so we don't have this problem.
 * 
*/
const int MIN_MOVEMENT_AXIS_DISPLACEMENT = 10;

/**
 * The amount of time that passes during each tick, in milliseconds.
 * Movement() is called each tick during the driver control period
 * Ticks have no effect during the autonomous period
*/
const int TICK_LENGTH = 20;

/**
 * Constant for the number of wheels on the robot. There are 4 wheels.
*/
const int NUM_WHEELS = 4;

/**
 * The number of velocity records we want to hold. These records are used for
 * determining average wheel velocity so we can correct drift.
*/
const int MAX_VELOCITY_RECORDS = 10;

/**
 * Node of a linked list that stores the velocity records.
 * (linked lists: https://www.cprogramming.com/tutorial/lesson15.html)
 * 
 * Linked Lists are more efficient than arrays in this case. We want to be able
 * to shift the list 'to the left' when we add a new velocity record. In other
 * words, we want to move all values to one index less than their current
 * index. By using linked lists, there are no indexes, and all we have to do is
 * add a node on the end and delete the node on the front ('head' or 'root').
 * 
 * If we were to do this with lists, we would have to change the value of each
 * index of the list (which is going to take up cpu and drain the robot's
 * battery). I'm more concerned about draining the battery than using CPU power
 * because, if the robot runs out of battery in the middle of a match, then we
 * pretty much lose the match.
*/
class Node {
    public:
        int vel = -201; //Cannot be less than -200 (means uninitialized)
    Node * next;
};

/**
 * A wrapper for motor class that implements drift correction.
 * Drift correction includes velocity records for the last MAX_VELOCITY_RECORDS ticks (approximately 1/5 of a second)
 * Note the use of 'velocity' instead of 'speed' because direction is also important.
*/
class Wheel {
    protected:
        Node *velRecordsHead;
        Node *velRecordsTail; //The head and the tail should be the same node at first
        int totalVelocityRecords = 0; //When at MAX_VELOCITY_RECORDS, then we should start deleting the head when new are added

    public:
        /**
         * The default constructor for the Wheel class. It takes the motor it 
         * is intended to wrap, and stores that motor.
        */
        Wheel(motor &wheelMotor);
        
        /*
         * double   The velocity at which the motor will be turning (not
         * necessarily at this moment) (measured in rpm).
        */
        double velocity = 0;

        /*
         * motor    The motor that this wheel is controlled by.
        */
        motor *wheelMotor;

        /*
         * Calculates the average velocity over the last MAX_VELOCITY_RECORDS ticks using the velocity records
         * The velocity records and the average velocity do not include the velocity modifications made for the
         * drift correction.
         * @returns int   The average velocity of this wheel over the last MAX_VELOCITY_RECORDS ticks (about 1/5 of a second)
        */
        int avgVelocity(void);

        /*
         * Adds a velocity record to the end of the linked list. If there are already MAX_VELOCITY_RECORDS velocity records, then
         * Remove the head as wheel (that is no longer needed because that was 11 ticks ago).
         * @param int newVelocity  The velocity to be added to the records
        */
        void shiftVelocityRecords(int newVelocity);

        /*
         * Spins the motor that controls this wheel at the velocity stored in
         * `Wheel#velocity` (measured in rpm)
         * @param directionType dir   The direction defined by vex that you
         *                                want (forward or backward).
        */
        void spin(directionType dir);

        /*
         * Spins the motor that controls this wheel at a custom velocity
         * (measured in rpm)
         * @param double velocity     The velocity at which this wheel should
         *                                be spinning (measured in rpm)
         *                            Used for having a different velocity than
         *                                the one stored in `Wheel#velocity`
         * @param directionType dir   The direction defined by vex that you
         *                                want (forward or backward)
        */
        void spin(double velocity, directionType dir);
};

/**
 * The direction of the wheel motors are determined by their position (not 
 * orientation) on a compass if you look straight ahead, with North being the
 * front of the robot (at the intake).
*/

/** The northeast wheel motor. */
extern motor neWheelMotor;
/** The northeast wheel motor. */
extern motor nwWheelMotor;
/** The northeast wheel motor. */
extern motor seWheelMotor;
/** The northeast wheel motor. */
extern motor swWheelMotor; 

/** The left intake motor. Reversed here because it's reversed on the robot. */
extern motor intakeLeftMotor; 
/** The right intake motor. */
extern motor intakeRightMotor;

/**
 * Note for the lift motors: Exactly one MUST reversed, thereby making them
 * both spin in the same direction. If they are not, then they will move the
 * lift gears in oppsite direction and potentially snap the bar running between
 * them.
*/

/** The left lift motor. */
extern motor liftLeftMotor;
/** The right lift motor. Reversed here because it's reversed on the robot. */
extern motor liftRightMotor;

//Wheels
extern Wheel neWheel; /** Represents the northeast wheel */
extern Wheel nwWheel; /** Represents the northwest wheel */
extern Wheel seWheel; /** Represents the southeast wheel */
extern Wheel swWheel; /** Represents the southwest wheel */

/**
 * Stores the wheels so that we can easily iterate over them.
*/
extern Wheel *wheels[NUM_WHEELS]; 

/**
 * The following are all the controls on the controller. The axes represent
 * one axis of one analog stick.
*/

/** The vertical axis of the left (movement) analog stick */
extern vex::controller::axis omnidirectionalY; 
/** The horizontal axis of the left (movement) analog stick */
extern vex::controller::axis omnidirectionalX;

/** The horizontal axis of the right (turning) analog stick (vertical unused) */
extern vex::controller::axis turning;

/** Button that causes the intake motors to intake objects. */
extern vex::controller::button intakeIn;
/** Button that causes the intake motors to expel objects. */
extern vex::controller::button intakeOut;

/** Button that causes the lift motors to lift objects. */
extern vex::controller::button liftUp;
/** Button that causes the lift motors to make objects go down. */
extern vex::controller::button liftDown;

/**
 * Button that immediately stops all motors and makes them brake (using
 * brakeType brake).
 *
 * An extremely rare phenomenon is that the motors don't stop moving, refuze
 * to change direction, or otherwise become unresponsive. If this were to
 * happen during a match, this could cause problems. If the robot starts to run
 * away, then hit this button to immediately stop it from moving. 
*/
extern vex::controller::button stopMotors;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif