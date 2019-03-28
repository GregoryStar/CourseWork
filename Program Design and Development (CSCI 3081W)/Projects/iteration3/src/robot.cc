/**
 * @file robot.cc
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */
#include "src/robot.h"

NAMESPACE_BEGIN(csci3081);

Robot::Robot(const struct robot_params& params) :
  ArenaMobileEntity(params.radius, params.collision_delta,
    params.pos, params.color),
  init_x(params.pos.x),
  init_y(params.pos.y),
  heading_angle_(220),
  sensor_touch_(),
  motion_handler_(),
  sensor_distress_(this, 100),
  sensor_proximity_(this, 100, 100),
  sensor_entity_type_(this, 100)
  {}

NAMESPACE_END(csci3081);
