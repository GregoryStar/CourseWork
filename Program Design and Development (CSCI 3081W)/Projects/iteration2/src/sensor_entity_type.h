/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_
#define PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/event_type_emit.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

 /**
  * @brief A sensor which returns the type of an entity in its range.
  */
class SensorEntityType : public Sensor {
 public:
   /**
    * @brief The constructor for SensorEntityType.
    *
    * @param The Robot it's attached to.
    * @param The range of the Sensor.
    */
  SensorEntityType(Robot* robot, double range);

  /**
   * @brief Accepts an EventTypeEmit. Calculates the distance from
   * the emit to the Robot and decides whether or not to activate.
   *
   * @param The Event to be accepted.
   */
  void Accept(EventTypeEmit* ete);

  /**
   * @brief Outputs the type of the entity it detects. Output kNULL
   * if nothing is detected.
   */
  enum entity_type Output() {
    return type;
  }

  /**
   * @brief Returns the range of the sensor.
   */
  double getRange() {
    return range_;
  }

  /**
   * @brief Sets the range of the sensor.
   *
   * @param The range to be set.
   */
  void setRange(double r) {
    range_ = r;
  }

 private:
  Robot* robot_;
  double range_;
  enum entity_type type;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION2_SRC_SENSOR_ENTITY_TYPE_H_
