/**
 * @file event_distress_call.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */


#ifndef PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_
#define PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_

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
  * an object it encountered.
  */
class EventTypeEmit : public EventBaseClass {
 public:
   /**
    * @brief The constructor for EventTypeEmit.
    *
    */
  EventTypeEmit(const Position& p, enum entity_type t) {
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
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_ */
