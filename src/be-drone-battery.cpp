#include <spdlog/cfg/env.h>  // Allows reading log level from env variable
#include <spdlog/spdlog.h>

#include <chrono>    // For chrono_literals
#include <iostream>  // For cout
#include <thread>    // For sleep_for

#include "drone/PioneerDrone.hpp"

int main() {
  // Read environment levels from an env variable. This was, you can set the
  // spdlod level like this (standard is "info"):
  // SPDLOG_LEVEL=debug be-drone
  // SPDLOG_LEVEL=warning be-drone
  spdlog::cfg::load_env_levels();

  blunux::drone::PioneerDrone drone;

  spdlog::info("Battery charge: {}%",
               drone.get_battery_percentage().value_or(0));
  // This might take some time since the static battery information is not
  // communicated as often as the dynamic information such as state of charge
  spdlog::info("Battery type: {}",
               drone.get_battery_type().value_or("unknown"));
}
