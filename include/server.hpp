#pragma once

#include "../include/Socket_af_dgram.hpp"
#include "../include/transf_info.hpp"


#include <thread>
#include <vector>

/**
 * @class server
 * @brief Implementa el servidor netcp
 */
class server {

  public:

    server(std::string ip = "", int port = 0);
    ~server(void);

    /**
     * @return std::string ip a la que está bindeado el socket principal del server
     */
    std::string get_ip(void);

    /**
     * @return int al que está bindeado el socket principal del server
     */
    int get_port(void);

    /**
     * @brief Sube un fichero al servidor (gestiona comunicación con el cliente)
     */
    int upload_file(transf_info new_transf);

    int listen(std::string dir = "");
  private:
    /**
     * @note Puede causar problemas el usar un puntero a socket? Cuál es la mejor opción
     * y porqué
     */
    Socket_base* sv_sock_;
    std::vector<std::thread> threads_;
    bool quit_;

    

};