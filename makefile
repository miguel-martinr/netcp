#############################################
CC = g++
CFLAGS = -g -std=c++11 -pthread
#############################################
#Socket Hierarchy

HCHY_INCLUDE = include/hierarchy
HCHY_SRC = src/hierarchy
HCHY_BIN = bin/hierarchy

HCHY_OBJS = $(HCHY_BIN)/Socket_base.o $(HCHY_BIN)/Socket_af.o $(HCHY_BIN)/Socket_af_dgram.o

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



#Socket Hierarchy 

$(HCHY_BIN)/Socket_base.o: $(HCHY_INCLUDE)/Socket_base.hpp $(HCHY_SRC)/Socket_base.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_base.cpp -o $(HCHY_BIN)/Socket_base.o

$(HCHY_BIN)/Socket_af.o: $(HCHY_INCLUDE)/Socket_af.hpp $(HCHY_SRC)/Socket_af.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_af.cpp -o $(HCHY_BIN)/Socket_af.o

$(HCHY_BIN)/Socket_af_dgram.o: $(HCHY_INCLUDE)/Socket_af_dgram.hpp $(HCHY_SRC)/Socket_af_dgram.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_af_dgram.cpp -o $(HCHY_BIN)/Socket_af_dgram.o

$(HCHY_BIN)/netcp: $(HCHY_OBJS) $(HCHY_SRC)/main.cpp
	$(CC) $(CFLAGS) $(HCHY_SRC)/main.cpp $(HCHY_OBJS) -o $(HCHY_BIN)/netcp	

.PHONY:
clean:
	rm bin/* bin/hierarchy/*
