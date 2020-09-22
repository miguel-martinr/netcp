#pragma once

#include <netinet/in.h>
#include <string>


/**
 * @struct received_info 
 * @brief Envuelve una sockaddr_in con la información del Socket 
 *        que ha enviado el mensaje y un booleano para saber 
 *        si se ha recibido un mensaje.
 */
struct received_info {

  received_info(void);

  /**
   * @return ip a la que el socket sender está bindeado
   */
  std::string ip(void);

  /**
   * @return puerto al que el socket sender está bindeado
   */
  int port(void);
  
  
  
  sockaddr_in sender_info;
  bool something_received;

};
