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

// VEXcode devices
extern motor neWheel;
extern motor nwWheel;
extern motor seWheel;
extern motor swWheel;
extern motor intakeLeft;
extern motor intakeRight;
extern motor liftLeft;
extern motor liftRight;

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