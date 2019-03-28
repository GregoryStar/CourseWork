/**
 * @file sensor.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_H_
#define PROJECT_ITERATION3_SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/arena_entity.h"
// #include "src/robot.h"
#include "src/event_collision.h"
#include "src/event_distress_call.h"
#include "src/event_proximity.h"
#include "src/event_type_emit.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;
class Robot;
/**
 * @brief A generalize sensor for all other Sensors to inherit from.
 * It can accept EventDistressCall, EventProximity, EventCollision, and
 * EventTypeEmit. It provides a default implentation for all of them
 * (i.e. a "do nothing" implentation), to allow for polymorphism. An
 * alternative may be to accept EventBaseClass and then cast but this
 * would require an EventType enumeration. A sensor also has an
 * activated state since that's kind of the purpose of a sensor.
 */
class Sensor {
 public:
  /**
   * @brief Accepts an EventDistressCall.
   *
   * @param The Event to be accepted.
   */
  virtual void Accept(EventDistressCall * e) {
    int x = 0;
  }

  /**
   * @brief Accepts an EventProximity.
   *
   * @param The Event to be accepted.
   */
  virtual void Accept(EventProximity * e) {
    int x = 0;
  }

  /**
   * @brief Accepts an EventCollision.
   *
   * @param The Event to be accepted.
   */
  virtual void Accept(EventCollision * e) {
    int x = 0;
  }

  /**
   * @brief Accepts an EventTypeEmit.
   *
   * @param The Event to be accepted.
   */
  virtual void Accept(EventTypeEmit * e) {
    int x = 0;
  }

  /**
   * @brief Returns the activated status of the Sensor.
   */
  virtual bool activated(void) { return activated_; }

  /**
   * @brief Sets the activated status of sensor.
   *
   * @param value The value to be used when setting activated_.
   */
  virtual void activated(bool value) { activated_ = value; }

  /**
   * @brief Deactivates the Sensor. Should also clear certain data in
   * children if overwritten.
   */
  virtual void Reset(void) {
    activated_ = false;
  }

 private:
  bool activated_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION3_SRC_SENSOR_H_
