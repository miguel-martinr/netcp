#pragma once

#include "Socket_af_dgram.hpp"
#include "transf_info.hpp"

#include <string>


class client {

 public:
   client(std::string ip = "", int port = 0);
   ~client(void);

   int upload_file(std::string filename, std::string remote_ip, int remote_port);
   int upload_file(transf_info transf);

   std::string get_ip(void);
   int get_port(void);
 
 private:
   Socket_base* cli_sock_;    

};