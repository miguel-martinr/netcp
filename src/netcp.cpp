#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
// Dirección del socket local
sockaddr_in local_address{};	// Así se inicializa a 0, como se recomienda
local_address.sin_family = AF_INET;	// Pues el socket es de dominio AF_INET
local_address.sin_addr.s_addr = htonl(INADDR_ANY);
local_address.sin_port = htons(0);


// Asignar la dirección al socket local
int result = bind(fd, reinterpret_cast<const sockaddr*>(&local_address),
			  sizeof(local_address))
if (result < 0) {
std::cerr << "falló bind: " << z << '\n';
return 5;	// Error. Terminar con un valor diferente y > 0
}
*/

struct Message {
	std::array<char, 1024> text;
};

sockaddr_in make_ip_address(const std::string& ip_address, int port) {
  sockaddr_in my_address {};
  in_addr* ptr_to_inad = &(my_address.sin_addr);
  my_address.sin_family = AF_INET;
  if (ip_address.empty())
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    else
    inet_aton(ip_address.c_str(), ptr_to_inad);
    
  my_address.sin_port = htons(port);
  return my_address;
}

class Socket
{
public:
	Socket(const sockaddr_in& address);
	~Socket();

  void send_to(const Message& message, const sockaddr_in& address);
  void receive_from(Message& message, sockaddr_in& address);


private:
	int fd_;
};

Socket::Socket(const sockaddr_in& address) {
  
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    std::cout << "Error al crear socket\n";
  }
  //error.handling ToDo
  
  int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address),
			              sizeof(address));
			  
  if (result < 0) {
    std::cout << "falló bind\n";
  }
  //error.handling ToDo
 
  
}

Socket::~Socket(void) {
  close(fd_);
}


/*

// Enviar un mensaje "¡Hola, mundo!" al socket remoto
std::string message_text("¡Hola, mundo!");

Message message;
message_text.copy(message.text.data(), message.text.size() - 1, 0)

...						// Inicializar otros campos de Message


int result = sendto(fd, &message, sizeof(message), 0,
	reinterpret_cast<const sockaddr*>(&remote_address),
sizeof(remote_address));
if (result < 0) {
std::cerr << "falló sendto: " << std::strerror(errno) << '\n';
return 6;	// Error. Terminar con un valor diferente y > 0
}
*/

void Socket::send_to(const Message& message, const sockaddr_in& address) {
int result = sendto(fd_, &message, sizeof(message), 0,
                    reinterpret_cast<const sockaddr*>(&address), 
                    sizeof(sockaddr_in));
if (result < 0) {
  std::cout << "Falló sendto.\n";
  //error.handling ToDo
}
}

void Socket::receive_from(Message& message, sockaddr_in& address) {

socklen_t src_len = sizeof(sockaddr_in);
int result = recvfrom(fd_, &message, sizeof(message), 0,
reinterpret_cast<sockaddr*>(&address), &src_len);
if (result < 0) {
std::cout << "falló recvfrom\n";
//errpr.handling ToDo
}
}



int main(void) {
    
  std::string my_ip = "192.168.0.10";
  const sockaddr_in add = make_ip_address(my_ip, 0);
  Socket my_socket(add);
    
  std::string message_text("¡Hola, mundo!");

  Message message;
  message_text.copy(message.text.data(), message.text.size() - 1, 0);
  my_socket.send_to(message, add);
  

    
    
    return 0;
}