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

// VEXcode devices
extern motor neWheel;
extern motor nwWheel;
extern motor seWheel;
extern motor swWheel;
extern motor consumeLeft;
extern motor consumeRight;
extern motor liftLeft;
extern motor liftRight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif