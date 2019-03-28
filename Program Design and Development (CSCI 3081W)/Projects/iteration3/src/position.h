/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_POSITION_H_
#define PROJECT_ITERATION3_SRC_POSITION_H_

#include "src/common.h"

NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Macros
 ******************************************************************************/
/**
  * @brief Provides position information for various entities in Arena.
  */
struct Position {
  Position(void) : x(0), y(0) { }

  // In the future, these should be changed to doubles
  Position(int in_x, int in_y) : x(in_x), y(in_y) { }
    double x;
    double y;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_POSITION_H_
