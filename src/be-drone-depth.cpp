#include <fmt/core.h>       // For fmt::format
#include <spdlog/spdlog.h>  // Allows reading log level from env variable

#include <chrono>    // For chrono_literals
#include <iostream>  // For cout
#include <thread>    // For sleep_for

#include "drone/PioneerDrone.hpp"

int main() {
  using namespace std::chrono_literals;  // For this_thread::sleep_for(1s);
  using namespace std;

  // Set log level to warn to mute log messages
  spdlog::set_level(spdlog::level::warn);

  blunux::drone::PioneerDrone drone;

  this_thread::sleep_for(1s);
  cout << fmt::format("Depth: {:.3f}", drone.get_depth()) << endl;
}
