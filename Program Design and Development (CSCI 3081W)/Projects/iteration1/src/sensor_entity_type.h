/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_ENTITY_TYPE_H_
#define PROJECT_ITERATION1_SRC_SENSOR_ENTITY_TYPE_H_

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

class SensorEntityType : public Sensor {
 public:
 private:
   double range;
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION1_SRC_SENSOR_ENTITY_TYPE_H_ */
