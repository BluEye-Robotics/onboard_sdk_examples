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

  for (int n = 0; n < 10; n++) {
    spdlog::info("Imu 0: {}", drone.get_imu_raw(0));
    spdlog::info("Imu 1: {}", drone.get_imu_raw(1));

    spdlog::info("Calibrated: {}", drone.get_imu());
    this_thread::sleep_for(100ms);
  }
}
