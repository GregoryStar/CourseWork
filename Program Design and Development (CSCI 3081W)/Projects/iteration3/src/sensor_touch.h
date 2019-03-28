/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_TOUCH_H_
#define PROJECT_ITERATION3_SRC_SENSOR_TOUCH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/event_collision.h"
#include "src/sensor.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a touch sensor. Touch or "bump" sensors are
 * "active" when pressed. For our purposes, imagine a series of bump sensors
 * around the perimeter of the player. A collision will activate the sensor
 * at a particular point of contact, which translates to an angle of contact
 *
 */
class SensorTouch : public Sensor{
 public:
   /**
    * @brief The constructor for SensorTouch.
    */
  SensorTouch();

  /**
   * @brief Returns the point of contact.
   */
  Position point_of_contact() { return point_of_contact_; }

  /**
   * @brief Sets the point of contact.
   *
   * @param The position that the point of contact will be set to.
   */
  void point_of_contact(Position p) {
    point_of_contact_.x = p.x;
    point_of_contact_.y = p.y;
  }


  /**
   * @brief gets the angle of contact.
   */
  double angle_of_contact(void) { return angle_of_contact_; }

  /**
   * @brief Sets the angle of contact.
   *
   * @param The angle of contact to be set.
   */
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief Gives the type of the entity that it's colliding with.
   */
  enum entity_type collidingWithWhat() {
    return collidingWith;
  }

  /**
   * @brief Compute a new reading based on the collision event.
   *
   * Note that collision events can report "no collision" which
   * will inactivate the sensor.
   *
   * @param The collision event to be processed.
   *
   */
  void Accept(EventCollision * e);

  /**
   * @brief The output of the Sensor. If the Sensor is activated return
   * 1, otherwise return 0.
   */
  int Output() {
    if (activated()) {
      return 1;
    } else {
      return 0;
    }
  }

 private:
  enum entity_type collidingWith = kNULL;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_SENSOR_TOUCH_H_
