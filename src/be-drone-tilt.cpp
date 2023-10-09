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
  // spdlod level like this (standard is "info"):
  // SPDLOG_LEVEL=debug be-drone
  // SPDLOG_LEVEL=warning be-drone
  spdlog::cfg::load_env_levels();

  blunux::drone::PioneerDrone drone;

  this_thread::sleep_for(1s);
  spdlog::info("Initialze tilt...");

  if (drone.tilt()->calibrate()) {
    spdlog::info("Tilt initialized");
  } else {
    spdlog::warn("Tilt initialization failed");
  }

  auto tilt_angle = drone.tilt()->get_angle();
  if (tilt_angle.has_value()) {
    spdlog::info("Tilt angle: {:.1f}", drone.tilt()->get_angle().value());
  } else {
    spdlog::warn("Tilt angle cannot be read");
  }

  drone.tilt()->set_velocity(1);
  this_thread::sleep_for(1.5s);
  drone.tilt()->set_velocity(-1);
  this_thread::sleep_for(3s);
  drone.tilt()->set_velocity(1);
  this_thread::sleep_for(1.5s);
  drone.tilt()->set_velocity(0);

  drone.tilt()->set_stabilization(true);
  this_thread::sleep_for(30s);
}
