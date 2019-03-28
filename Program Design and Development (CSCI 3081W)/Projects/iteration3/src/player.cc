/**
 * @file player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player.h"
#include "src/player_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Player::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Player::Player(const struct player_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  init_x(params->pos.x),
  init_y(params->pos.y),
  battery_(params->battery_max_charge),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  id_(-1) {
  id_ = next_id_++;
    set_color(Color(50, 50, 100, 255));
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Recalculates position and velocity, and also depletes battery.
  *
  * @param dt The amount of time that has passed since the last update.
  */
void Player::TimestepUpdate(uint dt) {
  if (freezeTime > 0) {
    freezeTime -= dt;
  }
  if (freezeTime <= 0) {
    frozen_ = false;
  }
  Position old_pos = get_pos();
  if (!frozen_) {
    // Update heading and speed as indicated by touch sensor
    motion_handler_.UpdateVelocity(sensor_touch_);
    // Use velocity and position to update position
    motion_behavior_.UpdatePosition(this, dt);
    // Deplete battery as appropriate given distance and speed of movement
  }
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Player::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

/**
* @brief Pass along a collision event (from arena) to the touch sensor.
* This method provides a framework in which sensors can get different
* types of information from different sources.
*
* @param e The collision needing to be processed.
*/
void Player::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
  if (e->collided() && e->getCollidedWith() == kSuperBot) {
    frozen_ = true;
    freezeTime = 70;
  }
  if (e-> collided()) {
    if (sensor_touch_.point_of_contact().y <= 0) {
      set_pos(Position(get_pos().x, 0 + get_radius()));
    }
    if (sensor_touch_.point_of_contact().y >= 768) {
      set_pos(Position(get_pos().x, 768 - get_radius()));
    }
    if (sensor_touch_.point_of_contact().x <= 0) {
      set_pos(Position(0 + get_radius(), get_pos().y));
    }
    if (sensor_touch_.point_of_contact().x >= 1024) {
      set_pos(Position(1024 - get_radius(), get_pos().y));
    }
  }


  // The speed is lowered when a collision occurs... this actually is
  // quite problematic, because it creates a tendency to get stuck.
  // Whereas before jitter would just look strange, now there is actually no
  // way out of an improper collision.
  if (e->collided() && motion_handler_.get_speed() > 0) {
    motion_handler_.set_speed(motion_handler_.get_speed() * 0.9);
  }
  battery_.Accept(e);
}

/**
 * @brief Player is given commands which modify speed. These commands
 * currently come from user input.
 *
 * @param cmd The command in question.
 */
void Player::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

/**
 * @brief Resets everything associated with the Player.
 */
void Player::Reset(void) {
  freezeTime = 0;
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
  const Position& p = Position(init_x, init_y);
  set_pos(p);
} /* Reset() */

/**
 * @brief Resets the player battery.
 */
void Player::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
