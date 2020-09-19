#include "../../include/hierarchy/Socket_af_dgram.hpp"

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <arpa/inet.h>

 
using namespace std;

bool quit = false;

void cmd_handler(void) {
  std::string cmd;
  while (!quit) {
    std::cin >> cmd;
    if (cmd == "quit") {
      quit = true;
    } else {
      std::cout << "Comando '" << cmd << "' no reconocido :(\n";
    }
  }
}


int main(int argc, char* argv[]) {

  std::vector<string> args;
  for (int i = 1; i < argc; i++)
    args.push_back(std::string(argv[i]));
  
  bool server_mode = false;
  int port = -1;
  std::string ip_addr;

  for (int i = 0; i < args.size(); i++) {
    if (args[i] == "-s" || args[i] == "--server") {
      server_mode = true;
    } else if (args[i] == "-p" || args[i] == "--port") {
      port = std::stoi(args[++i]);
    } else if (args[i] == "-i" || args[i] == "--ip-address") {
      ip_addr = std::string(args[++i]); 
    } else {
      std::cout << "\n\nModo de uso:"
                << "\n  ./bin/hierarchy/netcp OPCIONES"
                << "\n\nOpciones:"
                << "\n  -s --server  Modo servidor (client mode is set by default)"
                << "\n  -p --port    Especifica el puerto a usar, en modo servidor es opcional"
                << "\n";   
      return 0; 
    }
  }


  if (server_mode) { //Server mode
    if (port < 0)
      port = 0; //Any free port

    Socket_af_dgram serv_(ip_addr, port);
    std::cout << "\nServidor"
              << " \nIp:   " << serv_.ip()
              << " \nPort: " << serv_.port()
              << std::endl << std::endl;
    

    std::cout << "\nEscuchando...\n";
    std::thread cmd_handler_thread(cmd_handler);
    Message msg;
    sockaddr_in sender_address;

    /*
      Idea: meter while en un thread para porder matarlo cuando quit = true
    */

    while (!quit) {
      sender_address = serv_.receive(&msg);
      msg.text[sizeof(msg)-1] = '\0';
      std::cout << "\n" << inet_ntoa(sender_address.sin_addr) << ':' << ntohs(sender_address.sin_port) 
                << " dice: " << msg.text.data() << std::endl;
    

      /*
      Idea: Hacer una struct o clase que contenga a sockaddr_in y permita
            acceder más fácilmente a su ip y puerto. Así me ahorro el uso 
            explícito de ntohs() e inet_ntoa()
            ¿Cómo sé si se ha recibido y no ha saltado el timeout?
      */
    }

    cmd_handler_thread.join();
    
  } else { //Client mode
    if (port < 0) {
      std::cout << "\nIntroduzca un puerto válido \n";
      return port;
    }

    if (ip_addr.empty()) {
      std::cout << "\nIntroduzca una ip válida \n";
      return -2;
    }

    Socket_af_dgram client_("127.0.1.1", 0);
    std::cout << "\nCliente"
              << " \nIp:   " << client_.ip()
              << " \nPort: " << client_.port()
              << std::endl << std::endl;


    int bytes_read;
    Message msg;
    std::cout << "\nEnviando a " << ip_addr << ':' << port << std::endl;
  
    while((bytes_read = read(STDIN_FILENO, &msg, sizeof(msg)-1)) != 0) {
      msg.text[bytes_read] = '\0';
      client_.send_to(msg,ip_addr,port);
    }
    std::cout << "\nEnvío finalizado\n";
    
  }



 return 0;
}