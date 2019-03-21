SRC_DIR  	= src
LIBS_DIR	= libs
BUILD 		= build


# Set of src/inc files used in build process
HEADERS   	= $(wildcard $(SRC_DIR)/*/*.h)
COMMON_FILES= $(wildcard $(SRC_DIR)/common/*.cpp)
RPC_FILES   = $(wildcard $(SRC_DIR)/rpc/*.cpp)
NODE_FILES 	= $(wildcard $(SRC_DIR)/node/*.cpp)
PEER_FILES	= $(wildcard $(SRC_DIR)/peer/*.cpp)
LIBS_FILES	= $(wildcard $(LIBS_DIR)/*.*)

OBJ			= $(COMMON_FILES:.cpp=.o) $(RPC_FILES:.cpp=.o) $(NODE_FILES:.cpp=.o)


# Compiler/Linker required information
CXX      = g++
CXXFLAGS = -std=c++17 -g -I$(SRC_DIR) -Wall -pedantic -pthread
TARGET_RPC	= pds18-rpc
TARGET_NODE	= pds18-node
TARGET_PEER	= pds18-peer

RPC		= $(TARGET_RPC).cpp
NODE	= $(TARGET_NODE).cpp
PEER	= $(TARGET_PEER).cpp

all: rpc node peer


rpc:
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) $(COMMON_FILES) $(RPC_FILES)  $(RPC) -o $(BUILD)/$(TARGET_RPC) 

node:
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) $(COMMON_FILES) $(NODE_FILES)  $(NODE) -o $(BUILD)/$(TARGET_NODE) 

peer:
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) $(COMMON_FILES) $(PEER_FILES)  $(PEER) -o $(BUILD)/$(TARGET_PEER) 

clean:
	rm --recursive --force $(BUILD)/$(TARGET_RPC) $(BUILD)/$(TARGET_PEER) $(BUILD)/$(TARGET_NODE)

rnode1:
	./build/pds18-node --id 42 --reg-ipv4 192.168.1.105 --reg-port 8070

rnode2:
	./build/pds18-node --id 43 --reg-ipv4 192.168.1.105 --reg-port 8071

rpeer1:
	./build/pds18-peer --id 1 --username andrej --chat-ipv4 192.168.1.105 --chat-port 8081  -reg-ipv4 192.168.1.105 --reg-port 8070

rpeer2:
	./build/pds18-peer --id 2 --username aneta --chat-ipv4 192.168.1.105 --chat-port 8082  -reg-ipv4 192.168.1.105 --reg-port 8070

rpcMsg:
	./build/pds18-rpc --id 1 --peer --command message --from andrej --to andrej --message "hello"