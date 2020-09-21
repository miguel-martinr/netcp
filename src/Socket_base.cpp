#include "../include/Socket_base.hpp"

#include <arpa/inet.h>
#include <iostream> //provisional
#include <unistd.h>




// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <string>
// #include <array>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

Socket_base::~Socket_base(void) {
  close(fd_);
}

//Setters
void Socket_base::set_fd(int fd) {
  if (fd < 0) {
    //Lanzar excepción fd < 0
    std::cout << "\nError al crear socket\n"; //provisional
    perror("Error al crear socket:");
    return;
  }

  fd_ = fd;
}


//Getters
std::string Socket_base::ip(void) {
  return ip_;
}

int Socket_base::port(void) {
  return port_;
}

int Socket_base::fd(void) {
  return fd_;
}




/**
 * @details Es necesario que el socket ya esté bindeado, dado que esta función
 * hace uso de getsockname() para conocer la ip y el puerto.
 */
void Socket_base::initialize(void) {
 
  sockaddr_in sockinfo;
  socklen_t sockinfo_size = sizeof(sockinfo);
  getsockname(fd_,reinterpret_cast<sockaddr*>(&sockinfo),&sockinfo_size);

  port_ = ntohs(sockinfo.sin_port);
  ip_ = inet_ntoa(sockinfo.sin_addr);
}



