/**
 * @file robot.h
 *
 * @copyright 2017 Gregory Star, All rights reserved.
 */

#ifndef PROJECT_ITERATION2_SRC_ROBOT_H_
#define PROJECT_ITERATION2_SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <string>
#include "src/arena_mobile_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/color.h"
#include "src/robot_params.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_touch.h"
#include "src/entity_type.h"
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief An autonomous entity that moves around the Arena. It is frozen
  * when player collides with it, and unfreezes when another Robot collides
  * with it. Also, it can turn into a SuperBot, which has all the same
  * functionality of a Robot but freezes the player rather than freezing
  * itself. If all Robots turn into SuperBots, the game is lost. If all
  * Robots are frozen, the game is won.
  *
  * NOTE that Robots double as SuperBots, as their behavior is so similar
  * that inheritance seemed unnecessary.
  *
  * This class was complicated to code because of the circular dependency
  * between the Sensors and Robot. I guess I coded it up too quickly,
  * because there are many strange methods here that either do nothing
  * or don't do what they're supposed to do. I am afraid to modify or delete
  * them because we are so close to submission and I have to focus on
  * documentation, but if there is another iteration than cleaning this
  * mess up would be something to focus on. It's very possible that the
  * strange behavior of my robots is due to weird methods like this.
  *
  * It appears that there was an intention to utilize the motion handler a
  * lot more, but it never materialized. Honestly I wrote some pieces of this
  * so quickly that I simply don't remember what my intention was.
  */
// class SensorDistress;
class Robot : public ArenaMobileEntity {
 public:
   /**
    * @brief The constructor for a Robot.
    *
    * @param robots_params used to define the Robot.
    */
  explicit Robot(const struct robot_params& params);

  /**
   * @brief Returns the heading_angle_ of the Robot.
   */
  double get_heading_angle(void) const {
    return 0;
    // return motion_handler_.get_heading_angle();
  }
  void set_heading_angle(double ha) {
    int x = 0;
    // motion_handler_.set_heading_angle(ha);
  }

  /**
   * @brief Returns the type of the Robot. Should return
   * kRobot or kSuperBot depending on which on it is, but it doesn't...
   * instead it returns kRobot.
   */
  enum entity_type getEntityType() const {
    return kRobot;
  }

  /**
   * @brief Designed to return the speed of the robot but does nothing
   * right now.
   */
  double get_speed(void) {
    return 0;
    // return motion_handler_.get_speed();
  }

  /**
   * @brief Designed for setting the speed, but does nothing.
   */
  void set_speed(double sp) {
    int x = 0;
    // motion_handler_.set_speed(sp);
  }

  /**
   * @brief Returns a Robot's static id... I didn't like this
   * so I had it do nothing just to satisfy the inheritance.
   */
  int id(void) const {
    return 1;
  }
  std::string get_name(void) const {
    if (isSuperBot_) {
      return "SuperBot";
    } else {
      return "Robot";
    }
  }

  /**
   * @brief Returns the collision delta.
   */
  double get_collision_delta(void) const { return collision_delta_; }

  /**
   * @brief Sets the collision delta.
   *
   * @param The delta to be set.
   */
  double get_collision_delta(double delta) { collision_delta_ = delta; }


