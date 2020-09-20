#############################################
CC = g++
CFLAGS = -g -std=c++11 -pthread
#############################################
#Socket Hierarchy

HCHY_INCLUDE = include/
HCHY_SRC = src/
HCHY_BIN = bin/

HCHY_OBJS = $(HCHY_BIN)/Socket_base.o $(HCHY_BIN)/Socket_af.o $(HCHY_BIN)/Socket_af_dgram.o

#############################################


#netcp

$(HCHY_BIN)/netcp: $(HCHY_OBJS) $(HCHY_SRC)/main.cpp
	$(CC) $(CFLAGS) $(HCHY_SRC)/main.cpp $(HCHY_OBJS) -o $(HCHY_BIN)/netcp	


#Socket Hierarchy 

$(HCHY_BIN)/Socket_base.o: $(HCHY_INCLUDE)/Socket_base.hpp $(HCHY_SRC)/Socket_base.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_base.cpp -o $(HCHY_BIN)/Socket_base.o

$(HCHY_BIN)/Socket_af.o: $(HCHY_INCLUDE)/Socket_af.hpp $(HCHY_SRC)/Socket_af.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_af.cpp -o $(HCHY_BIN)/Socket_af.o

$(HCHY_BIN)/Socket_af_dgram.o: $(HCHY_INCLUDE)/Socket_af_dgram.hpp $(HCHY_SRC)/Socket_af_dgram.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC)/Socket_af_dgram.cpp -o $(HCHY_BIN)/Socket_af_dgram.o


.PHONY:
clean:
	rm bin/* 
