/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:       autonomous.h                                                    */
/*    Author:       Sean Johnson (Firehawks Robotics)                               */
/*    Created:      Sun Nov 22 2020                                                 */
/*    Description:  Autonomous Declarations                                         */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#ifndef AUTONOMOUS_HEADER_GUARD
#define AUTONOMOUS_HEADER_GUARD

#include "vex.h"

using namespace vex;

/**
 * The procedural autonomous.
 * 
 * Basic Process:
 * 1. Robot intakes ball in front of the closest side goal and the bottom ball
 *        in the said goal
 * 2. Robot scores the preload ball into the goal, still holding two balls
 * 3. Robot scores a ball in the middle home zone goal
 * 4. Robot moves to the third home zone goal
 * 5. Robot gives wide enough berth to the ally robot’s starting position (just
          enough to max robot size)
 * 6. Robot scores the third home zone goal with the last ball it is still
 *        holding
*/
void auton();

#endif