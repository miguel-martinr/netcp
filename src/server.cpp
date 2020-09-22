#include "../include/server.hpp"

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

server::server(std::string ip, int port) {
  sv_sock_ = new Socket_af_dgram(ip,port);  
  quit_ = false;
}

server::~server(void) {

}

std::string server::get_ip(void) {
  return sv_sock_->ip();
}

int server::get_port(void) {
  return sv_sock_->port();
}

int server::upload_file(transf_info new_transf) {
  int fd = open(new_transf.file_name.c_str(), O_WRONLY);
  if (fd < 0) {
    std::cout << "\nError subiendo " << new_transf.file_name << " :(\n";
    return -1;
  }

  Socket_af_dgram receiver;
  Message msg;
  msg.port_ = receiver.port();
  msg.code_ = 3;

  //Indicar al cliente el nuevo puerto y que siga
  //transmitiendo
  receiver.send_to(msg, new_transf.sender_ip, new_transf.sender_port); 

  received_info rec_;
  
  do {
    rec_.something_received = false;
    rec_ =  receiver.receive(&msg);

    if (write(fd,&msg.text,sizeof(msg.text)) < 0) {
      std::cout << "\nFallo en write(): " << new_transf.file_name << std::endl;
      rec_.something_received = false;
    }

  } while (!quit_ && rec_.something_received);
  
  std::cout << "\n Transferencia de " << new_transf.file_name << " finalizada.\n";
  return 0;
}