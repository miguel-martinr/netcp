#pragma once

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

struct Message {
	std::array<char, 1024> text;
};





class Socket
{
public:
	Socket(const sockaddr_in& address);
  Socket(const std::string& ip_address, int port);
  
  void initialize(void);


	~Socket();

  void send_to(const Message& message, const sockaddr_in& address);
  //ToDo: send_to al que solo se le pase el mensaje, la ip y el puerto (que se le pase lo menos posible)


  void receive_from(Message* message, sockaddr_in* address);
  //ToDo: un receive que devuelva la dirección de donde viene el mensaje (solo se le pasaría el contenedor mensaje)
  //ToDo: un receive que devuelva el mensaje (sin argumentos)
  //ToDo: un receive que devuelve el mensaje y se le pasa un contenedor dirección
  //ToDo: un receive que devuelva un struct que contenga el mensaje y la dirección (hacer ese struct)

  sockaddr_in make_ip_address(const std::string& ip_address, int port);


  int get_fd(void) {return fd_;}

  std::string ip_;
  int port_;


private:
	int fd_;
};