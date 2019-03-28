// Google Test Framework
#include <gtest/gtest.h>
#include "../src/sensor_proximity.h"
#include "..src/arena_entity.h"

#ifdef SENSOR_PROXIMITY_TESTS

TEST(SensorProximity, DetectInSensingArea){
  double range = 100;
  double fov = 100;
  csci3081::SensorProximity* sensorProximity = new SensorProximity(range, fov);
  //
}

#endif /*
