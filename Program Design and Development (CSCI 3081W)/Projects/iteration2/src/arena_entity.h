/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_
#define PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include "src/position.h"
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
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 *
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Note that not all classes need to be able to do these two things.
 */
class ArenaEntity {
 public:
  ArenaEntity(double radius, const Position& pos,
              const Color& color) :
      radius_(radius), pos_(pos), color_(color) {}
  virtual ~ArenaEntity(void) {}

  /**
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /**
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}


  virtual enum entity_type getEntityType() const = 0;

  /**
   * @brief Return name of entity.
   */
  virtual std::string get_name(void) const = 0;

  /**
   * @brief Set the position of an entity using Position struct.
   */
  void set_pos(const Position& pos) { pos_ = pos; }

  /**
   * @brief Returns the position of the entity as a Position struct.
   */
  const Position& get_pos(void) const { return pos_; }

  /**
   * @brief Returns the color of the entity as a Color struct.
   */
  const Color& get_color(void) const { return color_; }
  /**
   * @brief Sets the color of the entity.
   *
   * @param color The color to set.
   */
  void set_color(const Color& color) { color_ = color; }
  /**
   * @brief Should return whether it's mobile or not when implemented.
   */
  virtual bool is_mobile(void) = 0;
  /**
   * @brief Returns the radius of the entity.
   */
  double get_radius(void) const { return radius_; }

 private:
  double radius_;
  Position pos_;
  Color color_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION2_SRC_ARENA_ENTITY_H_ */
