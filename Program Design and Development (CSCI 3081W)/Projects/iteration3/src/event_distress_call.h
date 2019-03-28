/**
 * @file event_distress_call.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_
#define PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 /**
  * @brief An event responsible for carrying information about a distress call.
  */
class EventDistressCall : public EventBaseClass {
 public:
   /**
    * @brief The constructor for EventDistressCall.
    */
  explicit EventDistressCall(Position p) {
    position = p;
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
   * @brief Does nothing.
   */
  void EmitMessage(void) {
    // Do nothing... I don't understand the purpose of this function.
    int x = 0;
  }

 private:
  bool activated_;
  Position position;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_
