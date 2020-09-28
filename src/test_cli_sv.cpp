#include "../include/server.hpp"
#include "../include/client.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <ifaddrs.h>
#include <vector>
#include <netdb.h>

using namespace std;


vector<string> get_ifs(void) {
  vector<string> ifs;
  char host[1025];
 

  ifaddrs *ifap;
  ifaddrs *item;
  getifaddrs(&ifap);
  
  for (item = ifap; item != NULL; item = item->ifa_next) {
    if (item->ifa_addr->sa_family == AF_INET) {
      getnameinfo(item->ifa_addr, sizeof(sockaddr_in), host, 1025, NULL,0,1);
      ifs.push_back(string(host));
    }
  }

  return ifs;
}



int main(int argc, char* argv[]) {

  vector<string> args;
  for (int i = 1; i < argc; i++)
    args.push_back(string(argv[i]));
  
  bool server_mode = false;
  string local_ip, remote_ip, filename, output_dir;
  int local_port = 0, remote_port = 0;

  for (int i = 0; i < args.size(); i++) {
    if (args[i] == "-s" || args[i] == "--server-mode") {
      server_mode = true;
    } else if (args[i] == "-ri" || args[i] == "--remote-ip") {
      if (i == args.size()+1) {
        std::cout << "\nIntroduzca una remote_ip válida >:c\n";
        return -1;
      }
      remote_ip = args[++i];
    } else if (args[i] == "-li" || args[i] == "--local-ip") {
      if (i == args.size()-1) {
        cout << "\nIntroduzca una local_ip válida >:c\n";
        return -1;
      }
      local_ip = args[++i];
    } else if (args[i] == "-lp" || args[i] == "--local-port") {
      if (i == args.size()-1) {
        cout << "\nIntroduzca un puerto local válido >:c\n";
        return -1;
      }
      local_port = stoi(args[++i]);
    } else if (args[i] == "-rp" || args[i] == "--remote-port") {
      if (i == args.size()-1) {
        cout << "\nIntroduzca un puerto remoto válido >:c\n";
        return -1;
      }
      remote_port = stoi(args[++i]);
    } else if (args[i] == "-f" || args[i] == "--file") {
      if (i == args.size()-1) {
        cout << "\nIntroduzca un nombre de fichero válido :(\n";
        return -1;
      }
      filename = args[++i];
    } else if (args[i] == "-d" || args[i] == "--directory") {
      if (i == args.size()-1) {
        cout << "\nIntroduzca un directorio de salida válido >:c\n";
        return -1;
      }
      output_dir = args[++i];
      if (output_dir[output_dir.size()-1] != '/')
        output_dir = output_dir + '/';
    } else {
      cout << "\nNo se reconoce : " << args[i] << endl;
      cout << "\nModo de uso:\n"
           << "\n  bin/test_cli_sv"
           << "\nOpciones:\n"
           << "\n-s o --server  Activa modo server (el modo cliente está activado por defecto)"
           << "\n-ri o --remote-ip"
           << "\n-li o --local-ip"
           << "\n-rp o --remote-port"
           << "\n-lp o --local-port"
           << "\n";
      return 0;
    }

  }

  if (server_mode) { //server mode
    server test_sv(local_ip, local_port);
    cout << "\nServidor\n"
         << "\n ip:   " << test_sv.get_ip()
         << "\n port: " << test_sv.get_port()
         << "\n\n";

 
    
    cout << "\nEscuchando...\n";
    test_sv.listen(output_dir);   
  } else { 
    
    
    //client mode
    if (local_ip.empty()) {
      int ip_opt = -1;
      vector<string> ifs = get_ifs();
      for (int i = 0; i < ifs.size(); i++) 
        cout << endl << ' ' << i << ". <" << ifs[i] << "> "; 
      
      do {
        cout << "\nSeleccione una ip > "; 
        cin >> ip_opt;
      } while (ip_opt < 0 || ip_opt >= ifs.size());
      local_ip = ifs[ip_opt];
    }


    client test_cli(local_ip,local_port);
    cout << "\nCliente\n"
         << "\n " << test_cli.get_ip() << ':' << test_cli.get_port() 
         << endl;


    if (filename.empty()) {
      cout << "\nFichero a subir > ";
      cin >> filename;
    }
    
    while (remote_ip.empty()) {
      cout << "\nremote_ip  > ";
      cin >> remote_ip;
    }

    while(remote_port == 0) {
      cout << "\nremote_port > ";
      cin >> remote_port;
    }

    cout << "\nSubiendo " << filename << " a " << remote_ip << ':' << remote_port << endl;
    test_cli.upload_file(filename,remote_ip,remote_port);
  }
  

  return 0;
}