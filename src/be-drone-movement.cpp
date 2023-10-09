#include <fmt/core.h>        // For fmt::format
#include <spdlog/cfg/env.h>  // Allows reading log level from env variable

#include <chrono>    // For chrono_literals
#include <iostream>  // For cout
#include <thread>    // For sleep_for

#include "drone/PioneerDrone.hpp"

int main() {
  using namespace std::chrono_literals;  // For this_thread::sleep_for(1s);
  using namespace std;

  // Read environment levels from an env variable. This was, you can set the
  // spdlog level like this (standard is "info"):
  // SPDLOG_LEVEL=debug be-drone
  // SPDLOG_LEVEL=warning be-drone
  spdlog::cfg::load_env_levels();

  blunux::drone::PioneerDrone drone;
  // this_thread::sleep_for(10s);

  cout << "Setting surge for 1s" << endl;
  drone.set_force({.surge = 5, .sway = 0, .heave = 0, .yaw = 0});
  this_thread::sleep_for(1s);
  drone.set_force({});

  this_thread::sleep_for(1s);

  cout << "Setting sway for 1s" << endl;
  drone.set_force({.surge = 0, .sway = 5, .heave = 0, .yaw = 0});
  this_thread::sleep_for(1s);
  drone.set_force({});

  this_thread::sleep_for(1s);

  cout << "Setting heave for 1s" << endl;
  drone.set_force({.surge = 0, .sway = 0, .heave = 5, .yaw = 0});
  this_thread::sleep_for(1s);
  drone.set_force({});

  this_thread::sleep_for(1s);

  cout << "Setting yaw for 1s" << endl;
  drone.set_force({.surge = 0, .sway = 0, .heave = 0, .yaw = 5});
  this_thread::sleep_for(1s);
  drone.set_force({});

  // Since the pmu communicator is non-blocking, we need to wait until the
  // command is published to the PMU. Otherwise the program might exit before
  // the lights switch off.
  this_thread::sleep_for(100ms);
}
