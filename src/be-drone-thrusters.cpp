#include <fmt/core.h>        // For fmt::format
#include <spdlog/cfg/env.h>  // Allows reading log level from env variable

#include <chrono>    // For chrono_literals
#include <iostream>  // For cout
#include <thread>    // For sleep_for

#include "drone/PioneerDrone.hpp"

int main() {
  using namespace std::chrono_literals;  // For this_thread::sleep_for(1s);
  using namespace std;

  blunux::drone::PioneerDrone drone;

  // Read environment levels from an env variable. This was, you can set the
  // spdlod level like this (standard is "info"):
  // SPDLOG_LEVEL=debug be-drone
  // SPDLOG_LEVEL=warning be-drone
  spdlog::cfg::load_env_levels();

  // Set right thruster to 10% for 1s
  drone.set_thrusters({.right = 100, .left = 0, .lat = 0, .vert = 0});
  this_thread::sleep_for(1s);
  drone.set_thrusters({});

  this_thread::sleep_for(1s);

  // Set left thruster to 10% for 1s
  drone.set_thrusters({.right = 0, .left = 100, .lat = 0, .vert = 0});
  this_thread::sleep_for(1s);
  drone.set_thrusters({});

  this_thread::sleep_for(1s);

  // Set lateral thruster to 10% for 1s
  drone.set_thrusters({.right = 0, .left = 0, .lat = 100, .vert = 0});
  this_thread::sleep_for(1s);
  drone.set_thrusters({});

  this_thread::sleep_for(1s);

  // Set vertical thruster to 10% for 1s
  drone.set_thrusters({.right = 0, .left = 0, .lat = 0, .vert = 100});
  this_thread::sleep_for(1s);
  drone.set_thrusters({});

  // Since the pmu communicator is non-blocking, we need to wait until the
  // command is published to the PMU. Otherwise the program might exit before
  // the lights switch off.
  this_thread::sleep_for(100ms);
}
