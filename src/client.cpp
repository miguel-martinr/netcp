#include "../include/client.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

client::client(std::string ip, int port) {
  cli_sock_ = new Socket_af_dgram(ip,port);
}

client::~client(void) {

}


int client::upload_file(transf_info transf) {
  
  int fd = open(transf.file_name.c_str(), O_WRONLY);
  if (fd < 0) {
    std::cout << "\nError abriendo " << transf.file_name << std::endl;
    return -1;
  }

/**
 * Idea: sería mejor enviar trans_info =
 */

  Message msg;
  msg.code_ = 3;
  memcpy(&msg.text, transf.file_name.c_str(), transf.file_name.size()-1);
  msg.text[transf.file_name.size()] = '\0';

  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip, transf.sender_port);

  msg = Message();
  received_info rec = reinterpret_cast<Socket_af_dgram*>(cli_sock_)->receive(&msg);//n = 5 segundos

  if (rec.ip() != transf.sender_ip) {
    std::cout << "\nError de seguridad >:(\n";
    return -99;
  }

  if (!rec.something_received) {
    std::cout << "\nNo hay respuesta del servidor :(\n";
    return -2;
  }

  if (msg.code_ != 4) {
    std::cout << "\nEl servidor no ha confirmado el envío :(\n";
    return -3;
  }

  int newport = msg.port_;
  

  msg = Message();

  int bytes_read = read(fd,&msg.text,sizeof(msg.text)-1);
  msg.text[bytes_read] = '\0';
  msg.code_ = 0;
  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);


  while ((bytes_read = read(fd,&msg.text,sizeof(msg.text)-1)) != 0) {
    msg.text[bytes_read] = '\0';
    if (bytes_read < sizeof(msg.text)-1)
      msg.code_ = 2;
      else 
      msg.code_ = 1; //Creo que no hacen falta los códigos de todas formas

    reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);

    msg = Message();
  }


  std::cout << "\nEnvío de " << transf.file_name << " finalizado.\n";

  return 0;
}