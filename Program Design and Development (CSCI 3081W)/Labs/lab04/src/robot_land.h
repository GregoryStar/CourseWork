/**
 * @file robot_land.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_LAND_H_
#define SRC_ROBOT_LAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include "src/robot.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * RobotViewer or Tests call \ref set_time and \ref advance_time to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of robots and
 * obstacles).
 *
 *  For now, RobotLand is hard coded to run a simulation of two robots running
 *  around in a circle.  You can see their sensors, but they don't yet respond
 *  to each other or to obstacles.
 */
class RobotLand {
 public:
  RobotLand(void) { sim_time_ = 0.0; robot0 = new Robot(); robot1 = new Robot;}

  /**
   * @brief Set the simulation time for \ref RobotLand.
   *
   * This function will be used mainly for testing purposes, as time flows in a
   * steady forward direction in general simulation.
   *
   * @param[in] t The new simulation time.
   */
  void set_time(double t) {
    sim_time_ = t;
    std::cout << "Setting simulation time to " << sim_time_ << std::endl;
  }

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by.
   */

  // Once the robot class is created, this should call a robot method to
  // advance its position and set the velocity based on dt
  void advance_time(double dt) {
    sim_time_ += dt;
    std::cout << "Advancing simulation time to " << sim_time_ << std::endl;

    // Update the positions of both robots based on their velocities and
    // the time taken.

    // When I wrote robot I was unaware of this function, so I actually keep
    // track of the last time robot was updated. By using the updated sim_time,
    // this leads to an identical result.
    robot0->updateRobotPosition(sim_time_);
    robot1->updateRobotPosition(sim_time_);

    // This part doesn't make sense to me. You say that velocity should be based
    // on dt, but in fact, change in position should be based on velocity. This
    // seems like a backwards way of thinking about things, which leads me to
    // believe that there is some somewhat strange code in this program.
    // I change velcity in an almost random way, and then change position by
    // dt * velocity. This to me seems like the only logical way to deal with
    // this.

    double *rob0_x_vel = new double;
    double *rob0_y_vel = new double;
    double *rob1_x_vel = new double;
    double *rob1_y_vel = new double;

    // I'd prefer to not use pointers honestly, but I'm following the
    // conventions set by RobotLand.
    robot0->getVelocity(rob0_x_vel, rob0_y_vel);
    robot1->getVelocity(rob1_y_vel, rob1_y_vel);


    //Modifies vel
    if(*rob0_x_vel < 20){
      robot0->setVelocity(*rob0_x_vel += 2, *rob0_y_vel);
    }
    else{
      robot0->setVelocity(-20, *rob0_y_vel);
    }
    if(*rob0_y_vel < 20){
      robot0->setVelocity(*rob0_x_vel, *rob0_y_vel += 2);
    }
    else{
      robot0->setVelocity(*rob0_x_vel, -20);
    }

    //
    if(*rob1_x_vel < 87){
      robot1->setVelocity(*rob1_x_vel += 0.5, *rob1_y_vel);
    }
    else{
      robot1->setVelocity(-14, *rob1_y_vel);
    }
    if(*rob1_y_vel < 30){
      robot1->setVelocity(*rob1_x_vel, *rob1_y_vel += 0.5);
    }
    else{
      robot1->setVelocity(*rob1_x_vel, -40);
    }
  }

  /**
   * @brief Get the current simulation time.
   */
  double get_current_time(void) { return sim_time_; }

  /*
   * @brief Get the current # of robots in the arena. Currently a stub.
   *
   * @todo: Actually implement this.
   */
  int get_num_robots(void);

  int get_robot_color(int id);

  void set_robot_color(int id, int color);

  /**
   * @brief Get the current position of the specified robot. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   * @param[out] x_pos The X position of the robot.
   * @param[out] y_pos The Y position of the robot.
   *
   * @return @todo: What does this mean?
   */
  bool get_robot_pos(int id, double *x_pos, double *y_pos);

  /**
   * @brief Get the current velocity of the specified robot. Currently a stub.
   *
   * @todo Actually implement this.
   *
   * @param[in] id The ID of the robot.
   * @param[out] x_vel The X component of velocity.
   * @param[out] y_vel The Y component of velocity.
   *
   * @return @todo what does this mean?
   */
  bool get_robot_vel(int id, double *x_vel, double *y_vel);

  /**
   * @brief Get the radius of the specified robot. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   *
   * @return The robot's radius.
   */
  double get_robot_radius(int id);

  /**
   * @brief Get the angle of the specified robots sensor, in radians. Currently
   * a stub.
   *
   * @todo: Actually implement this.
   *
   * @param id The ID of the robot.
   *
   * @return The sensor angle in radians,
   */
  double get_robot_sensor_angle(int id);

  /**
   * @brief Get the distance of a specified robot's sensor. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   *
   * @return The sensor distance.
   */
  double get_robot_sensor_distance(int id);

  /**
   * @brief Get the # of obstacles currently in RobotLand. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @return The # of obstacles.
   */
  int get_num_obstacles(void);

  /**
   * @brief Get the position of the specified obstacle. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the obstacle.
   * @param[out] x_pos The X component of the position.
   * @param[out] y_pos The Y component of the position.
   *
   * @return @todo What does this mean?
   */
  bool get_obstacle_pos(int id, double *x_pos, double *y_pos);

  /**
   * @brief Get the radius of the specified obstacle.
   *
   * @param[in] id The ID of the obstacle.
   *
   * @return The obstacle's radius.
   */
  double get_obstacle_radius(int id);

 private:
   Robot *robot0;
   Robot *robot1;
  // Hard coding these robots to move in a circle
  double circle_x(double t) { return 512 + 200.0 * cos(t); }
  double circle_y(double t) { return 350 + 200.0 * sin(t); }

  double sim_time_;
};

#endif  // SRC_ROBOT_LAND_H_
