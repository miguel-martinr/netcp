#include "../include/Socket.h"

#include <arpa/inet.h>
#include <array>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>


bool quit = false;


//Puertos no asignados: 47002-47099

void cmd_handler(void) {
   std::string cmd;
   while (!quit) {
     std::cin >> cmd;

     if (cmd == "quit") {
       quit = true;
       sleep(1);
       kill(getpid(), SIGTERM);
     } else {

     }
   }
}



int main(int argc, char* argv[]) {

  std::string ip_add;
  int port = 0;



  if (argc == 3) {
    ip_add = argv[1];
    port = std::stoi(argv[2]);
  } else {
    std::cout << "\nServer 21\n";
    std::cout << " IP   > ";
    std::cin >> ip_add;
    std::cout << " port > ";
    std::cin >> port;
  }

  system("clear");


  std::thread cmd_handler_thread(cmd_handler);

  Socket server_(ip_add,port);
  //try-catch para server
  
  std::cout << "\nServer 21\n";
  std::cout << "\n Ip   :" << server_.ip_
            << "\n Port :" << server_.port_
            << std::endl;
  
  
  Message message;
  
  sockaddr_in sender_addr;
  
  std::cout << "Server is running...\n";
  while (!quit) {
    server_.receive_from(&message, &sender_addr);
    std::cout << "Se ha recibido " << message.text.begin() << std::endl;
  }

  cmd_handler_thread.join();
  return 0;
}