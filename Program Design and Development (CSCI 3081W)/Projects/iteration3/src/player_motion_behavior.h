/**
 * @file player_motion_behavior.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_PLAYER_MOTION_BEHAVIOR_H_
#define PROJECT_ITERATION3_SRC_PLAYER_MOTION_BEHAVIOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <Eigen/Dense>
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
  * @brief The motion behavior for Player. Does motion calculations.
  */

class PlayerMotionBehavior {
 public:
  PlayerMotionBehavior(void) {}

  /**
   * @brief Update the position for an ArenaEntity, based on its current
   * position and velocity.
   *
   * PlayerMotionHandler manages the modification to the velocity based on
   * user input and collisions.
   * PlayerMotionBehavior translates velocity and position to a new position.
   * Both of these are straightforward, but the framework allows for more
   * sophisticated models of motion in which each wheel has distinct speed.
   *
   * @param[in] ent The entitity to update.
   */
  void UpdatePosition(class ArenaMobileEntity * const ent, uint dt);
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_PLAYER_MOTION_BEHAVIOR_H_ */
