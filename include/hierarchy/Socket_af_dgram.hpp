/**
 * 
 * @author Miguel Martín
 * @date 20200919
 */


#pragma once
#include "Socket_af.hpp"

class Socket_af_dgram : public Socket_af {
 public:
  Socket_af_dgram(std::string ip, int port);
  ~Socket_af_dgram(void);

  void bindsock(int fd, std::string ip, int port);
  void send_to(Message msg, std::string remote_ip, int remote_port);
};