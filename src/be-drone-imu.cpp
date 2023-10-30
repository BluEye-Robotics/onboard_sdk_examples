#include <spdlog/spdlog.h>

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

  for (int n = 0; n < 10; n++) {
    cout << "Imu 0: " << drone.get_imu_raw(0) << endl;
    cout << "Imu 1: " << drone.get_imu_raw(1) << endl;

    cout << "Calibrated: " << drone.get_imu() << endl;
    this_thread::sleep_for(100ms);
  }
}
