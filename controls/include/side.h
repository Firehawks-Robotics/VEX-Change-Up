/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       side.h                                                          */
/*    Author:       Sean Johnson (Firehawks Robotics)                               */
/*    Created:      Sun Nov 22 2020                                                 */
/*    Description:  Defines the Autonomous Side                                     */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

/**
 * This file has a special function. It defines the side of the board the robot
 * will be on during the autonomous period.
 *
 * Why is this necessary? Why not just create multiple autonomous programs?
 * This allows us to create one autonomous function, and, using the workflow
 * script `cp_autonomous`, copy all the code, except this file, will be copied
 * from the ChangeUpControls program to the autonomous programs. (The 
 * autonomous program folders should start with 'Auto' for the script to work).
*/

#ifndef SIDE_HEADER_GUARD
#define SIDE_HEADER_GUARD

/**
 * The side that the robot will start on during the autonomous period.
 * During controls testing, there is no autonomous, so the SIDE is 0.
 * When on the left side, the SIDE is -1.
 * When on the right side, the SIDE is 1.
 *
 * Many autonomous procedural calls will have their parameters multiplied by
 * this number. If on the left side during autonomous, then some actions will
 * be reversed (such as turning, direction to move, etc.).
*/
const int SIDE = 0;

#endif