/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#include "src/sensor_distress.h"
#include "src/robot.h"

NAMESPACE_BEGIN(csci3081);

SensorDistress::SensorDistress(Robot* robot, double range):
  robot_(robot), range_(range) {}

void SensorDistress::Accept(EventDistressCall* ed) {
  double distressX = ed->x();
  double distressY = ed->y();

  // Find the distance from the distress call to the Robot
  Position p = robot_->get_pos();
  double x = p.x;
  double y = p.y;

  double dist =
   std::sqrt(std::pow(x - distressX, 2) + std::pow(y - distressY, 2));

  if (dist < range_) {
    activated(true);
  } else {
    activated(false);
  }
}

NAMESPACE_END(csci3081);
