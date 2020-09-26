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


int client::upload_file(std::string filename, std::string remote_ip, int remote_port) {
  transf_info transf;
  transf.file_name = filename;
  transf.sender_ip = remote_ip;
  transf.sender_port = remote_port;
  return upload_file(transf);
}


std::string client::get_ip(void) {
  return cli_sock_->ip();  
}

int client::get_port(void) {
  return cli_sock_->port();
}

int client::upload_file(transf_info transf) {
  

/**
 * Idea: sería mejor enviar trans_info =
 */

  Message msg;
  msg.code_ = 3; //Solicitar envío
  memcpy(&msg.text, transf.file_name.c_str(), transf.file_name.size()); //Copio el nombre del fichero
  msg.text[transf.file_name.size()] = '\0';
  msg.bytes_read_ = transf.file_name.size();
  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip, transf.sender_port); //Solicita permiso para subir fichero

  received_info rec = reinterpret_cast<Socket_af_dgram*>(cli_sock_)->receive(&msg,20);//n = 20 segundos Espera la respuesta del servidor

  if (rec.ip() != transf.sender_ip) { //Si responde otra ip error de seguridad
    std::cout << "\nError de seguridad >:("
              << "\nSe esperaba " << transf.sender_ip << " y se obtuvo " << rec.ip() << std::endl;
    return -99;
  }
    
  if (!rec.something_received) { //Si no recibe nada -> no hay respuesta del servidor
    std::cout << "\nNo hay respuesta del servidor :(\n";
    return -2;
  }

  if (msg.code_ != 4) { //Si el servidor no acepta 
    std::cout << "\nEl servidor no ha confirmado el envío :(\n";
    return -3;
  }

  //servidor aceptó el envío

  int fd = open(transf.file_name.c_str(), O_RDONLY); //Abre el fichero

  if (fd < 0) {
    std::cout << "\nError abriendo " << transf.file_name << std::endl;
    return -1;
  }

  int newport = msg.port_; //Puerto abierto por el servidor
  

  //Empieza el envío
  int bytes_read = read(fd,&msg.text,sizeof(msg.text)-1); //Cargo un trozo del fichero en msg
  msg.text[bytes_read] = '\0'; 

  if (bytes_read < sizeof(msg.text)-1) 
    msg.code_ = 5; //El fichero entero cabe en msg
    else 
    msg.code_ = 0; //Se necesitará más de un envío

  msg.bytes_read_ = bytes_read;

 



  
  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);

  while ((bytes_read = read(fd,&msg.text,sizeof(msg.text)-1)) != 0) {
    msg.text[bytes_read] = '\0';
    if (bytes_read < sizeof(msg.text)-1)
      msg.code_ = 2;
      else 
      msg.code_ = 1; //Creo que no hacen falta los códigos de todas formas
    msg.bytes_read_ = bytes_read;
    reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);
  }

  if (msg.code_ != 2) {
    msg.bytes_read_ = 0;
    msg.code_ = 2;
    reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);
  }

  close(fd);
  std::cout << "\nEnvío de " << transf.file_name << " finalizado.\n";

  return 0;
}