/**
 * @file sensor.h
 *
 * @copyright 2017 Gregory S, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_H_
#define PROJECT_ITERATION1_SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/position.h"
#include "src/arena_entity.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A generalize sensor has an activated state which can be
 * activated, and then reset. That's the only thing I could come up
 * with from our already small definition of a SensorTouch.
 */
class Sensor {
 public:
   /**
    * @brief Will return the activated status of Sensor when implemented.
    */
  //Sensor(ArenaEntity* entity) :
    //    observer(entity) {}

  virtual void Accept(EventBaseClass * e){
    int x = 0;
  }
  void registerObserver(ArenaEntity* a){
    observer = a;
  }
  void setActivator(ArenaEntity* entity){
    activator = entity;
  }
  void removeObserver(){
    observer = NULL;
  }
  virtual void notifyObservers(){
    int x = 0;
  }
  ArenaEntity* getObserver(){
    return observer;
  }

  virtual bool activated(void) { return activated_; }
  /**
   * @brief Sets the activated status of sensor.
   *
   * @params value The value to be used when setting activated_.
   */
  virtual void activated(bool value) { activated_ = value; }
  /**
   * @brief Will deactivate the sensor when implemented.
   */
  void Reset(void){
    activated_ = false;
  };

 private:
  bool activated_;
  ArenaEntity* observer;
  ArenaEntity* activator;
};

NAMESPACE_END(csci3081);

#endif   /* PROJECT_ITERATION1_SRC_SENSOR_H_ */
