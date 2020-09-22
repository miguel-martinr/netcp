#include "../include/received_info.hpp"

#include <arpa/inet.h>

received_info::received_info(void) {
  something_received = false;
}

std::string received_info::ip(void) {
  return std::string(inet_ntoa(sender_info.sin_addr));
}


int received_info::port(void) {
  return ntohs(sender_info.sin_port);
}