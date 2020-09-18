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







int main(void) {

  sockaddr_in remote_address = make_ip_address("127.0.1.1", 1123);
  sockaddr_in local_address = make_ip_address("192.168.1.37", 2000);


  Socket local(local_address);

  
  int test_file = open("tests/prueba.txt", O_RDONLY);
  
  if (test_file < 0) {
    std::cout << "Error al abrir fichero tests/prueba.txt\n";
    return -1;
  }

  Message message;
  
  int i = 0;
  char buff;
  while (read(test_file, &message, sizeof(message)) != 0){
    local.send_to(message, remote_address);
   // sendto(local.get_fd(), &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&remote_address), sizeof(remote_address));
    std::cout << std::endl << "He enviado: " << message.text.begin() << std::endl;
  }

  

  //read(test_file, &message.text[0], sizeof(message.text));


  
  close(test_file);

  return 0;
}