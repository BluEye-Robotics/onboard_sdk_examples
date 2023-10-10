cmake_minimum_required(VERSION 3.18)
project(blunux VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(blunux REQUIRED)
message(STATUS "blunux_FOUND = ${blunux_FOUND}")
message(STATUS "blunux_LIBRARIES = ${blunux_LIBRARIES}")
message(STATUS "blunux_LIB_DIRS = ${blunux_LIB_DIRS}")
message(STATUS "blunux_INCLUDE_DIRS = ${blunux_INCLUDE_DIRS}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(FMT fmt)
message(STATUS "FMT_LIBRARIES = ${FMT_LIBRARIES}")
message(STATUS "FMT_LIBRARY_DIRS = ${FMT_LIBRARY_DIRS}")

find_package(spdlog REQUIRED)

# Order seems to be important here
add_definitions(-DSPDLOG_FMT_EXTERNAL)
add_definitions(-DSPDLOG_COMPILED_LIB)

message(STATUS "SPDLOG_LIBRARIES = ${SPDLOG_LIBRARIES}")

IF("${SPDLOG_LIBRARIES}" STREQUAL "")
    set(SPDLOG_LIBRARIES spdlog::spdlog)
    message(STATUS "SPDLOG_LIBRARIES = ${SPDLOG_LIBRARIES}")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${blunux_INCLUDE_DIRS})
link_directories(${blunux_LIB_DIRS} ${FMT_LIBRARY_DIRS})

add_executable(be-drone-lights src/be-drone-lights.cpp)
target_link_libraries(be-drone-lights ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-lights DESTINATION bin)

add_executable(be-drone-indicators src/be-drone-indicators.cpp)
target_link_libraries(be-drone-indicators ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-indicators DESTINATION bin)

add_executable(be-drone-thrusters src/be-drone-thrusters.cpp)
target_link_libraries(be-drone-thrusters ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-thrusters DESTINATION bin)

add_executable(be-drone-thruster-forwarder src/be-drone-thruster-forwarder.cpp)
target_link_libraries(be-drone-thruster-forwarder ${blunux_LIBRARIES})
install(TARGETS be-drone-thruster-forwarder DESTINATION bin)

add_executable(be-drone-tilt src/be-drone-tilt.cpp)
target_link_libraries(be-drone-tilt ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-tilt DESTINATION bin)

add_executable(be-drone-movement src/be-drone-movement.cpp)
target_link_libraries(be-drone-movement ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-movement DESTINATION bin)

add_executable(be-drone-depth src/be-drone-depth.cpp)
target_link_libraries(be-drone-depth ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-depth DESTINATION bin)

add_executable(be-drone-imu src/be-drone-imu.cpp)
target_link_libraries(be-drone-imu ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-imu DESTINATION bin)

add_executable(be-drone-battery src/be-drone-battery.cpp)
target_link_libraries(be-drone-battery ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-battery DESTINATION bin)

add_executable(be-drone-attitude src/be-drone-attitude.cpp)
target_link_libraries(be-drone-attitude ${blunux_LIBRARIES} ${SPDLOG_LIBRARIES} ${FMT_LIBRARIES})
install(TARGETS be-drone-attitude DESTINATION bin)
