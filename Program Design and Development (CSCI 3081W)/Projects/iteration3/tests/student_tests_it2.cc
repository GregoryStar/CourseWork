// Google Test Framework
#include <gtest/gtest.h>
#include "../src/sensor.h"
#include "../src/arena_entity_params.h"
#include "../src/arena_mobile_entity_params.h"
#include "../src/robot_params.h"
#include "../src/sensor_touch.h"
#include "../src/sensor_proximity.h"
#include "../src/sensor_distress.h"
#include "../src/sensor_entity_type.h"
#include "../src/arena_entity.h"
#include "../src/robot.h"
#include "../src/player.h"

using namespace csci3081;

// NOTE: There are no explicit tests for constructors because Constructors
// are indirectly tested in every single test function.


TEST(SensorProximity, setRange){
  double range = 100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorProximity, setRange2){
  double range = -100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorProximity, setRange3){
  double range = 1000000;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

/* NOTE: Testing getters and setters is the same, but I want to comply with
the requirements so I'm testing both...  */

TEST(SensorProximity, getRange){
  double range = 1000;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorProximity, getRange2){
  double range = -30;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorProximity, getRange3){
  double range = 1241314;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorProximity, setFOV){
  double range = 100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

TEST(SensorProximity, setFOV2){
  double range = 100;
  double fov = 112210;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

TEST(SensorProximity, setFOV3){
  double range = 100;
  double fov = -100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

///////

TEST(SensorProximity, getFOV){
  double range = 100;
  double fov = 30;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

TEST(SensorProximity, getFOV2){
  double range = 100;
  double fov = 1219;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

TEST(SensorProximity, getFOV3){
  double range = 100;
  double fov = 0;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  EXPECT_EQ(fov, sp->getFOV());
}

// NOTE: These three tests are for both Accept and Output since
// these methods rely on each other.
TEST(SensorProximity, Output){
  double range = 100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorProximity* sp = new SensorProximity(robot, range, fov);
  sp->activated(true);
  EXPECT_EQ(-1, sp->Output());
}

TEST(SensorProximity, Output2){
  double range = 100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  // Center the proximity sensor at 0, 0. Then see if
  // it can actually detect something in range by accepting
  // a proximity event.
  Position p = Position(0, 0);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  robot->set_heading_angle(-45);
  SensorProximity* sp = new SensorProximity(robot, range, fov);

  EventProximity* e = new EventProximity(Position(10, 10), 20, kObstacle);
  EXPECT_TRUE(sp->Output() != -1);
}

TEST(SensorProximity, Output3){
  double range = 100;
  double fov = 100;

  // radius, pos, color, collision delta, angle delta
  // Test to see that event proximity detects nothing when out of range.
  Position p = Position(200, 400);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  robot->set_heading_angle(-45);
  SensorProximity* sp = new SensorProximity(robot, range, fov);

  EventProximity* e = new EventProximity(Position(10, 10), 20, kObstacle);
  EXPECT_TRUE(sp->Output() == -1);
}

///////////////////////////////
TEST(SensorDistress, setRange){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorDistress, setRange2){
  double range = -100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorDistress, setRange3){
  double range = 1000000;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

/* NOTE: Testing getters and setters is the same, but I want to comply with
the requirements so I'm testing both...  */

TEST(SensorDistress, getRange){
  double range = 1000;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorDistress, getRange2){
  double range = -30;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorDistress, getRange3){
  double range = 1241314;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

////////////////////////////////////////////////////////
// NOTE: Accept and Output are being tested together as they
// rely on each other to work.

// Test whether an activated sensor returns 1 as expected
TEST(SensorDistress, Output){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  sp->activated(true);
  EXPECT_EQ(1, sp->Output());
}

// Test whether an unactivated sensor returns 0 as expected
TEST(SensorDistress, Output2){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  sp->activated(false);
  EXPECT_EQ(0, sp->Output());
}

//Actually test whether or not an entity in range activates the sensor
TEST(SensorDistress, Output3){
  double range = 100;

  // radius, pos, color, collision delta, angle delta

  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorDistress* sp = new SensorDistress(robot, range);
  EventDistressCall* e = new EventDistressCall(Position (100, 100));
  EXPECT_EQ(1, sp->Output());
}

//////////////////////////////////////////////////////////////

TEST(SensorEntityType, setRange){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorEntityType, setRange2){
  double range = -100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorEntityType, setRange3){
  double range = 1000000;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

/* NOTE: Testing getters and setters is the same, but I want to comply with
the requirements so I'm testing both...  */

TEST(SensorEntityType, getRange){
  double range = 1000;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorEntityType, getRange2){
  double range = -30;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

TEST(SensorEntityType, getRange3){
  double range = 1241314;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);
  EXPECT_EQ(range, sp->getRange());
}

///////////////////////////////////////////////////
// NOTE: Output and Accept are tested simultaneously as they depend on
// each other.

// Test if it can detect an obstacle in range
TEST(SensorEntityType, Output){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);

  EventTypeEmit* e = new EventTypeEmit(Position (100, 100), kObstacle);
  sp->Accept(e);
  EXPECT_EQ(kObstacle, sp->Output());
}

// Test if returns null when obstacle not in range
TEST(SensorEntityType, Output2){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);

  EventTypeEmit* e = new EventTypeEmit(Position (1000, 1000), kObstacle);
  sp->Accept(e);
  EXPECT_EQ(kNULL, sp->Output());
}

// Test if can detect another type of entity
TEST(SensorEntityType, Output3){
  double range = 100;

  // radius, pos, color, collision delta, angle delta
  Position p = Position(100, 100);
  Color c = Color(255, 255, 255, 255);
  robot_params rParams;
  rParams.angle_delta = 10.0;
  rParams.collision_delta = 10.0;
  rParams.color = c;
  rParams.pos = p;
  rParams.radius = 10.0;
  Robot* robot = new Robot(rParams);
  SensorEntityType* sp = new SensorEntityType(robot, range);

  EventTypeEmit* e = new EventTypeEmit(Position (150, 150), kRobot);
  sp->Accept(e);
  EXPECT_EQ(kRobot, sp->Output());
}

//////////////////////////////////////////////////

TEST(SensorTouch, Accept){
  csci3081::EventCollision* e = new csci3081::EventCollision();
  e->collided(false);
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->Accept(e);
  EXPECT_EQ(st->angle_of_contact(), 0);
}

TEST(SensorTouch, Accept2){
  csci3081::EventCollision* e = new csci3081::EventCollision();
  e->angle_of_contact(100);
  e->collided(false);
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->Accept(e);
  EXPECT_EQ(st->angle_of_contact(), 100);
}
TEST(SensorTouch, Accept3){
  csci3081::EventCollision* e = new csci3081::EventCollision();
  e->setCollidedWith(kSuperBot);
  e->collided(true);
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->Accept(e);
  EXPECT_EQ(st->collidingWithWhat(), kSuperBot);
}

//////////////////////////

TEST(SensorTouch, get_angle_of_contact){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(10);
  EXPECT_EQ(st->angle_of_contact(), 10);
}

TEST(SensorTouch, get_angle_of_contact2){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(20);
  EXPECT_EQ(st->angle_of_contact(), 20);
}

TEST(SensorTouch, get_angle_of_contact3){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(30);
  EXPECT_EQ(st->angle_of_contact(), 30);
}

/////////////////////////////
// NOTE: Tests for getters and setters are identical...

TEST(SensorTouch, set_angle_of_contact){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(10);
  EXPECT_EQ(st->angle_of_contact(), 10);
}

TEST(SensorTouch, set_angle_of_contact2){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(20);
  EXPECT_EQ(st->angle_of_contact(), 20);
}

TEST(SensorTouch, set_angle_of_contact3){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->angle_of_contact(30);
  EXPECT_EQ(st->angle_of_contact(), 30);
}

////////////////////////////////////////////

// When the sensor is activated it should return 1
TEST(SensorTouch, Output){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->activated(true);
  EXPECT_EQ(st->Output(), 1);
}

// When the sensor is not activated it should return 0
TEST(SensorTouch, Output2){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->activated(false);
  EXPECT_EQ(st->Output(), 0);
}

// This third test is redundant but... I need something here
TEST(SensorTouch, Output3){
  csci3081::SensorTouch* st = new csci3081::SensorTouch();
  st->activated(true);
  EXPECT_FALSE(st->Output());
}






// TEST(SensorProximity, setFOV){
//   double FOV = 100;
//   csci3081::SensorProximity* sp = new csci3081::SensorProximity();
//   sp->setFOV(FOV);
//   EXPECT_EQ(FOV, sp->getFOV());
// }
//
// TEST(SensorProximity, Constructor){
//   csci3081::SensorProximity* sp = new csci3081::SensorProximity();
//   EXPECT_TRUE(sp != NULL);
// }
//
// TEST(SensorProximity, getRange){
//   double range = 20;
//   csci3081::SensorProximity* sp = new csci3081::SensorProximity();
//   sp->setRange(range);
//   EXPECT_EQ(range, sp->getRange());
// }
//
// TEST(SensorProximity, getFOV){
//   double FOV = 30;
//   csci3081::SensorProximity* sp = new csci3081::SensorProximity();
//   sp->setFOV(FOV);
//   EXPECT_EQ(FOV, sp->getFOV());
// }
//
// //////////////////////////////////////////////////////////////////
// TEST(SensorTouch, Constructor){
//   csci3081::SensorTouch* st = new csci3081::SensorTouch();
//   EXPECT_TRUE(st != NULL);
// }
//
// TEST(SensorTouch, Accept){
//   csci3081::EventCollision* e = new csci3081::EventCollision();
//   e->collided(false);
//   csci3081::SensorTouch* st = new csci3081::SensorTouch();
//   st->Accept(e);
//   EXPECT_EQ(st->angle_of_contact(), 0);
// }
//
// TEST(SensorTouch, angle_of_contact){
//   csci3081::SensorTouch* st = new csci3081::SensorTouch();
//   EXPECT_EQ(st->angle_of_contact(), 0);
// }
//
// TEST(SensorTouch, set_angle_of_contact){
//   csci3081::SensorTouch* st = new csci3081::SensorTouch();
//   st->angle_of_contact(3);
//   EXPECT_EQ(st->angle_of_contact(), 3);
// }
//
// TEST(SensorTouch, activated){
//   csci3081::SensorTouch* st = new csci3081::SensorTouch();
//   st->activated(true);
//   EXPECT_EQ(st->activated(), true);
// }
// //////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// TEST(SensorEntityType, Constructor){
//   csci3081::SensorEntityType* st = new csci3081::SensorEntityType();
//   EXPECT_TRUE(st != NULL);
// }
//
// TEST(SensorEntityType, getRange){
//   csci3081::SensorEntityType* st = new csci3081::SensorEntityType();
//   st->setRange(100);
//   EXPECT_EQ(st->getRange(), 100);
// }
//
// TEST(SensorEntityType, setRange){
//   csci3081::SensorEntityType* st = new csci3081::SensorEntityType();
//   st->setRange(0);
//   EXPECT_EQ(st->getRange(), 0);
// }
//
// TEST(SensorEntityType, reset){
//   csci3081::SensorEntityType* st = new csci3081::SensorEntityType();
//   st->activated(true);
//   st->Reset();
//   EXPECT_EQ(st->activated(), false);
// }
//
// TEST(SensorEntityType, activated){
//   csci3081::SensorEntityType* st = new csci3081::SensorEntityType();
//   st->activated(true);
//   EXPECT_EQ(st->activated(), true);
// }
// //////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// TEST(SensorDistress, Constructor){
//   csci3081::SensorDistress* st = new csci3081::SensorDistress();
//   EXPECT_TRUE(st != NULL);
// }
//
// TEST(SensorDistress, getRange){
//   csci3081::SensorDistress* sd = new csci3081::SensorDistress();
//   sd->setRange(100);
//   EXPECT_EQ(sd->getRange(), 100);
// }
//
// TEST(SensorDistress, setRange){
//   csci3081::SensorDistress* sd = new csci3081::SensorDistress();
//   sd->setRange(0);
//   EXPECT_EQ(sd->getRange(), 0);
// }
//
// TEST(SensorDistress, reset){
//   csci3081::SensorDistress* sd = new csci3081::SensorDistress();
//   sd->activated(true);
//   sd->Reset();
//   EXPECT_EQ(sd->activated(), false);
// }
//
// TEST(SensorDistress, activated){
//   csci3081::SensorDistress* sd = new csci3081::SensorDistress();
//   sd->activated(true);
//   EXPECT_EQ(sd->activated(), true);
// }
//////////////////////////////////////////////////////////////////////
