#include "../../include/hierarchy/Socket_af_dgram.hpp"

#include <iostream>
#include <vector>
 
using namespace std;


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


  if (server_mode) {
    if (port < 0)
      port = 0; //Any free port

    Socket_af_dgram serv_(ip_addr, port);
    std::cout << "\nServidor"
              << " \nIp:   " << serv_.ip()
              << " \nPort: " << serv_.port()
              << std::endl << std::endl;
    

  } else { //Cliente mode
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
    
  }



 return 0;
}