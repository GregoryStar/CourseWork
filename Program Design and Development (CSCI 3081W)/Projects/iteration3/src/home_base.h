/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_HOME_BASE_H_
#define PROJECT_ITERATION3_SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits.h>
#include <string>
#include <cstdlib>
#include "src/arena_mobile_entity.h"
#include "src/home_base_params.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief When player touches the home base you win.
 */
class HomeBase: public ArenaMobileEntity {
 private:
  /**
  * @brief Heading angle of the home base.
  */
  double heading_angle_;
  /**
  * @brief Speed of the home base.
  */
  double speed_;
  /**
  * @brief Initial heading angle of the home base.
  */
  double initial_heading_angle_;
  /**
  * @brief Initial speed of the home base.
  */
  double initial_speed_;
  /**
  * @brief Initial x position of the home base.
  */
  double ix;
  /**
  * @brief Initial y position of the home base.
  */
  double iy;

 public:
   /**
   * @brief Constructor for home base. Sets the initial values too.
   *
   * @param params The home base params to be used.
   */
  explicit HomeBase(const struct home_base_params* const params) :
    ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color) {
      speed_ = 5;
      initial_speed_ = speed_;
      heading_angle_ = 270;
      initial_heading_angle_ = heading_angle_;
      ix = params->pos.x;
      iy = params->pos.y;
    }
  std::string get_name(void) const { return "Home Base"; }

  // Accepting recharge events makes no sense but it must be done in
  // the current inheritence structure.
  void Accept(EventRecharge * e) {
      double x = 0;
  }

  /**
   * @brief Override TimestepUpdate() and handle the logic directly in HomeBase
   * rather than use PlayerMotionHandler. The nicest solution would
   * probably be to make a general motion handler class and have player
   * motion handler inherit from that, but I've started to favor hacky
   * solutions given the unit testing and complexity of the code.
   *
   * @param dt The amount of time that has passed since the last update.
   */
  void TimestepUpdate(uint dt) {
    // Get the old position so that the calculated delta can be added.
    int oldX = ArenaEntity::get_pos().x;
    int oldY = ArenaEntity::get_pos().y;
    double velMag = speed_ * dt;

    // I guess this should be replaced with some thread-safe version
    // eventually.
    int r = rand();

    // If the random number is greater than a very large integer, then
    // use it to generate a new heading angle. This has to happen fairly
    // infrequently, because it if happens during a collision then errors
    // occur.
    if (r > INT_MAX - 25000000) {
      heading_angle_ += static_cast<double>(r % 360);
    }
    double radAngle = heading_angle_ * (M_PI/180);
    const Position& p = Position(oldX + velMag * std::cos(radAngle),
        oldY + velMag * std::sin(radAngle));
    ArenaEntity::set_pos(p);
  }

  /**
   * @brief Process a collision event. If the collision actually happened,
   * reverse the heading angle.
   *
   * @param e The collision event in question.
   */
  void Accept(EventCollision * e) {
    if (e -> collided()) {
      heading_angle_ = -e->angle_of_contact();
      if (e->point_of_contact().y <= 0) {
        set_pos(Position(get_pos().x, 0 + get_radius()));
      }
      if (e->point_of_contact().y >= 768) {
        set_pos(Position(get_pos().x, 768 - get_radius()));
      }
      if (e->point_of_contact().x <= 0) {
        set_pos(Position(0 + get_radius(), get_pos().y));
      }
      if (e->point_of_contact().x >= 1024) {
        set_pos(Position(1024 - get_radius(), get_pos().y));
      }
    }
  }

  /**
   * @brief Set everything back to their initial values.
   */
  void Reset() {
    const Position& p = Position(ix, iy);
    heading_angle_ = initial_heading_angle_;
    speed_ = initial_speed_;
    set_pos(p);
  }


  enum entity_type getEntityType() const {
    return kHomeBase;
  }

  /**
   * @brief Return heading angle.
   */
  double get_heading_angle(void) const {return heading_angle_;}
  /**
   * @brief Set heading angle.
   *
   * @param ha The heading angle to set.
   */
  void set_heading_angle(double ha) { heading_angle_ = ha;}
  /**
   * @brief Return speed.
   */
  double get_speed(void) {return speed_;}
  /**
   * @brief Set speed.
   *
   * @param sp The speed to set.
   */
  void set_speed(double sp) {speed_ = sp;}
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_HOME_BASE_H_
