#include <boost/asio.hpp>
#include <iostream>  // For cout

#include "drone/PioneerDrone.hpp"

/*
Control from python:

import socket
import struct
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(struct.pack("hhhh", *[0,0,0,100]), ("192.168.1.101", 2023))
*/

typedef struct __attribute__((__packed__)) {
  int16_t right;
  int16_t left;
  int16_t lat;
  int16_t vert;
} struct_udp_thrusters;

int main() {
  using namespace std;

  blunux::drone::PioneerDrone drone;
  boost::asio::io_context io_context;

  // Create a UDP socket
  boost::asio::ip::udp::socket socket(io_context);

  // Set up the endpoint to listen on all available network interfaces and a
  // specific port
  boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::udp::v4(), 2023);

  // Bind the socket to the endpoint
  socket.open(endpoint.protocol());
  socket.bind(endpoint);

  std::cout << "UDP receiver listening on port 2023..." << std::endl;
  drone.set_indicator(
      {.green = true, .yellow = false, .orange = false, .red = true});

  // Buffer to receive data
  char receiveBuffer[1024];
  while (true) {
    boost::asio::ip::udp::endpoint senderEndpoint;
    std::size_t bytesRead =
        socket.receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);
    struct_udp_thrusters thrusters;
    if (bytesRead == sizeof(thrusters)) {
      memcpy(&thrusters, receiveBuffer, sizeof(thrusters));
      drone.set_thrusters({.right = thrusters.right,
                           .left = thrusters.left,
                           .lat = thrusters.lat,
                           .vert = thrusters.vert});
      {
        // Switch indicator on each packet
        static int num_packets = 0;
        num_packets++;
        if (num_packets % 2 == 0) {
          drone.set_indicator(
              {.green = true, .yellow = false, .orange = true, .red = true});
        } else {
          drone.set_indicator(
              {.green = true, .yellow = true, .orange = false, .red = true});
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
