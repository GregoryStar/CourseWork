/**
 * @file player_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
PlayerMotionHandler::PlayerMotionHandler() {
    MotionHandler();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void PlayerMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_SLOW_DOWN:
    if (get_speed() >= 1) {
      set_speed(get_speed() - 1);
    }
  break;
  case COM_TURN_LEFT:
    set_heading_angle(get_heading_angle() - 45);
  break;
  case COM_TURN_RIGHT:
    set_heading_angle(get_heading_angle() + 45);
  break;
  case COM_SPEED_UP:
  if (get_speed() < max_speed()) {
    set_speed(get_speed() + 1);
  }
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void PlayerMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    set_heading_angle(- st.angle_of_contact());
  }
}

NAMESPACE_END(csci3081);
