/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       robot-config.h                                                  */
/*    Author:       Sean Johnson, Richard Wang, Luke Wittbrodt (Firehawks Robotics) */
/*    Created:      Thu Oct 22 2020                                                 */
/*    Description:  Robot Configuration Header                                      */
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
extern motor consumeLeft;
extern motor consumeRight;
extern motor liftLeft;
extern motor liftRight;

//Controls
extern vex::controller::axis omnidirectionalY;
extern vex::controller::axis omnidirectionalX;

extern vex::controller::axis turning;

extern vex::controller::button intakeIn;
extern vex::controller::button intakeOut;

extern vex::controller::button liftUp;
extern vex::controller::button liftDown;

extern vex::controller::button toggleMode;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif