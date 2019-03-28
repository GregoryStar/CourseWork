/**
 * @file event_distress_call.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */


#ifndef PROJECT_ITERATION2_SRC_EVENT_PROXIMITY_H_
#define PROJECT_ITERATION2_SRC_EVENT_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/entity_type.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
  * @brief An event responsible for carrying information about the type of
  * the proximity of an object.
  */
class EventProximity : public EventBaseClass {
 public:
   /**
    * @brief The constructor for EventProximity.
    *
    */
  EventProximity(const Position& p, double r, enum entity_type t) {
    radius_ = r;
    position = p;
    type = t;
  }

  /**
   * @brief Returns the x position of the recorded object.
   */
  double x() {
    return position.x;
  }

  /**
   * @brief Returns the radius of the recorded object.
   */
  double radius() {
    return radius_;
  }

  /**
   * @brief Returns the y position of the recorded object.
   */
  double y() {
    return position.y;
  }

  /**
   * @brief Returns the type of the recorded object.
   */
  enum entity_type entityType() {
    return type;
  }

  /**
   * @brief Does nothing.
   */
  void EmitMessage(void) {
    int x = 0;
  }

 private:
  Position position;
  enum entity_type type;
  double radius_;
};

NAMESPACE_END(csci3081);


#endif /* PROJECT_ITERATION2_SRC_EVENT_PROXIMITY_H_ */
