#include <spdlog/cfg/env.h>  // Allows reading log level from env variable
#include <spdlog/spdlog.h>

#include <chrono>    // For chrono_literals
#include <iostream>  // For cout
#include <thread>    // For sleep_for

#include "drone/PioneerDrone.hpp"

int main() {
  using namespace std;

  // Set log level to warn to mute log messages
  spdlog::set_level(spdlog::level::warn);

  blunux::drone::PioneerDrone drone;

  cout << "Battery charge: " << drone.get_battery_percentage().value_or(0)
       << "%" << endl;

  // This might take some time since the static battery information is not
  // communicated as often as the dynamic information such as state of charge
  cout << "Battery type: " << drone.get_battery_type().value_or("unknown")
       << endl;
}
