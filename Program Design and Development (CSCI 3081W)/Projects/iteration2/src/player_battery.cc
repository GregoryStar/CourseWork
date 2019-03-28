/**
 * @file player_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <cmath>
#include "src/player_battery.h"
#include "src/position.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double PlayerBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
    if (dt <= 0) {
      return charge_;
    }
    double x1 = static_cast<double>(old_pos.x);
    double y1 = static_cast<double>(old_pos.y);
    double x2 = static_cast<double>(new_pos.x);
    double y2 = static_cast<double>(new_pos.y);

    // Calculate depletion base on base depletion and how far you've moved.
    double d = std::sqrt(std::pow((x2-x1), 2) + std::pow((y2-y1), 2));
    double velocity = d/dt;
    charge_ -= kBASE_DEPLETION * dt + kLINEAR_SCALE_FACTOR * velocity;
    /* @todo deplete battery by some value based on movement and speed */
    printf("current charge = %f\n", charge_);
    if (charge_ <= 0) {
      charge_ = 0;
    }
    return charge_;
} /* deplete() */


/**
 * @brief Decreases the charge of the battery by a constant amount whenever
 * a collision occurs.
 *
 * @param e The collision event that needs to be processed.
 */
void PlayerBattery::Accept(__unused EventCollision * e) {
  if (e->collided()) {
    charge_ -= 10;
    if (charge_ <= 0) {
      charge_ = 0;
    }
  }
}

NAMESPACE_END(csci3081);
