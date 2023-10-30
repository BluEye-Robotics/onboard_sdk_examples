#include <fmt/core.h>        // For fmt::format
#include <spdlog/cfg/env.h>  // Allows reading log level from env variable

#include "logging/Logger.hpp"
#include "logging/factory.hpp"

namespace my_namespace {
class MyClass : blunux::logging::Logger<MyClass> {
 public:
  MyClass() { logger->info("Hello from MyClass"); }
  void do_something() { logger->info("Doing something"); }
};

void example_function() {
  // Retrieve logger for the example_function
  static auto logger = blunux::logging::GET_FUNCTION_LOGGER();

  // Log different severity levels with relevant messages
  logger->trace("Entering example_function: a trace message.");
  logger->debug("Performing operation in example_function: a debug message.");
  logger->info("Executing example_function: an informational message.");
  logger->warn("Caution in example_function: a warning message.");
  logger->error("Error encountered in example_function: an error message.");
  logger->critical("Critical issue in example_function: a critical message.");
}
}  // namespace my_namespace

int main() {
  using namespace my_namespace;

  // Read environment levels from an env variable. This was, you can set the
  // spdlod level like this (standard is "info"):
  // SPDLOG_LEVEL=debug be-drone-logging
  // SPDLOG_LEVEL=warning be-drone-logging
  spdlog::cfg::load_env_levels();

  MyClass my_class;
  my_class.do_something();
  example_function();
}
