#include "../include/server.hpp"

server::server(void) {
  sv_sock_ = new Socket_af_dgram();


}

server::~server(void) {

}

std::string server::get_ip(void) {
  return sv_sock_->ip();
}

int server::get_port(void) {
  return sv_sock_->port();
}