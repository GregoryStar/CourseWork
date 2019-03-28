/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_ARENA_MOBILE_ENTITY_H_
#define PROJECT_ITERATION3_SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The mobile child of ArenaEntity. ArenaMobileEntities can move.
  */
class ArenaMobileEntity : public ArenaEntity {
 public:
   /**
    * @brief Constructor of ArenaMobileEntity
    *
    * @param radius Radius of Entity.
    * @param collision_delta When distances between entities are less then
    * collision_delta, a collision is registered.
    * @param pos Position of Entity represented as a Position struct.
    * @param color Color of Entity represented as a Color struct.
    */
  ArenaMobileEntity(double radius, double collision_delta,
                    const Position& pos, const Color& color) :
      ArenaEntity(radius, pos, color),
      collision_delta_(collision_delta) {}
  /**
   * @brief Will always return true because ArenaMobileEntities are mobile.
   */
  bool is_mobile(void) { return true; }
  /**
   * @brief Will return direction of movement of Entity when implemented.
   */
  virtual double get_heading_angle(void) const = 0;
  /**
   * @brief Will set the direction of movement of Entity when implemented.
   *
   * @param heading_angle The heading angle to set.
   */
  virtual void set_heading_angle(double heading_angle) = 0;
  /**
   * @brief Will return the speed of the Entity when implemented.
   */
  virtual double get_speed(void) = 0;
  /**
   * @brief Will set the speed of the Entity when implemented.
   *
   * @param sp The speed to set.
   */
  virtual void set_speed(double sp) = 0;
  /**
   * @brief Will return the collision delta when implemented.
   */
  double get_collision_delta(void) const { return collision_delta_; }
  /**
   * @brief Will set the collision delta of the Entity.
   *
   * @param delta The collision delta to set.
   */
  double get_collision_delta(double delta) { collision_delta_ = delta; }
  /**
   * @brief Updates the time which should cause a mobile entity to move
   * based on its current speed and other factors.
   *
   * @param dt The amount of time that has passed since the last update.
   */
  virtual void TimestepUpdate(uint dt);
  /**
   * @brief Processes collision events.
   *
   * @param e The collision event that needs to be processed.
   */
  virtual void Accept(EventCollision * e) = 0;
  /**
   * @brief Processes recharge events.
   *
   * @param e The Recharge event that needs to be processed.
   */
  virtual void Accept(EventRecharge * e) = 0;

 private:
  double collision_delta_;
};

NAMESPACE_END(csci3081);

#endif /* PROJECT_ITERATION3_SRC_ARENA_MOBILE_ENTITY_H_ */
