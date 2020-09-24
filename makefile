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
SV_OBJ = bin/server.o
SV_DEP = $(SV_INCLUDE) $(SV_SRC) $(HCHY_OBJS)


#############################################
#Client
CLI_INCLUDE = include/client.hpp
CLI_SRC = src/client.cpp
CLI_OBJ = bin/client.o
CLI_DEP = $(CLI_INCLUDE) $(CLI_SRC) $(HCHY_OBJS)

#############################################
#Tests

#Server test
SV_TEST = bin/server_test
SV_TEST_INCLUDE = 
SV_TEST_SRC = src/server_test.cpp
SV_TEST_OBJS = $(SV_OBJ) $(HCHY_OBJS) bin/received_info.o

#############################################
#netcp
MAIN_OBJS = bin/received_info.o $(HCHY_OBJS)


#############################################


#netcp

#main program
$(HCHY_BIN_PATH)/netcp: $(MAIN_OBJS) $(HCHY_SRC_PATH)/main.cpp
	$(CC) $(CFLAGS) $(HCHY_SRC_PATH)/main.cpp $(MAIN_OBJS) -o $(HCHY_BIN_PATH)/netcp	


#SERVER

#server test
$(SV_TEST): $(SV_TEST_INCLUDE) $(SV_TEST_SRC) $(SV_TEST_OBJS) 
	$(CC) $(CFLAGS) $(SV_TEST_SRC) $(SV_TEST_OBJS) -o $(SV_TEST)

#server.o
$(SV_OBJ): $(SV_DEP)
	$(CC) $(CFLAGS) -c  $(SV_SRC) -o $(SV_OBJ)


#CLIENT

$(CLI_OBJ): $(CLI_DEP)
	$(CC) $(CFLAGS) -c $(CLI_SRC) -o $(CLI_OBJ)


bin/test_cli_sv: src/test_cli_sv.cpp $(CLI_OBJ) $(SV_OBJ) bin/received_info.o
	$(CC) $(CFLAGS) src/test_cli_sv.cpp $(CLI_OBJ) $(SV_OBJ) $(HCHY_OBJS) bin/received_info.o -o bin/test_cli_sv



#received_info
bin/received_info.o: include/received_info.hpp src/received_info.cpp
	$(CC) $(CFLAGS) -c src/received_info.cpp -o bin/received_info.o


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