  /**
   * @brief Output from each sensor is taken, and then actions are
   * taken based on the output. Different decisions are made base on
   * whether or not the Robot is a SuperBot.
   *
   * @param The amount of time that has passed since the last update.
   */
  virtual void TimestepUpdate(uint dt) {
    // First check for a collision. If a collision occurred, you need to know
    // The type of thing you collided with. If player, and you're a superbot,
    // then freeze. If homebase, turn into superbot. Otherwise, bounce.


    // get output from all the sensors
    int isColliding = sensor_touch_.Output();
    int isDistress = sensor_distress_.Output();
    double proxDist = sensor_proximity_.Output();
    enum entity_type t = sensor_entity_type_.Output();


    if (isColliding == 1) {
      enum entity_type collisionType = sensor_touch_.collidingWithWhat();
      if (collisionType == kPlayer && !isSuperBot_) {
        frozen_ = true;
        motion_handler_.set_frozen(true);
      } else if (collisionType == kRobot || collisionType == kSuperBot) {
        frozen_ = false;
        motion_handler_.set_frozen(false);
      } else if (collisionType == kHomeBase) {
        isSuperBot_ = true;
        set_color(Color(20, 250, 36, 255));
      } else {
        // heading_angle_ = - heading_angle_;
      }
      motion_handler_.set_heading_angle(- sensor_touch_.angle_of_contact());
      heading_angle_ = motion_handler_.get_heading_angle();
    }

    /**
    * @bug This code is supposed to be responsible for slowing down the
    * robot when
    * it's within a certain proximity, but it doesn't work. Instead, it
    * accelerates the robots off to infinity.
    */
    // if(isDistress == 0 && !frozen_ && proxDist != -1
    //            && (proxDist <= 100 || proxDist >= 1)){
    //  motion_handler_.set_speed(motion_handler_.get_speed() * (proxDist/100));
    // }

    // Get the old position so that the calculated delta can be added.
    int oldX = get_pos().x;
    int oldY = get_pos().y;
    motion_handler_.updateSpeed();
    // double speed = motion_handler_.get_speed();
    double velMag = motion_handler_.get_speed() * dt;


    heading_angle_ = motion_handler_.get_heading_angle();
    double radAngle = heading_angle_ * (M_PI/180);
    const Position& p = Position(oldX + velMag * std::cos(radAngle),
        oldY + velMag * std::sin(radAngle));
    ArenaEntity::set_pos(p);
  }

  /**
   * @brief Passes the Event to the Sensor that can handle it.
   *
   * @param The Event to be passed.
   */
  void Accept(EventRecharge * e) {
    // Do nothing; remove this from mobile entity later
    int x = 0;
  }

  /**
   * @brief Passes the Event to the Sensor that can handle it.
   *
   * @param The Event to be passed.
   */
  void Accept(EventCollision * e) {
      sensor_touch_.Accept(e);
      // Some logic about freezing goes here
  }

  /**
   * @brief Passes the Event to the Sensor that can handle it.
   *
   * @param The Event to be passed.
   */
  void Accept(EventDistressCall * e) {
      sensor_distress_.Accept(e);
      // Some logic about freezing goes here
  }

  /**
   * @brief Passes the Event to the Sensor that can handle it.
   *
   * @param The Event to be passed.
   */
  void Accept(EventProximity * e) {
      sensor_proximity_.Accept(e);
      // Some logic about freezing goes here
  }

  /**
   * @brief Passes the Event to the Sensor that can handle it.
   *
   * @param The Event to be passed.
   */
  void Accept(EventTypeEmit * e) {
      sensor_entity_type_.Accept(e);
      // Some logic about freezing goes here
  }

  /**
   * @brief Resets all aspects of the Robot, including its SuperBot status
   * and color.
   */
  void Reset(void) {
    const Position& p = Position(init_x, init_y);
    // set_heading_angle(get_initial_heading_angle);
    // set_speed(get_initial_speed);
    set_pos(p);
    isSuperBot_ = false;
    frozen_ = false;
    set_color(Color(0, 0, 255, 255));
    motion_handler_.set_frozen(frozen_);
    // Reset relevant entities here.
    motion_handler_.Reset();
    sensor_touch_.Reset();
  }

  /**
   * @brief Says whether the Robot is a SuperBot or not.
   */
  bool isSuperBot() {
    return isSuperBot_;
  }

  /**
   * @brief Says whether the Robot is frozen or not.
   */
  bool frozen() {
    return frozen_;
  }



 private:
  bool isSuperBot_ = false;
  bool frozen_ = false;
  double collision_delta_;
  double heading_angle_;
  double init_x;
  double init_y;
  MotionHandlerRobot motion_handler_;
  SensorTouch sensor_touch_;
  SensorDistress sensor_distress_;
  SensorProximity sensor_proximity_;
  SensorEntityType sensor_entity_type_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION2_SRC_ROBOT_H_
