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
  
  int fd = open(transf.file_name.c_str(), O_RDONLY); //Abre el fichero

  if (fd < 0) {
    std::cout << "\nError abriendo " << transf.file_name << std::endl;
    return -1;
  }

/**
 * Idea: sería mejor enviar trans_info =
 */

  Message msg;
  msg.code_ = 3;
  memcpy(&msg.text, transf.file_name.c_str(), transf.file_name.size());
  msg.text[transf.file_name.size()] = '\0';


  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip, transf.sender_port); //Solicita permiso para subir fichero

  msg = Message();
  received_info rec = reinterpret_cast<Socket_af_dgram*>(cli_sock_)->receive(&msg);//n = 5 segundos Espera la respuesta del servidor

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

  int newport = msg.port_; //Puerto abierto por el servidor
  

  msg = Message(); //Limpio msg

  int bytes_read = read(fd,&msg.text,sizeof(msg.text)-1); //Cargo un trozo del fichero en msg
  
  msg.text[bytes_read] = '\0'; 

  if (bytes_read < sizeof(msg.text)-1) 
    msg.code_ = 5;
    else 
    msg.code_ = 0;

  char str1[] = "\nEnviando -> ", str2[] = "<- a ";

  write(STDOUT_FILENO,&str1,13);
  write(STDOUT_FILENO,&msg.text,1023);
  write(STDOUT_FILENO,&str2,5);
  // std::cout << "\nOFFSET: " << lseek(fd)

  /**
   * Arreglar: parece que al enviar el primer mensaje el offset vuelve al principio
   */
  
  reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);

  while ((bytes_read = read(fd,&msg.text,sizeof(msg.text)-1)) != 0) {
    msg.text[bytes_read] = '\0';
    if (bytes_read < sizeof(msg.text)-1)
      msg.code_ = 2;
      else 
      msg.code_ = 1; //Creo que no hacen falta los códigos de todas formas

    reinterpret_cast<Socket_af_dgram*>(cli_sock_)->send_to(msg,transf.sender_ip,newport);
    write(STDOUT_FILENO,&str1,13);
    write(STDOUT_FILENO,&msg.text,1023);
    write(STDOUT_FILENO,&str2,5);
    msg = Message();
  }


  std::cout << "\nEnvío de " << transf.file_name << " finalizado.\n";

  return 0;
}