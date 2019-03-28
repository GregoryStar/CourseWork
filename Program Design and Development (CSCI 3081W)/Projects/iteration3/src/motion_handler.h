/**
 * @file motion_handler.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_MOTION_HANDLER_H_
#define PROJECT_ITERATION3_SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The generalized handler for the motion of mobile entities. It
 * technically can be initialized, but it's meant to be abstract.
 */
class MotionHandler {
 public:
   /**
    * @brief The MotionHandler constructor.
    */
  MotionHandler() {
       heading_angle_ = 0;
       speed_ = 0;
       max_speed_ = 5;
       initial_speed_ = speed_;
       initial_heading_angle_ = heading_angle_;
  }

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  virtual void Reset(void) {
    heading_angle_ = initial_heading_angle_;
    speed_ = initial_speed_;
  }

  /**
   * @brief Return the speed.
   */
  virtual double get_speed() { return speed_; }

  /**
   * @brief Sets the speed.
   *
   * @param The speed to be set.
   */
  void set_speed(double sp) {
    speed_ = sp; }

    /**
     * @brief Return the initial speed.
     */
  virtual double get_initial_speed() {
    return initial_speed_;
  }

  /**
   * @brief Gets the initial heading angle.
   */
  virtual double get_initial_heading_angle() {
    return initial_heading_angle_;
  }

  /**
   * @brief Gets the heading angle.
   */
  virtual double get_heading_angle() const { return heading_angle_;}

  /**
   * @brief Sets the heading angle.
   *
   * @param The heading angle to be set.
   */
  virtual void set_heading_angle(double ha) { heading_angle_ = ha; }

  /**
   * @brief Returns the max speed.
   */
  virtual double max_speed() { return max_speed_; }

  /**
   * @brief Sets the max speed.
   *
   * @param The max speed to be set.
   */
  virtual void max_speed(double ms) { max_speed_ = ms; }

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
  double initial_heading_angle_;
  double initial_speed_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_MOTION_HANDLER_H_
