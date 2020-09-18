#include "../include/Socket.h"

#include <iostream> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

sockaddr_in make_ip_address(const std::string& ip_address, int port) {
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

int main(void) {

  sockaddr_in remote_address = make_ip_address("192.168.0.10", 2000);
  sockaddr_in local_address = make_ip_address("192.168.0.10", 2001);
  Socket local(local_address);
  Message message;
  std::cout << "Tamaño de message: " << sizeof(message.text) << std::endl; 
  std::cout << "Escuchando..." << std::endl;
  int i = 0;
  while (true) {
    local.receive_from(message, remote_address);
    std::cout << "He recibido: -->[" << message.text[i++] << "] <--";
  }

  
  return 0;
}