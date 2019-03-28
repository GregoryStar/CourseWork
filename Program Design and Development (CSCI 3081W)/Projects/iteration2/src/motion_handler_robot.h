/**
 * @file motion_handler_robot.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_MOTION_HANDLER_ROBOT_H_
#define PROJECT_ITERATION2_SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_handler.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The motion handler tailored the Robot. It doesn't accept keypress
 * commands like the motion handler for player.
 */
class MotionHandlerRobot : MotionHandler {
 public:
   /**
    * @brief The constructor for MotionHandlerRobot.
    */
  MotionHandlerRobot() {
    heading_angle_ = 220;
    speed_ = 5;
    max_speed_ = 5;
    initial_speed_ = speed_;
    initial_heading_angle_ = heading_angle_;
  }

  /**
  * @brief Reset stuff.
  */
  void Reset(void) {
    heading_angle_ = initial_heading_angle_;
    speed_ = initial_speed_;
  }

  /**
   * @brief Return 0 when frozen, otherwise return speed_.
   */
  double get_speed() {
    if (frozen) {
      return 0;
    } else {
      return speed_;
    }
  }

  /**
   * @brief Increase speed while it's lower than max_speed_ unless
   * frozen. This was in anticipation of slowing down for other entities,
   * but did not materialize because of how buggy that code was.
   */
  void updateSpeed() {
    if (!frozen && speed_ < max_speed_) {
      speed_ += 0.3;
    }
  }

  /**
   * @brief Sets the speed.
   *
   * @param The speed to be set.
   */
  void set_speed(double sp) {
    speed_ = sp; }

    /**
     * @brief Get the initial speed.
     */
  double get_initial_speed() {
    return initial_speed_;
  }

  /**
   * @brief Sets the status of proximity.
   *
   * @param The proximity to be set.
   */
  void set_proximity(bool b) {
    proximity = b;
  }

  /**
   * @brief Sets the frozen status.
   *
   * @param The frozen status to be set.
   */
  void set_frozen(bool b) {
    frozen = b;
  }

  /**
   * @brief Get the initial heading angle.
   */
  double get_initial_heading_angle() {
    return initial_heading_angle_;
  }

  /**
   * @brief Get the heading angle.
   */
  double get_heading_angle() const { return heading_angle_;}

  /**
   * @brief Sets the heading angle.
   *
   * @param The heading angle to be set.
   */
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  /**
   * @brief Gets the max speed.
   */
  double max_speed() { return max_speed_; }

  /**
   * @brief Sets the max speed.
   *
   * @param The max speed to be set.
   */
  void max_speed(double ms) { max_speed_ = ms; }

 private:
  bool frozen = false;
  bool proximity = false;
  double heading_angle_;
  double speed_;
  double max_speed_;
  double initial_heading_angle_;
  double initial_speed_;
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION2_SRC_MOTION_HANDLER_ROBOT_H_ */
