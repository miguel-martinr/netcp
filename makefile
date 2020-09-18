#############################################
CC = g++
CFLAGS = -g -std=c++11 -pthread
#############################################


bin/server: src/server.cpp bin/Socket.o
	$(CC) $(CFLAGS) src/server.cpp bin/Socket.o -o bin/server

bin/client: src/client.cpp bin/Socket.o
	$(CC) $(CFLAGS) src/client.cpp bin/Socket.o -o bin/client

bin/send: src/NetcpSend.cpp bin/Socket.o
	$(CC) $(CFLAGS) src/NetcpSend.cpp bin/Socket.o -o bin/send 

bin/receive: src/NetcpReceive.cpp bin/Socket.o
	$(CC) $(CFLAGS) src/NetcpReceive.cpp bin/Socket.o -o bin/receive


bin/Socket.o: include/Socket.h src/Socket.cpp
	$(CC) $(CFLAGS) -c src/Socket.cpp -o bin/Socket.o



.PHONY:
clean:
	rm *.o
