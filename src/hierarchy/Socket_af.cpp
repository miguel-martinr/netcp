#include "../../include/hierarchy/Socket_af.hpp"

#include <arpa/inet.h>

// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <string>
// #include <unistd.h>
// #include <array>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

sockaddr_in Socket_af::get_sockaddr_in_from(const std::string ip_address, int port) {
  sockaddr_in my_address {};
  in_addr* ptr_to_inad = &(my_address.sin_addr);
  my_address.sin_family = AF_INET;

  if (ip_address.empty())
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    else
    inet_aton(ip_address.c_str(), ptr_to_inad);
    
  my_address.sin_port = htons(port);

  return my_address;
}