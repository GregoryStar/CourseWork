/**
 * @file robot_land.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_land.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Still going to return 2 because I've chosen to make 2 robot objects rather
// than making an array.
int RobotLand::get_num_robots(void) { return 2; }

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
bool RobotLand::get_robot_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    robot0->getPosition(x_pos, y_pos);
    return true;
  } else if (id == 1) {
    robot1->getPosition(x_pos, y_pos);
    return true;
  } else {
    return false;
  }
}

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
// Notice the use of "id" -- how will you handle this in your robot class??
bool RobotLand::get_robot_vel(int id, double *x_vel, double *y_vel) {
  if (id == 0) {
    robot0->getVelocity(x_vel, y_vel);
    return true;
  } else if (id == 1) {
    robot1->getVelocity(x_vel, y_vel);
    return false;
  }
}

// Hard coded for now...
double RobotLand::get_robot_radius(int id) {
  if(id == 0){
    return robot0->getRadius();
  }
  else if(id == 1){
    return robot1->getRadius();
  }
  else{
    return 0;
  }
}

int RobotLand::get_robot_color(int id){
  if(id == 0){
    return robot0->getColor();
  }
  else if(id == 1){
    return robot1->getColor();
  }
  else{
    return 0;
  }
}
void RobotLand::set_robot_color(int id, int color){
  if(id == 0){
    robot0->setColor(color);
  }
  else if(id == 1){
    robot1->setColor(color);
  }
  else{

  }
}

// Hard coded for now...  in radians
double RobotLand::get_robot_sensor_angle(int id) { return 2.0; }

// Hard coded for now...
double RobotLand::get_robot_sensor_distance(int id) {
  return 3.0 * get_robot_radius(id);
}

// Hard coded for now...
int RobotLand::get_num_obstacles() { return 1; }

// Hard coded for now...
bool RobotLand::get_obstacle_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    *x_pos = 200;
    *y_pos = 300;
    return true;
  }
  return false;
}

// Hard coded for now...
double RobotLand::get_obstacle_radius(int id) { return 75; }
