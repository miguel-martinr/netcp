#include "../include/server.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

  cout << "\nserver test...\n";
  server netcp_server;
  cout << "\nIp  : " << netcp_server.get_ip() << endl;
  cout << "\nPort: " << netcp_server.get_port() << endl;


  

  return 0;
}