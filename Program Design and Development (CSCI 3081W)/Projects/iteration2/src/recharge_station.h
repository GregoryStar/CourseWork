/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_RECHARGE_STATION_H_
#define PROJECT_ITERATION2_SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Recharges the player's battery when touched by the player.
  */
class RechargeStation: public Obstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const Color& color) :
      Obstacle(radius, pos, color) {}
  std::string get_name(void) const {
    return "Recharge Station";
  }

  enum entity_type getEntityType() {
    return kRechargeStation;
  }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_RECHARGE_STATION_H_ */
