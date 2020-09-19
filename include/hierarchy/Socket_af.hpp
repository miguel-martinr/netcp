/**
 * @author Miguel Martín
 * @date 20200919
 */
#pragma once

#include "Socket_base.hpp"

/**
 * @class Socket_af
 * @brief Clase abstracta de un socket perteneciente a la familia AF_INET
 * Es decir, que permite "conexiones" tanto desde el mismo equipo como desde equipos
 * externos.
 */

class Socket_af : public Socket_base {

 public:

  /**
   * @brief Devuelve sockaddr_in inicializada 
   * @param ip_address Dirección ip a bindear al socket
   * @param port Puerto a bindear al socket
   */
   sockaddr_in get_sockaddr_in_from(const std::string ip_address, int port);

};