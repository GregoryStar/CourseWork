/**
 * @file home_base_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
#ifndef PROJECT_ITERATION2_SRC_HOME_BASE_PARAMS_H_
#define PROJECT_ITERATION2_SRC_HOME_BASE_PARAMS_H_

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
  * @brief Params for the constructor of HomeBase. A collision delta was added
  * because homebase is now mobile.
  */
struct home_base_params : public arena_entity_params {
  home_base_params(void) : collision_delta(),
      arena_entity_params() {}

      // Added a collision_delta since HomeBase is now mobile. Didn't want
      // to change the actual inheritence structure of home_base_params
      // because the unit tests did not compile when I did.
      double collision_delta;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_HOME_BASE_PARAMS_H_
