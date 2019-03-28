/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_
#define PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/arena_entity.h"
#include "src/sensor.h"
#include "src/event_collision.h"
// #include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

 /**
  * @brief A sensor that's shaped like a cone and is able to detect
  * when another entity is inside of it. It is used for knowing the
  * closeness to another entity.
  */
class SensorProximity : public Sensor {
 public:
   /**
    * @brief The constructor for a Proximity Sensor.
    *
    * @params The Robot it's attached to.
    * @params The range of the sensor.
    * @params The field of view of the sensor.
    */
  SensorProximity(Robot* robot, double range, double fov);

  /**
   * @brief Accepts an EventProximity. Does the calculation for an object
   * in a cone and returns the distance. If it's not in the cone, set the
   * member variable distance to -1.
   *
   * @param The Event to be accepted.
   */
  void Accept(EventProximity* ep);

  /**
   * @brief Sets the range of the Sensor.
   *
   * @param The range to be set.
   */
  void setRange(double r) {
    range_ = r;
  }

  /**
   * @brief Gets the range of the sensor.
   */
  double getRange(void) {
    return range_;
  }

  /**
   * @brief Sets the Field of View of the sensor.
   *
   * @param The FOV to be set.
   */
  void setFOV(double f) {
    fov_ = f;
  }

  /**
   * @brief Gets the Field of View of the sensor.
   */
  double getFOV(void) {
    return fov_;
  }

  /**
   * @brief Returns the distance to an object it's detecting. If
   * the object is out of bounds (i.e. there is nothing in the proximity),
   * then it returns -1.
   */
  double Output() {
    if (activated()) {
      return distance;
    } else {
      return -1;
    }
  }

 private:
  double range_;
  double fov_;
  Robot* robot_;
  double distance = -1;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION2_SRC_SENSOR_PROXIMITY_H_
