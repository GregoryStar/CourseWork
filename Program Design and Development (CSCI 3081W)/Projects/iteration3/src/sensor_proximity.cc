/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */
#include "src/sensor_proximity.h"
#include "src/robot.h"

NAMESPACE_BEGIN(csci3081);

SensorProximity::SensorProximity(Robot* robot, double range, double fov):
  robot_(robot), range_(range), fov_(fov) {}

void SensorProximity::Accept(EventProximity* ep) {
  Position p = robot_->get_pos();
  double deltaX = p.x - ep->x();
  double deltaY = p.y - ep->y();

  double dist = std::sqrt(
      std::pow(deltaX, 2) + std::pow(deltaY, 2));


  // std::cout << "dist " << dist;
  if (dist <= range_ + ep->radius() && dist != 0) {
    double theta = std::atan(deltaY/deltaX)*(180/3.14) + 180;

    while (theta > 360) {
      theta -= 360;
    }
    while (theta < 0) {
      theta += 360;
    }

    double upperBound = robot_->get_heading_angle() + (fov_ / 2);
    double lowerBound = robot_->get_heading_angle() - (fov_ / 2);

    while (upperBound > 360) {
      upperBound -= 360;
    }
    while (upperBound < 0) {
      upperBound += 360;
    }
    while (lowerBound > 360) {
      lowerBound -= 360;
    }
    while (lowerBound < 0) {
      lowerBound += 360;
    }

    if (upperBound < lowerBound) {
      double temp = upperBound;
      upperBound = lowerBound;
      lowerBound = temp;
    }

    double distanceToSet = dist - ep->radius();
    if (theta > lowerBound && theta < upperBound) {
      // std::cout << "set distance is " << (dist - ep->radius());
      if (distanceToSet < distance || distance == -1) {
        distance = distanceToSet;
      }
    }
  }
}

NAMESPACE_END(csci3081);
