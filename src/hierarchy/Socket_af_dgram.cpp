/**
 * 
 * @author Miguel Martín
 * @date 20200919
 */

#include "../../include/hierarchy/Socket_af_dgram.hpp"

#include <iostream> //provisional
#include <sys/time.h>


Socket_af_dgram::Socket_af_dgram(std::string ip, int port) {
  int fd = socket(AF_INET, SOCK_DGRAM, 0); 
  set_fd(fd); //Hay que hacer un try catch aquí?
  bindsock(fd,ip,port);
  initialize();
}

Socket_af_dgram::~Socket_af_dgram(void) {

}

void Socket_af_dgram::bindsock(int fd, std::string ip, int port) { //Debería transferirla a Socket_base y quitar el parámetro fd? 
  sockaddr_in socket_address = get_sockaddr_in_from(ip,port);
  int result = bind(fd,reinterpret_cast<const sockaddr*>(&socket_address),sizeof(socket_address));
  if (result < 0) {
    //lanzar excepción error al bindear
    std::cout << "\nError al bindear\n"; //provisional
    perror("Error al bindear: "); //provisional
    return;
  }
}

void Socket_af_dgram::send_to(Message msg, std::string remote_ip, int remote_port) {
  sockaddr_in remote_addr = get_sockaddr_in_from(remote_ip, remote_port);
  int result = sendto(fd(), &msg, sizeof(msg), 0,
                      reinterpret_cast<const sockaddr*>(&remote_addr), 
                      sizeof(remote_addr));
    if (result < 0) {
      //Lanzar excepción (?) fallo en send
      std::cout << "Falló sendto.\n"; //provisional
      perror("Fallo sendto: ");
    }
}

received_info Socket_af_dgram::receive(Message* msg) {
  received_info info;
  sockaddr_in remote_address;
  info.something_received = false;
  socklen_t remote_address_size = sizeof(remote_address);
  
  fd_set fd_;
  FD_ZERO(&fd_);
  FD_SET(fd(),&fd_);

  //Set timeout to 5 secs 
  struct timeval tv;
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  int result = select(fd()+1, &fd_, NULL, NULL, &tv);
  if (result > 0) {
    result = recvfrom(fd(),msg,sizeof(*msg),0,
                          reinterpret_cast<sockaddr*>(&remote_address),
                          &remote_address_size);
    if (result < 0) {
      std::cout << "\nError en recvfrom()\n"; //provisional
      perror("Error recfrom():"); //provisional
      //Lanzar excepción (?) error recvfrom
    }
    info.something_received = true; //Se ha recibido un mensaje
  } else if (result < 0) {
    std::cout << "\nListo\n";
    std::cout << "\nError slect()\n"; //Provisional
    perror("Error select():"); //Provisional
  }
  

  /*
    Ideas: 
    *En la struct que contendrá sockaddr_in y que este método devolverá
    puedo poner un bool para indicar que se recibió un mensaje (HECHO)
      -Falta facilitar acceso a ip y puerto

    *Pasar argumento int timeout 
  */

  info.sender_info = remote_address;
  return info;
}