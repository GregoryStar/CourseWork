/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_PLAYER_H_
#define PROJECT_ITERATION2_SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player_motion_handler.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/player_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  /***************************************************************************
  * Member Functions
  **************************************************************************/
  void ResetBattery(void);
  void Reset(void);
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }
  void TimestepUpdate(unsigned int dt);
  void Accept(EventRecharge * e);
  void Accept(EventCollision * e);
  void EventCmd(enum event_commands cmd);
  enum entity_type getEntityType() const {
    return kPlayer;
  }

  double battery_level(void) const { return battery_.level(); }
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle();
  }
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  int id(void) const { return id_; }
  std::string get_name(void) const {
    return "Player" + std::to_string(id());
  }

 private:
  static unsigned int next_id_;

  /**
  * @brief Initial x position of the player.
  */
  double init_x;
  /**
  * @brief Initial y position of the player.
  */
  double init_y;

  int id_;
  double heading_angle_;
  double angle_delta_;
  PlayerBattery battery_;
  PlayerMotionHandler motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  bool frozen_ = false;
  double freezeTime = 600;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_PLAYER_H_ */
