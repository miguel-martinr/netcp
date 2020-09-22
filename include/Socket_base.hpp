/**
 * @file Socket_base.hpp
 * @brief Clase abstracta Socket
 * @author Miguel Martín 
 * @date 20200919
 */


#pragma once

#include <array>
#include <netinet/in.h>
#include <string>

/**
 * @struct Message
 * @brief Representa un mensaje POD (Plain old data)
 * con un texto de 1024 bytes (caracteres)
 */
struct Message {
  int code_;
	std::array<char, 1024> text;
};

/**
 * @class Socket_base
 * @brief Clase abstracta base para un socket
 */
class Socket_base
{
public:



	virtual ~Socket_base(void);

//Getters
/** 
 * @brief Devuelve la ip del socket.
 * @return Objeto std::string que es la dirección ip a la que el socket está bindeado.
 */
  std::string ip(void);


//Setters
/**
 * @brief Settea el fd y verifica errores
 */
void set_fd(int fd);

/**
 * @brief Devuelve el puerto del socket.
 * @return int que es el puerto al que el socket está bindeado.
 */
  int port(void);

/**
 * @brief Devuelve el descriptor de fichero del socket
 */
  int fd(void); //Esto es peligroso?

/**
 * @brief Inicializa ip_ y port_ una vez bindeado el socket 
 */
  void initialize(void);




/**
 * @brief Devuelve sockaddr_in inicializada 
 * @param ip_address Dirección ip a bindear al socket
 * @param port Puerto a bindear al socket
 */
  virtual sockaddr_in get_sockaddr_in_from(const std::string ip_address, int port) = 0;

  
 private:

  std::string ip_;
  int port_;
	int fd_;
};