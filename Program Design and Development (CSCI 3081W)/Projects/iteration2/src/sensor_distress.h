/**
 * @file sensor_distress.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_SENSOR_DISTRESS_H_
#define PROJECT_ITERATION2_SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/event_distress_call.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief A sensor that can sense distress calls, which robots emit when
 * they're frozen.
 */
class SensorDistress : public Sensor {
 public:
   /**
    * @brief The constructor for a SensorDistress.
    *
    * @param The Robot the Sensor is attached to.
    * @param The range of the sensor.
    */
  SensorDistress(Robot* robot, double range);

  /**
   * @brief Accepts an EventDistressCall. Finds the distance from
   * the distress call to the robot, and then decides whether to activate
   * or not.
   *
   * @param The Event to be accepted.
   */
  void Accept(EventDistressCall * ed);

  /**
   * @brief Output 1 if it detects a distress call and 0 otherwise.
   */
  int Output() {
    if (activated()) {
      return 1;
    } else {
      return 0;
    }
  }

  double getRange() {
    return range_;
  }

  void setRange(double r) {
    range_ = r;
  }

 private:
  double range_;
  Robot* robot_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION2_SRC_SENSOR_DISTRESS_H_
