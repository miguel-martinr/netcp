#############################################
CC = g++
CFLAGS = -g -std=c++11 -pthread
#############################################
#Socket Hierarchy
#revisar 

HCHY_INCLUDE_PATH = include
HCHY_SRC_PATH = src
HCHY_BIN_PATH = bin

HCHY_OBJS = $(HCHY_BIN_PATH)/Socket_base.o $(HCHY_BIN_PATH)/Socket_af.o $(HCHY_BIN_PATH)/Socket_af_dgram.o

#############################################
#Server
#esta organizacion es mejor?
SV_INCLUDE = include/server.hpp
SV_SRC = src/server.cpp
SV_OBJS = bin/server.o


#############################################
#Tests

#Server test
SV_TEST = bin/server_test
SV_TEST_INCLUDE = 
SV_TEST_SRC = src/server_test.cpp
SV_TEST_OBJS = $(SV_OBJS) $(HCHY_OBJS)



#############################################


#netcp

#main program
$(HCHY_BIN_PATH)/netcp: $(HCHY_OBJS) $(HCHY_SRC_PATH)/main.cpp
	$(CC) $(CFLAGS) $(HCHY_SRC_PATH)/main.cpp $(HCHY_OBJS) -o $(HCHY_BIN_PATH)/netcp	

#server
$(SV_TEST): $(SV_TEST_INCLUDE) $(SV_TEST_SRC) $(SV_TEST_OBJS)
	$(CC) $(CFLAGS) $(SV_TEST_SRC) $(SV_TEST_OBJS) -o $(SV_TEST)

$(SV_OBJS): $(SV_INCLUDE) $(SV_SRC) $(HCHY_OBJS)
	$(CC) $(CFLAGS) -c  $(SV_SRC) -o $(SV_OBJS)

#Socket Hierarchy 

$(HCHY_BIN_PATH)/Socket_base.o: $(HCHY_INCLUDE_PATH)/Socket_base.hpp $(HCHY_SRC_PATH)/Socket_base.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC_PATH)/Socket_base.cpp -o $(HCHY_BIN_PATH)/Socket_base.o

$(HCHY_BIN_PATH)/Socket_af.o: $(HCHY_INCLUDE_PATH)/Socket_af.hpp $(HCHY_SRC_PATH)/Socket_af.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC_PATH)/Socket_af.cpp -o $(HCHY_BIN_PATH)/Socket_af.o 

$(HCHY_BIN_PATH)/Socket_af_dgram.o: $(HCHY_INCLUDE_PATH)/Socket_af_dgram.hpp $(HCHY_SRC_PATH)/Socket_af_dgram.cpp
	$(CC) $(CFLAGS) -c $(HCHY_SRC_PATH)/Socket_af_dgram.cpp -o $(HCHY_BIN_PATH)/Socket_af_dgram.o


.PHONY:
clean:
	rm -Rf bin/* 
