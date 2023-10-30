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

  while (true) {
    Eigen::Vector3d attitude = drone.observer_state()->getGlobalAttitudeEuler();

    spdlog::info("Attitude: {:.0f} {:.0f} {:.0f}", attitude.x(), attitude.y(),
                 attitude.z());
    this_thread::sleep_for(100ms);
  }
}
