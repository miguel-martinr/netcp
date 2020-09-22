# netcp
`netcp` es la implementación de un programa cliente-servidor utilizado para la transferencia de ficheros múltiple y simultánea.

Hace uso de:
  * Sockets en linux
  * Hilos en C++ (`std::thread`)

### Por hacer 
* 20/09/2020 21:00 Quiero crear una clase server e introducir en ella las funciones que realiza el programa en el modo server (server_mode = true) (en proceso)
* Sistema para el envío de ficheros. ¿Como diferencio entre enviar mensajes individuales y ficheros? -> Enviar ficheros fragmentándolos en mensajes -> Requiere establecer una estructura de mensaje que tenga campos con un código que indique si es el primero, intermedio, etc...
* Excepciones (mirar lo hecho en el repositorio <a href="https://github.com/miguel-martinr/Data-Structure-Classes" target="_blank">DSC</a>
* ¿Podría transferir el método bind a un nivel superior en la jerarquía de Socket? -> ¿Cuál es la diferencia al bindear cada tipo de socket?

### Hecho
* 20/09/2020 21:11 Voy a reorganizar todo el proyecto
  * Eliminar Socket.h hecho (20/09/2020 22:55)
  * Sacar ficheros de include/hierarchy y src/hierarchy y eliminar esos directorios (hecho 20/09/2020 22:55)
  * Corregir makefile para que funcione con la nueva organización (hecho 20/09/2020 22:55)

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
  
