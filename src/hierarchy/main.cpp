#include "../../include/hierarchy/Socket_af_dgram.hpp"

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <arpa/inet.h>

 
using namespace std;

/**
 * @brief el programa termina si @a quit == true
 */
bool quit = false;

void cmd_handler(void) {
  std::string cmd;
  while (!quit) {
    std::cin >> cmd;
    if (cmd == "quit") {
      std::cout << "\nFinalizando el programa...\n";
      quit = true;
    } else {
      std::cout << "Comando '" << cmd << "' no reconocido :(\n";
    }
  }
}


int main(int argc, char* argv[]) {

  
  bool server_mode = false;
  int port = -1;
  std::string ip_addr;

  //Parseando argumentos del programa
  std::vector<string> args;
  for (int i = 1; i < argc; i++)
    args.push_back(std::string(argv[i]));


  for (int i = 0; i < args.size(); i++) {
    if (args[i] == "-s" || args[i] == "--server") {
      server_mode = true;
    } else if (args[i] == "-p" || args[i] == "--port") {
      if (i == args.size() - 1) {
        std::cout << "\nIntroduzca un puerto válido\n";
        return -1;
      }
      port = std::stoi(args[++i]);
    } else if (args[i] == "-i" || args[i] == "--ip-address") {
      if (i == args.size()-1) {
        std::cout << "\nIntroduzca una ip válida\n";
        return -1;
      }
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
    std::cout << "\nModo servidor"
              << " \nIp:   " << serv_.ip()
              << " \nPort: " << serv_.port()
              << std::endl << std::endl;
    

    std::cout << "\nEscuchando...\n";
    std::thread cmd_handler_thread(cmd_handler);
    
    Message msg, empty_msg;
    empty_msg.text[0] = '\0';
    received_info rec_info;

    /*
      Idea: meter while en un thread para porder matarlo cuando quit = true
      sería una función receive_messages()

      Debería crear una clase server y encapsular todo lo que hace main en server_mode
      dentro de ella?

      Cuestión: como diferencio entre recibir un mensaje y recibir un fichero? Recibir
      un fichero puede ser recibir fragmentos de dicho fichero como mensajes pero necesito
      saber cuando es el primer fragmento, un fragmento intermedio y el final. (O principio
      y final al mismo tiempo)
    */

    while (!quit) {
      rec_info = serv_.receive(&msg, 1);
      if (rec_info.something_received) {
        msg.text[sizeof(msg)-1] = '\0';
        std::cout << "\n" << inet_ntoa(rec_info.sender_info.sin_addr) << ':' << ntohs(rec_info.sender_info.sin_port) 
                  << " dice: " << msg.text.data() << std::endl;
        msg = empty_msg;
      }
      /*
        Bugs:
        *La primera vez que se recibe un mensaje se imprime un puerto que no corresponde al puerto real del cliente
      */

      /*
      Idea: Hacer una struct o clase que contenga a sockaddr_in y permita
            acceder más fácilmente a su ip y puerto. Así me ahorro el uso 
            explícito de ntohs() e inet_ntoa() (Socket_af_dgram::receive() 
            devolverá una instancia de esta struct)
            
            ¿Cómo sé si se ha recibido y no ha saltado el timeout? -> Lo hice con select()
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