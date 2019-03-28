/**
 * @file arena_mobile_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_PARAMS_H_
#define PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief A struct holding the arguments for the constructor of
  * an ArenaMobileEntity.
  */
struct arena_mobile_entity_params : public arena_entity_params {
  /**
   * @brief Constructor for arena_mobile_entity_params
   */
  arena_mobile_entity_params(void) : arena_entity_params(),
                               collision_delta() {}

  double collision_delta;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION1_SRC_ARENA_MOBILE_ENTITY_PARAMS_H_ */
