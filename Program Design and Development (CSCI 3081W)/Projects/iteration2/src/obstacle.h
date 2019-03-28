/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_OBSTACLE_H_
#define PROJECT_ITERATION2_SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"
#include "src/color.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief An ArenaImmobileEntity that has no other special properties.
  */
class Obstacle: public ArenaImmobileEntity {
 public:
  Obstacle(double radius, const Position& pos,
                   const Color& color);

  std::string get_name(void) const {
    return "Obstacle" + std::to_string(id_);
  }

  enum entity_type getEntityType() const {
    return kObstacle;
  }


 private:
  static uint next_id_;

  int id_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_OBSTACLE_H_ */
