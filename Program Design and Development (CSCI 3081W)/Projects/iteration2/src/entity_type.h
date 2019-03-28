/**
 * @file actuator entity_type.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION2_SRC_ENTITY_TYPE_H_
#define PROJECT_ITERATION2_SRC_ENTITY_TYPE_H_

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
  kPlayer,
  kRobot,
  kObstacle,
  kSuperBot,
  kHomeBase,
  kRechargeStation,
  kWall,
  kNULL
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_ENTITY_TYPE_H_
