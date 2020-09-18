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
#include <stdlib.h>




int main(int argc, char* argv[]) {
  std::string ip_add, finput_name;
  int input_fd, port = 0;

  /*
  Quiero algo que pueda usar como si fuera el 
  case y shift de bash pero en c++ para parsear 
  el argv[]
  */
  
  bool get_from_std = true;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file") {
      finput_name = argv[++i];
      get_from_std = false;
    
    } else if (std::string(argv[i]) == "-i" || std::string(argv[i]) == "--ip-address") {
      ip_add = argv[++i];
  
    } else if (std::string(argv[i]) == "-p" || std::string(argv[i]) == "--port") {
      port = std::stoi(argv[++i]);
    }
  }

  //std::cout << "\nip: " << ip_add << "\nport: " << port << "\nfinput_name: " << finput_name << std::endl;

  Socket client_(std::string(),0); //ToDo: try-catch para Socket

  if (!get_from_std) {
    input_fd = open(finput_name.c_str(), O_RDONLY);
    if (input_fd < 0) {
      perror("Error al abrir fichero: ");
      return -1;
    }
  } else {
    input_fd = STDIN_FILENO;
  }


  Message message;
  while (read(input_fd, &message, sizeof(message)) != 0){
    client_.send_to(message, make_ip_address(ip_add, port));
  }

  close(input_fd);
  
  return 0;
}