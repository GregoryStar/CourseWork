/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <fstream>
#include <string>
#include <cstdlib>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"
#include "src/position.h"
/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
void setEntityParams(std::string line, std::string type, int number,
  csci3081::player_params &pparams,
  csci3081::arena_params &aparams) {
  if (line.find("battery_max_charge") == 0) {
    line.erase(0, 19);
    pparams.battery_max_charge = std::atof(line.c_str());
  } else if (line.find("angle_delta") == 0) {
    line.erase(0, 12);
    if (type == "player")
      pparams.angle_delta = std::atoi(line.c_str());
    else if (type == "robot")
      aparams.robots[number].angle_delta = std::atoi(line.c_str());
  } else if (line.find("collision_delta") == 0) {
    line.erase(0, 16);
    if (type == "player")
      pparams.collision_delta = std::atoi(line.c_str());
    else if (type == "robot")
      aparams.robots[number].collision_delta = std::atoi(line.c_str());
    else if (type == "home_base")
      aparams.home_base.collision_delta = std::atoi(line.c_str());
  } else if (line.find("radius") == 0) {
    line.erase(0, 7);
    if (type == "player")
      pparams.radius = std::atof(line.c_str());
    else if (type == "robot")
      aparams.robots[number].radius = std::atof(line.c_str());
    else if (type == "recharge_station")
      aparams.recharge_station.radius = std::atof(line.c_str());
    else if (type == "home_base")
      aparams.home_base.radius = std::atof(line.c_str());
    else if (type == "obstacle")
      aparams.obstacles[number].radius = std::atof(line.c_str());
  } else if (line.find("pos") == 0) {
    line.erase(0, 4);
    double x = std::atof((line.substr(0, line.find(" "))).c_str());
    line.erase(0, line.find(" ") + 1);
    double y = std::atof(line.c_str());
    if (type == "player")
      pparams.pos = csci3081::Position(x, y);
    else if (type == "robot")
      aparams.robots[number].pos = csci3081::Position(x, y);
    else if (type == "recharge_station")
      aparams.recharge_station.pos = csci3081::Position(x, y);
    else if (type == "home_base")
      aparams.home_base.pos = csci3081::Position(x, y);
    else if (type == "obstacle")
      aparams.obstacles[number].pos = csci3081::Position(x, y);
  } else if (line.find("color") == 0) {
    line.erase(0, 6);
    int r = std::atoi((line.substr(0, line.find(" "))).c_str());
    line.erase(0, line.find(" ") + 1);
    int g = std::atoi((line.substr(0, line.find(" "))).c_str());
    line.erase(0, line.find(" ") + 1);
    int b = std::atoi((line.substr(0, line.find(" "))).c_str());
    line.erase(0, line.find(" ") + 1);
    int a = std::atoi(line.c_str());
    if (type == "player")
      pparams.color = csci3081::Color(r, g, b, a);
    else if (type == "robot")
      aparams.robots[number].color = csci3081::Color(r, g, b, a);
    else if (type == "recharge_station")
      aparams.recharge_station.color = csci3081::Color(r, g, b, a);
    else if (type == "home_base")
      aparams.home_base.color = csci3081::Color(r, g, b, a);
    else if (type == "obstacle")
      aparams.obstacles[number].color = csci3081::Color(r, g, b, a);
  }
}

int main(int, char **) {
  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities
  csci3081::player_params pparams;

  // csci3081::robot_params rparams;

  csci3081::arena_params aparams;

  std::ifstream input;
  input.open("params.txt");
  int num_of_players = 0;
  int num_of_robots = 0;
  int num_of_recharge_stations = 0;
  int num_of_home_bases = 0;
  int num_of_obstacles = 0;
  std::string line;
  std::string type;
  while (std::getline(input, line)) {
    if (line.find("player_params") == 0) {
      type = "player";
      num_of_players += 1;
    } else if (line.find("robot_params") == 0) {
      type = "robot";
      num_of_robots += 1;
    } else if (line.find("recharge_station_params") == 0) {
      type = "recharge_station";
      num_of_recharge_stations += 1;
    } else if (line.find("home_base_params") == 0) {
      type = "home_base";
      num_of_home_bases += 1;
    } else if (line.find("obstacle_params") == 0) {
      type = "obstacle";
      num_of_obstacles += 1;
    } else if (type == "player") {
      setEntityParams(line, type, num_of_players - 1, pparams, aparams);
    } else if (type == "robot") {
      setEntityParams(line, type, num_of_robots - 1, pparams, aparams);
    } else if (type == "recharge_station") {
      setEntityParams(line, type, num_of_recharge_stations - 1,
        pparams, aparams);
    } else if (type == "home_base") {
      setEntityParams(line, type, num_of_home_bases - 1, pparams, aparams);
    } else if (type == "obstacle") {
      setEntityParams(line, type, num_of_obstacles - 1, pparams, aparams);
    }
  }

  aparams.player = pparams;

  aparams.n_obstacles = num_of_obstacles;
  aparams.x_dim = 1024;
  aparams.y_dim = 768;

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
