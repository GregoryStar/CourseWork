/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/robot.h"
#include "src/event_distress_call.h"
#include "src/event_type_emit.h"
#include "src/event_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  gameWon_(false), gameLost_(false),
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  player_(new Player(&params->player)),
  n_players_(1),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  player_->set_heading_angle(37);
  entities_.push_back(player_);
  mobile_entities_.push_back(player_);
  // Adding the home base to mobile entities so collisions are checked.
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);
  entities_.push_back(home_base_);

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */

  for (size_t i = 0; i < 5; ++i) {
    Robot* r = new Robot(params->robots[i]);
    entities_.push_back(r);
    mobile_entities_.push_back(r);
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  // Make it so that the game is neither lost nor won.
  // I'm not a fan of using two separate variables for this (it makes more
  // sense to have some sort of gameOver variable), but it works.
  gameLost_ = false;
  gameWon_ = false;
  for (auto ent : entities_) {
    ent->Reset();
  }
  /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* players() */


std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      res.push_back(r);
    }
  } /* for(ent..) */
  return res;
} /* players() */

void Arena::AdvanceTime(void) {
  std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

/**
 * @brief In addition to what it did before, it now also creates distress
 * events and proximity events. In principle I'd like to put implementation
 * for that into separate methods; I just did this to test them out. However,
 * as it turns out, actually reacting to distress events broke the program
 * so I never got that far.
 */
void Arena::UpdateEntitiesTimestep(void) {
  // Create a distress event for every frozen robot
  // Pass that event to every robot
  for (auto ent : entities_) {
      if (ent->getEntityType() == kRobot) {
          Robot* r = dynamic_cast<Robot*>(ent);
          if (r->frozen()) {
            for (auto ent2 : entities_) {
                if (ent2->getEntityType() == kRobot ||
                  ent2->getEntityType() == kSuperBot) {
                  Robot* r2 = dynamic_cast<Robot*>(ent2);
                  r2->Accept(new EventDistressCall(r->get_pos()));
                }
            }
          }
      }
  }

  // Create a proximity event for every robot
  // Pass that event to every robot
  for (auto ent : entities_) {
      if (ent->getEntityType() == kRobot) {
          Robot* r = dynamic_cast<Robot*>(ent);
          for (auto ent2 : entities_) {
            if (ent2->getEntityType() != kRobot) {
              r->Accept(new EventProximity(ent2->get_pos(), ent2->get_radius(),
                ent2->getEntityType()));
            }
          }
      }
  }

  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the player has run out of battery
   */
  if (player_->battery_level() <=0) {
    gameLost_ = true;
  }

  /*
   * Next, check if the player has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * player away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;

  CheckForEntityCollision(player_, home_base_, &ec,
    player_->get_collision_delta());
  if (ec.collided()) {
    gameWon_ = true;
  }

  CheckForEntityCollision(player_, recharge_station_,
    &ec, player_->get_collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    player_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec,
          ent->get_collision_delta());
        if (ec.collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x+ ent->get_radius() >= x_dim_) {
    // Right Wall
    event->collided(true);
    event->point_of_contact(Position(x_dim_, ent->get_pos().y));
    event->angle_of_contact(ent->get_heading_angle() + 180);
  } else if (ent->get_pos().x- ent->get_radius() <= 0) {
    // Left Wall
    event->collided(true);
    event->point_of_contact(Position(0, ent->get_pos().y));
    event->angle_of_contact(ent->get_heading_angle() + 180);
  } else if (ent->get_pos().y+ ent->get_radius() >= y_dim_) {
    // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->angle_of_contact(ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->get_radius() <= 0) {
    // Top Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->angle_of_contact(ent->get_heading_angle());
  } else {
    event->collided(false);
  }
} /* entity_out_of_bounds() */


void Arena::CheckForEntityCollision(const ArenaEntity* const ent1,
  const ArenaEntity* const ent2,
  EventCollision * event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x;
  double ent1_y = ent1->get_pos().y;
  double ent2_x = ent2->get_pos().x;
  double ent2_y = ent2->get_pos().y;
  event->setCollidedWith(ent2->getEntityType());

  // This entire code doesn't work right because you can't Calculate
  // collisions without knowing the heading angle.
  double dist = std::sqrt(
    std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
  if ((dist > ent1->get_radius() + ent2->get_radius() + collision_delta)) {
    event->collided(false);
  } else {
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact
    // These calculations are suspicious at best...
    double dx = ent2_x - ent1_x;
    double dy = ent2_y - ent1_y;
    double rAngle = (std::atan(dy/dx));
    double angle = (180/M_PI) * rAngle;
    event->angle_of_contact(angle);

    double xPOC = ent1_x + ent1->get_radius() * std::cos(rAngle);
    double yPOC = ent1_y + ent1->get_radius() * std::sin(rAngle);
    event->point_of_contact(Position(xPOC, yPOC));

    // collided is set to true so that the event will actually be acted
    // upon in the entity that it concerns.
    event->collided(true);
  }
} /* entities_have_collided() */




void Arena::Accept(__unused EventKeypress * e) {
  player_ -> EventCmd(e -> get_key_cmd());
}

NAMESPACE_END(csci3081);
