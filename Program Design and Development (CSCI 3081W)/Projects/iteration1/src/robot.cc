/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
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
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Recalculates position and velocity, and also depletes battery.
  *
  * @param dt The amount of time that has passed since the last update.
  */
void Robot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Robot::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

/**
* @brief Pass along a collision event (from arena) to the touch sensor.
* This method provides a framework in which sensors can get different
* types of information from different sources.
*
* @param e The collision needing to be processed.
*/
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
  // The speed is lowered when a collision occurs... this actually is
  // quite problematic, because it creates a tendency to get stuck.
  // Whereas before jitter would just look strange, now there is actually no
  // way out of an improper collision.
  if (e->collided() && motion_handler_.get_speed() > 0) {
    motion_handler_.set_speed(motion_handler_.get_speed() - 1);
  }
  battery_.Accept(e);
}

/**
 * @brief Robot is given commands which modify speed. These commands
 * currently come from user input.
 *
 * @param cmd The command in question.
 */
void Robot::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

/**
 * @brief Resets everything associated with the Robot.
 */
void Robot::Reset(void) {
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
  const Position& p = Position(init_x, init_y);
  set_pos(p);
} /* Reset() */

/**
 * @brief Resets the robot battery.
 */
void Robot::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
