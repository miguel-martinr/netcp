# Netcp
## Introducción
`netcp` es la implementación de un programa cliente-servidor utilizado para la transferencia de ficheros múltiple y simultánea.

Hace uso de:
  * Sockets en linux
  * Hilos en C++ (`std::thread`)


## El servidor
El servidor (implementado por  `class server`) funciona mediante mensajes (representados por `struct Message`) cuyos campos indican el estado de la transferencia.
### Message

```
struct Message {
  int code_;
  std::array<char,1024> text;
  
}
```
#### codes
5 = Primer y único mensaje 

0 = Mensaje inicial
1 = Fragmento intermedio
2 = Mensaje final

3 = Solicitud para empezar envío de fichero (cli -> sv)
4 = Confirmación para empezar envío de fichero (sv -> cli)


## El cliente
`class client`
### Pasos para envío de un fichero
  1. Abre el fichero y comprueba
  2. Envía un Message con código 3 y el nombre del fichero al socket principal del server
  3. Espera n segundos por la respuesta del servidor
  4. 
    * Si el servidor confirma el envío entonces empieza a enviar al nuevo puerto indicado por el servidor
    * Si no lo recibe (o recibe un código de error) lo comunica






### Por hacer 
* Excepciones (mirar lo hecho en el repositorio <a href="https://github.com/miguel-martinr/Data-Structure-Classes" target="_blank">DSC</a>
* ¿Podría transferir el método bind a un nivel superior en la jerarquía de Socket? -> ¿Cuál es la diferencia al bindear cada tipo de socket?
* Tengo que idear un mecanismo de comunicación entre cliente y servidor -> El cliente solicita subir un fichero, el servidor verifica que se pueda subir (o lo pone en una cola hasta que se pueda?) y si es así abre un hilo para recibir el fichero y un socket en ese puerto para recibirlo, le comunica el puerto al cliente para que este empieze a transmitir
* Como termino adecuadamente el programa? -> Terminar hilos | Donde hago el join() ? Es siquiera necesario?
* Cuando el cliente envía a un puerto donde no hay un servidor escuchando aparece el mensaje error de seguridad (ip) en vez de no hay respuesta del servidor -> Revisar
* No está funcionando al intentar enviar un fichero desde otro PC de la lan -> Espera la ip del servidor pero recibe 253.127.0.0 o 0.0.0.0 -> REVISAR

### Hecho
* 20/09/2020 21:11 Voy a reorganizar todo el proyecto
  * Eliminar Socket.h hecho (20/09/2020 22:55)
  * Sacar ficheros de include/hierarchy y src/hierarchy y eliminar esos directorios (hecho 20/09/2020 22:55)
  * Corregir makefile para que funcione con la nueva organización (hecho 20/09/2020 22:55)
* 20/09/2020 21:00 Quiero crear una clase server e introducir en ella las funciones que realiza el programa en el modo server (server_mode = true) (en proceso) LISTO
* Sistema para el envío de ficheros. ¿Como diferencio entre enviar mensajes individuales y ficheros? -> Enviar ficheros fragmentándolos en mensajes -> Requiere establecer una estructura de mensaje que tenga campos con un código que indique si es el primero, intermedio, etc...  LISTO

## Jerarquía de clases Socket
> Esto puede considerarse un **subproyecto** de `netcp` y planeo extraerlo, junto a su documentación, a un repositorio propio :)<br/><br/>
Mi idea actualmente (a fecha 20 de Septiembre de 2020) es crear una jerarquía de clases Socket que corresponda (en principio) a la siguiente estructura :

  * Socket_base : Clase abstracta base
    * Socket_af : Clase abstracta(?) base para aquellos sockets de la familia AF_INET (protocolo IPv4), tengo que corregir el nombre, el ideal sería `Socket_inet` y afectaría a todos sus hijos.
      * Socket_af_dgram : Implementación de un socket de la familia AF_INET no orientado a conexión (UDP).
      * Socket_af_stream : Implementación de un socket de la familia AF_INET orientado a conexión (TCP)
    * Socket_unix : Clase abstracta(?) base para aquellos sockets de la familia AF_UNIX (conexión local)
      * Socket_unix_dgram : Implementación de un socket de la familia AF_UNIX no orientado a conexión (UDP)
      * Socket_unix_stream : Implementación de un socket de la familia AF_UNIX orientado a conexión (TCP)
  
