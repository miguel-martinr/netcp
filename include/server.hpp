#pragma once

#include "../include/Socket_af_dgram.hpp"

/**
 * @class server
 * @brief Implementa el servidor netcp
 */
class server {

  public:
    server(void);
    ~server(void);




  private:
    /**
     * @note Puede causar problemas el usar un puntero a socket? Cuál es la mejor opción
     * y porqué
     */
    Socket_af_dgram* sv_sock_;

    
};