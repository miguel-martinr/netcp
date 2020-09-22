
#pragma once

#include <array>


/**
 * @struct Message
 * @brief Representa un mensaje POD (Plain old data)
 * con un texto de 1024 bytes (caracteres)
 * @details 
 * Codes:
 *   0 - 
 *   1 - Fragmento intermedio
 *   2 - Fragmento final
 *   3 - Continuar envío al puerto indicado en port_
 */
struct Message {
  
  // std::array<char,16> sender_ip; //Idea
  // int sender_port;
	std::array<char, 1024> text;
  int code_;
  int port_;
};