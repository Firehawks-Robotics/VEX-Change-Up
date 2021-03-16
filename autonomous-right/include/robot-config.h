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

const int FUNCTION_MOTOR_SPEED = 200; //rpm

const int DRIVE_TRAIN_SPEED = 100;

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
const int TICK_LENGTH = 50;

/**
 * Constant for the number of wheels on the robot. There are 4 wheels.
*/
const int NUM_WHEEL_TRAINS = 2;

/**
 * The percentage of the max speed (200 rpm) that the wheels should move
 * when at full speed. Defaults to 75%.
*/
extern double percentOfMaxSpeed;

/*
  * The rate at which the velocity of the robot's wheel trains moves toward their
  * respective goal velocities. Should be constant so that we have a constant
  * change in the velocity (a linear model).
  *
  * Proportional to the acceleration of the wheels.
  *
  * Can (and should) be modified in the autonomous to make things go smoother.
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
extern double angular_accelerational_constant; 

/**
 * The direction of the wheel motors are determined by their position (not 
 * orientation) on a compass if you look straight ahead, with North being the
 * front of the robot (at the intake).
*/

extern motor rightWheelTrainMotor;
extern motor leftWheelTrainMotor;

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
extern motor liftTopMotor;
/** The right lift motor. Reversed here because it's reversed on the robot. */
extern motor liftBottomMotor;

/**
 * The following are all the controls on the controller. The axes represent
 * one axis of one analog stick.
*/

/** The vertical axis of the left (movement) analog stick */
extern vex::controller::axis forwardAxis; 
/** The horizontal axis of the turning analog axis */
extern vex::controller::axis turningAxis;

/** Button that causes the wheel motor percentOfMaxSpeed to increase. */
extern vex::controller::button speedUp;
/** Button that causes the wheel motor percentOfMaxSpeed to increase. */
extern vex::controller::button speedDown;

/** Button that causes the intake motors to intake and lift balls. */
extern vex::controller::button functionUp;
/** Button that causes the intake motors to expel and bring balls down. */
extern vex::controller::button functionDown;

extern vex::controller::button functionIntake;
extern vex::controller::button functionExpel;

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
