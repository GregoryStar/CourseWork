/**
 * @file common.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_COMMON_H_
#define PROJECT_ITERATION3_SRC_COMMON_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))

#endif  // PROJECT_ITERATION3_SRC_COMMON_H_
