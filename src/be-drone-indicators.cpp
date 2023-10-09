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

  // Print current state of the indicators
  cout << fmt::format("Indicators: {}", drone.get_indicator()) << endl;

  // Set the indicator lights in the lower canister
  // [red|ORANGE|yellow|GREEN]
  drone.set_indicator(
      {.green = false, .yellow = true, .orange = false, .red = true});

  // Print current state of the indicators
  cout << fmt::format("Indicators: {}", drone.get_indicator()) << endl;

  this_thread::sleep_for(2s);

  // Set the indicator lights in the lower canister
  // [RED|orange|YELLOW|green]
  drone.set_indicator(
      {.green = true, .yellow = false, .orange = true, .red = false});

  // Print current state of the indicators
  cout << fmt::format("Indicators: {}", drone.get_indicator()) << endl;

  this_thread::sleep_for(2s);

  // Reset to standard blinking pattern by switching off all indicator lights
  drone.set_indicator({});

  // Print current state of the indicators
  cout << fmt::format("Indicators: {}", drone.get_indicator()) << endl;

  // Since the pmu communicator is non-blocking, we need to wait until the
  // command is published to the PMU. Otherwise the program might exit before
  // the indicators switch off.
  this_thread::sleep_for(100ms);
}
