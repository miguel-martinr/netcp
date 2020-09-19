#include "../include/Socket.h"
#include <errno.h>

Socket::Socket(const sockaddr_in& address) {
 
 
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    std::cout << "Error al crear socket\n";
  }
  //error.handling ToDo
  int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
			              sizeof(address));
			  //bind(socket1, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) << std::endl;
  if (result < 0) {
    perror("Falló bind: ");
  }
  //error.handling ToDo
  initialize();
}

Socket::Socket(const std::string& ip_address, int port) {
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    std::cout << "Error al crear socket\n";
  }
  //error.handling ToDo
  
  sockaddr_in address = make_ip_address(ip_address,port);
  int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
			              sizeof(address));
	
  if (result < 0) {
    perror("Falló bind: ");
  }
  //error.handling ToDo
  initialize();
}

void Socket::initialize(void) {
 
  sockaddr_in sockinfo;
  socklen_t sockinfo_size = sizeof(sockinfo);
  getsockname(fd_,reinterpret_cast<sockaddr*>(&sockinfo),&sockinfo_size);

  port_ = ntohs(sockinfo.sin_port);
  ip_ = inet_ntoa(sockinfo.sin_addr);
}

Socket::~Socket(void) {
  close(fd_);
}



void Socket::send_to(const Message& message, const sockaddr_in& address) {
    int result = sendto(fd_, &message, sizeof(message), 0,
                        reinterpret_cast<const sockaddr*>(&address), 
                        sizeof(address));
    if (result < 0) {
      std::cout << "Falló sendto.\n";
      //error.handling ToDo
    }
}



void Socket::receive_from(Message* message, sockaddr_in* address) {
  socklen_t src_len = sizeof(sockaddr_in);
  // std::cout << "FD: " << fd_ << std::endl;
  int result = recvfrom(fd_, message, sizeof(*message), 0,
	                      reinterpret_cast<sockaddr*>(address), 
                        &src_len);
  if (result < 0) {
    // std::cout << "falló recvfrom\n";
    perror("Falló recvfrom: ");
    //error.handling ToDo
  }
}


sockaddr_in Socket::make_ip_address(const std::string& ip_address, int port) {
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


//Tal vez sea mejor hacer que make_ip_address sea miembro de Socket
