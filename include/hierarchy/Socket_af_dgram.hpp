/**
 * 
 * @author Miguel Martín
 * @date 20200919
 */


#pragma once
#include "Socket_af.hpp"

class Socket_af_dgram : public Socket_af {
 public:
  Socket_af_dgram(std::string ip, int port);
  ~Socket_af_dgram(void);

  /**
   * @brief Bindea el socket a la ip y puerto especificados
   * @param ip Dirección ip a la que bindear el socket
   * @param port Puerto al que bindear el socket
   */
  void bindsock(int fd, std::string ip, int port);
  
  /**
   * @brief Envía el mensaje @a msg al socket bindeado a la dirección @a remote_ip
   * y puerto @a remote_port 
   * @param remote_ip Dirección ip remota
   * @param remote_port Puerto remoto
   */
  void send_to(Message msg, std::string remote_ip, int remote_port);
  
  /**
   * @brief Recive un mensaje y lo guarda en el Message apuntado por @a msg
   * @param msg Puntero a una estructura @a Message
   * @return Retorna una struct sockaddr_in con la dirección de donde ha recibido el mensaje
   */
  sockaddr_in receive(Message* msg);

  
};