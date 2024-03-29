/**
 * @file actuator entity_type.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION1_SRC_ENTITY_TYPE_H_
#define PROJECT_ITERATION1_SRC_ENTITY_TYPE_H_

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
enum entity_type {
  kRobot,
  kSuperBot,
  kPlayer,
  kHomeBase,
  kRechargeStation,
  kWall
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_ENTITY_TYPE_H_
