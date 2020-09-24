#include "../include/server.hpp"

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <sstream>

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
  int fd = open(new_transf.file_name.c_str(), O_CREAT | O_WRONLY | O_RDONLY, S_IWUSR | S_IRUSR | S_IWOTH);
  if (fd < 0) {
    std::cout << "\nError subiendo " << new_transf.file_name << " :(\n";
    return -1;
  }

  Socket_af_dgram receiver(sv_sock_->ip() );
  Message msg;
  msg.port_ = receiver.port();
  msg.code_ = 4;

  //Indicar al cliente el nuevo puerto y que siga
  //transmitiendo
  
  std::mutex sv_sock_mutex;
  sv_sock_mutex.lock();
  reinterpret_cast<Socket_af_dgram*>(sv_sock_)->send_to(msg, new_transf.sender_ip, new_transf.sender_port); 
  sv_sock_mutex.unlock();

  received_info rec_;
  
  do {
    rec_.something_received = false;
    rec_ =  receiver.receive(&msg,1);
    std::cout << "\nMENSAJE RECIBIDO : " << msg.text.data() << std::endl;
    if (rec_.something_received) {
      if (write(fd,&msg.text,sizeof(msg.text)) < 0) {
        std::cout << "\nFallo en write(): " << new_transf.file_name << std::endl;
        rec_.something_received = false;
      }
    }
  } while (!quit_ && rec_.something_received);
  /**
   * Hay que arreglar: por qué recibe dos veces el mismo mensaje??
   */
  std::cout << "\n Transferencia de " << new_transf.file_name << " finalizada.\n";
  return 0;
}


int server::listen(void) {
  
  Message msg;
  received_info rec;
  transf_info transf;
  while(!quit_) {
    rec = reinterpret_cast<Socket_af_dgram*>(sv_sock_)->receive(&msg,1);
    
    if (rec.something_received) {
      if (msg.code_ == 3) { //petición para subir fichero
        //transf.file_name = 
        std::stringstream(std::string(msg.text.data())) >> transf.file_name;
        transf.sender_ip = rec.ip();
        transf.sender_port = rec.port();
        std::cout << "\nIniciando subida de " << transf.file_name << "...\n";
        upload_file(transf);
      }
    }

    msg = Message();
    transf = transf_info();
  }

  return 0;
}