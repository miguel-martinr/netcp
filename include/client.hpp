#pragma once

#include "Socket_af_dgram.hpp"
#include "transf_info.hpp"

#include <string>


class client {

 public:
   client(std::string ip = "", int port = 0);
   ~client(void);


   int upload_file(transf_info transf);

 
 
 private:
   Socket_base* cli_sock_;    

};