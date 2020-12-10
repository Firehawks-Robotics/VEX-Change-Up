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

extern double acc;

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
const int MIN_MOVEMENT_AXIS_DISPLACEMENT = 5;
const int MIN_TURNING_AXIS_DISPLACEMENT = 5;

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
 * The amount that the percentOfMaxSpeed should change per tick when the
 * appropriate control is held down. Is 1% per tick.
*/
double constexpr PERCENTOFMAXSPEEDSTEP = 0.01; 

/**
 * The percentage of the max speed (200 rpm) that the wheels should move
 * when at full speed. Defaults to 75%.
*/
extern double percentOfMaxSpeed;

/**
 * A wrapper for motor class that implements drift correction.
 * Drift correction includes velocity records for the last MAX_VELOCITY_RECORDS ticks (approximately 1/5 of a second)
 * Note the use of 'velocity' instead of 'speed' because direction is also important.
*/
class Wheel {
    private:
        /*
         * double   The velocity at which the motor will be turning (not
         * necessarily at this moment) (measured in rpm).
        */
        double velocity = 0;

        /*
         * double   The velcoity at which we want the motor to be turning soon
         * (measured in rpm). Used for implementing gradual acceleration.
         * To prevent the robot from slipping initially.
        */
        double goalVelocity = 0;

        /*
         * double   The velocity the wheel was moving at when the analog stick moved.
        */
        double initialVelocity = 0;

        /*
         * double   The rate at which the robot's velocity is changing in order
         * to reach the goalVelocity. Proportional to the
         * ANGULAR_ACCELERATIONAL_CONSTANT.
        */
        double acceleration = 0;

    public:
        /*
         * The rate at which the velocity of the robot's wheels moves toward their
         * respective goal velocities. Should be constant so that we have a constant
         * change in the velocity (a linear model).
         *
         * Proportional to the acceleration of the wheels.
         *
         * Should be between 0 and 1. An accelerational constant of 1 means that the
         * wheel's velocity will immediately go up to the goalVelocity (which means
         * there is no gradual acceleration). An accelerational constant of 0 means
         * that the wheel's velocity will never change.
         *
         * A good rule for determining the accelerational constant is using this:
         * ANGULAR_ACCELERATIONAL_CONSTANT = 1/(ticks), where ticks is the number of
         * ticks that should pass between the time the wheel starts accelerating
         * and when it reaches its goalVelocity. 
         *
         * For example, an accelerational constant of 1/20 would result in the wheel
         * accelerating to its goal velocity over 20 ticks (approximately 400 ms or
         * 2/5 of a second when the ticklength is 20 ms).
        */
        static double constexpr ANGULAR_ACCELERATIONAL_CONSTANT = 0.33; 

        /**
         * The default constructor for the Wheel class. It takes the motor it 
         * is intended to wrap, and stores that motor.
        */
        Wheel(motor &wheelMotor);

        /**
         * @returns int   The wheel's current velocity.
        */
        double getVelocity() { return velocity; }

        /**
         * @param double  The new velocity of the wheel.
        */
        void setVelocity(double velocity) {
            this->velocity = velocity;
        }

        /**
         * @returns double    The wheel's goal velocity we want.
        */
        double getGoalVelocity() { return goalVelocity; }

        /**
         * Sets the goal velocity. 
         * Updates the acceleration of the wheel accordingly.
         * @param double    The new goal velocity we want.
        */
        void setGoalVelocity(double goalVel) {
            // Only have change in acceleration if there is a change in goal velocity
            // (We don't want to have the acceleration decrease unnecessarily,
            // particularly in autonomous).
            if(this->goalVelocity != goalVel) { 
                // (final-initial) * accelerational_constant
                this->goalVelocity = goalVel;
                this->initialVelocity = this->velocity;
            }
        }

        /**
         * @return double   The initial velocity.
        */
        double getInitialVelocity() {
            return initialVelocity;
        }

        /**
         * @param double   The initial velocity.
        */
        void setInitialVelocity(double initialVelocity) {
            this->initialVelocity = initialVelocity;
        }

        double getAcceleration() {
            return acceleration;
        }

        /*
         * motor    The motor that this wheel is controlled by.
        */
        motor *wheelMotor;

        /*
         * A method to control drifting and changing of direction when the
         * robot first starts to move. This allows us to gradually change the
         * velocity of the robot so that we do not have kinetic friction
         * between the robot's wheels and the floor.
         *
         * The model for the increase in acceleration should be linear. It
         * should slope up in the case that the desired velocity is positive.
         * The slope will be negative when 
         * This gives us a constant acceleration.
         *
         * The rate at which this occurs is proportional to the 
         * ACCELERATIONAL_CONSTANT, which will allow us to adjust the rate of
         * acceleration so that the driver has the most control over the
         * robot's movement.
         *
         * This will be called once per tick.
         *
         * V = initialV + (acceleration)(time)
        */
        void calculateAcceleratingVelocity();

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

/** Button that causes the wheel motor percentOfMaxSpeed to increase. */
extern vex::controller::button speedUp;
/** Button that causes the wheel motor percentOfMaxSpeed to increase. */
extern vex::controller::button speedDown;

/** Button that causes the intake motors to intake and lift balls. */
extern vex::controller::button functionUp;
/** Button that causes the intake motors to expel and bring balls down. */
extern vex::controller::button functionDown;

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