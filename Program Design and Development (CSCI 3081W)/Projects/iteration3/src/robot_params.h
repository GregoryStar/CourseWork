/**
 * @file robot_params.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_ROBOT_PARAMS_H_
#define PROJECT_ITERATION3_SRC_ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief Parameters for a Robot.
  */
struct robot_params : public arena_mobile_entity_params {
  robot_params(void) :
      arena_mobile_entity_params() {}
      double angle_delta;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_ROBOT_PARAMS_H_ */
