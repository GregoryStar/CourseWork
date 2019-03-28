/**
 * @file player_battery.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_PLAYER_BATTERY_H_
#define PROJECT_ITERATION3_SRC_PLAYER_BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/position.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The battery for a player.
 */
class PlayerBattery {
 public:
  explicit PlayerBattery(double max_charge) : charge_(max_charge),
                                             max_charge_(max_charge) {}

  /**
   * @brief All players consume SOME power, even when just sitting there not moving.
   */
  double kBASE_DEPLETION = 0.1;

  /**
   * @brief The amount of energy consumed by the player due to its linear speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kLINEAR_SCALE_FACTOR = 0.01;

  /**
   * @brief The amount of energy consumed by the player due to its angular speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kANGULAR_SCALE_FACTOR = 0.01;

  /**
   * @brief Get the current battery level.
   */
  double level(void) const {
    if (charge_ <= 0) {
      return 0;
    } else {
      return charge_;
    }
  }

  /**
   * @brief Handle a recharge event by instantly restoring the player's battery
   * to its maximum value.
   */
  void EventRecharge(void) { charge_ = max_charge_; }

  /**
   * @brief Reset the player's battery to its newly constructed/undepleted state.
   */
  void Reset(void) { EventRecharge(); }

  /**
   * @brief Depletes the battery given the speed of the player and
   * some constants.
   *
   * @param old_post The old position.
   * @param new_pos The new position.
   * @param dt The amount of time that has passed. Using this and the
   * old and new positions, we can calcuate the velocity of the player.
   */
  double Deplete(__unused Position old_pos,
    __unused Position new_pos, __unused double dt);

  /**
   * @brief This is how the battery can be informed a collision occured.
   * Deplete accordingly.
   *
   * @param e The collision event needing to be processed.
   */
  void Accept(EventCollision * e);

 private:
  double charge_;
  double max_charge_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION3_SRC_PLAYER_BATTERY_H_
