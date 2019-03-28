/**
 * @file arena_immobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ARENA_IMMOBILE_ENTITY_H_
#define PROJECT_ITERATION1_SRC_ARENA_IMMOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The immobile child of ArenaEntity. These entities can not move.
  */
class ArenaImmobileEntity : public ArenaEntity {
 public:
   /**
    * @brief Constructor for ArenaImmobileEntity
    *
    * @param radius Radius of Entity
    * @param pos Position of Entity
    * @param color Color of entity.
    */
  ArenaImmobileEntity(double radius, const Position& pos,
                    const Color& color) :
      ArenaEntity(radius, pos, color) {}

  /**
   * @brief Since ArenaImmobileEntities are always immobile, return false.
   */
  bool is_mobile(void) { return false; }
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION1_SRC_ARENA_IMMOBILE_ENTITY_H_ */
