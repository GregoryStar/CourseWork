/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */
#include "src/sensor_entity_type.h"
#include "src/robot.h"

NAMESPACE_BEGIN(csci3081);

SensorEntityType::SensorEntityType(Robot* robot, double range):
  robot_(robot), range_(range) {}

void SensorEntityType::Accept(EventTypeEmit* ete) {
  double distressX = ete->x();
  double distressY = ete->y();

  // Find the distance from the distress call to the Robot
  Position p = robot_->get_pos();
  double x = p.x;
  double y = p.y;

  double dist =
   std::sqrt(std::pow(x - distressX, 2) + std::pow(y - distressY, 2));

  if (dist < range_) {
    activated(true);
    type = ete->entityType();
  } else {
    type = kNULL;
    activated(false);
  }
}

NAMESPACE_END(csci3081);
