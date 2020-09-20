# netcp
`netcp` es la implementación de un programa cliente-servidor utilizado para la transferencia de ficheros múltiple y simultánea.

Hace uso de:
  * Sockets en linux
  * Hilos en C++ (<thread>)

## Jerarquía de clases Socket
> Esto puede considerarse un **subproyecto** de `netcp` y planeo extraerlo, junto a su documentación, a un repositorio propio :)<br/><br/>
Mi idea actualmente (a fecha 20 de Septiembre de 2020) es crear una jerarquía de clases Socket que se corresponda (en principio) con la siguiente estructura :

  * Socket_base : Clase abstracta base
    * Socket_af : Clase abstracta(?) base para aquellos sockets de la familia AF_INET (protocolo IPv4), tengo que corregir el nombre, el ideal sería `Socket_inet` y afectaría a todos sus hijos.
      * Socket_af_dgram : Implementación de un socket de la familia AF_INET no orientado a conexión (UDP).
      * Socket_af_stream : Implementación de un socket de la familia AF_INET orientado a conexión (TCP)
    * Socket_unix : Clase abstracta(?) base para aquellos sockets de la familia AF_UNIX (conexión local)
      * Socket_unix_dgram : Implementación de un socket de la familia AF_UNIX no orientado a conexión (UDP)
      * Socket_unix_stream : Implementación de un socket de la familia AF_UNIX orientado a conexión (TCP)
  
