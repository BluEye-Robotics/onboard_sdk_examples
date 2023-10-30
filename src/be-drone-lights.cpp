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

  // Print current state of the light
  cout << fmt::format("Light: {}", drone.get_light()) << endl;

  // Set light in unit range [0..1]
  drone.set_light(0.01);
  // Print current state of the light
  cout << fmt::format("Light: {}", drone.get_light()) << endl;

  this_thread::sleep_for(1s);

  // Switch off light
  drone.set_light(0);
  // Print current state of the light
  cout << fmt::format("Lights: {}", drone.get_light()) << endl;

  // Since the pmu communicator is non-blocking, we need to wait until the
  // command is published to the PMU. Otherwise the program might exit before
  // the lights switch off.
  this_thread::sleep_for(100ms);
}
