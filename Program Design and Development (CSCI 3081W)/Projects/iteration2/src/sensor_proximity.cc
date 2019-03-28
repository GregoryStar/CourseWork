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
  if (dist > range_ + ep->radius()) {
    activated(false);
  }

  double triangle_theta = std::abs(std::atan((ep->radius())/dist)*180/3.14);
  double distance_theta = std::abs(std::atan2(deltaY, deltaX)*180/3.14);
  double sensor_lower = robot_->get_heading_angle() - fov_ / 2;
  double sensor_upper = robot_->get_heading_angle() + fov_ / 2;
  double sensed_lower = distance_theta - triangle_theta;
  double sensed_upper = distance_theta + triangle_theta;

  if (sensor_lower > sensor_upper) {
    double temp = sensor_lower;
    sensor_lower = sensor_upper;
    sensor_upper = temp;
  }
  if (sensed_lower > sensed_upper) {
    double temp = sensed_lower;
    sensed_lower = sensed_upper;
    sensed_upper = temp;
  }
  if (sensed_lower >= sensor_lower && sensor_lower <= sensor_upper) {
    activated(true);
    distance = dist;
  } else if (sensed_upper >= sensor_lower && sensed_upper <= sensor_upper) {
    activated(true);
    distance = dist;
    // if(dist > 100){
    //   dist = 100;
    // }
    // if(dist < 1 && dist != -1){
    //   dist = 1;
    // }
  } else {
    activated(false);
    distance = -1;
  }
}

NAMESPACE_END(csci3081);
