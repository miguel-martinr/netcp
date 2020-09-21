/**
 * 
 * @author Miguel Martín
 * @date 20200919
 */


#pragma once
#include "Socket_af.hpp"

/**
 * @struct Devuelta por el método Socket_af_dgram::receive(), envuelve
 * una sockaddr_in @a sender_info con la información del Socket que ha enviado el mensaje
 * y un booleano @a something_received para saber si se ha recibido un mensaje.
 */
struct received_info {
  sockaddr_in sender_info;
  bool something_received;
};

/**
 * @class Socket de la familia AF_INET y no orientado a conexión
 */
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
   * @param stimeout Número máximo de segundos que esperará el socket hasta estar listo para leer (read readiness)
   * @return Retorna una struct sockaddr_in con la dirección de donde ha recibido el mensaje
   */
  received_info receive(Message* msg, int stimeout = 5);


};