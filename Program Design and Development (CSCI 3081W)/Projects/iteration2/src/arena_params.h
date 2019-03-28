/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION2_SRC_ARENA_PARAMS_H_
#define PROJECT_ITERATION2_SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_params.h"
#include "src/home_base_params.h"
#include "src/robot_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_ROBOTS 5

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief The params for an Arena constructor.
  */
struct arena_params {
  struct player_params player;
  struct arena_entity_params recharge_station;
  struct home_base_params home_base;
  struct robot_params robots[MAX_ROBOTS];
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  size_t n_obstacles;
  size_t n_robots;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_ARENA_PARAMS_H_ */
