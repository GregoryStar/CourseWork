/**
 * @file actuator_commands.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_COMMANDS_H_
#define PROJECT_ITERATION3_SRC_EVENT_COMMANDS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
 /**
  * @brief An enumeration that contains different movement commands.
  */
enum event_commands {
  // The commands were changed; I originally added COM_FORWARD and
  // COM_BACKWARD, but then replaced them with COM_SPEED_UP and
  // COM_SLOW_DOWN respectively. That's how we were instructed to do this.
  COM_TURN_LEFT,
  COM_TURN_RIGHT,
  COM_SPEED_UP,
  COM_SLOW_DOWN
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_COMMANDS_H_
