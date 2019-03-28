/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_
#define PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A generalize sensor has an activated state which can be
 * activated, and then reset. That's the only thing I could come up
 * with from our already small definition of a SensorTouch.
 */
class SensorDistress : public Sensor {
 public:
   
 private:
   double range;
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_ */
