SRC_DIR  	= src
LIBS_DIR	= libs
IP = 192.168.2.95


# Set of src/inc files used in build process
HEADERS   	= $(wildcard $(SRC_DIR)/*/*.h)
COMMON_FILES= $(wildcard $(SRC_DIR)/common/*.cpp)
RPC_FILES   = $(wildcard $(SRC_DIR)/rpc/*.cpp)
NODE_FILES 	= $(wildcard $(SRC_DIR)/node/*.cpp)
PEER_FILES	= $(wildcard $(SRC_DIR)/peer/*.cpp)
LIBS_FILES	= $(wildcard $(LIBS_DIR)/*.a)

OBJ			= $(COMMON_FILES:.cpp=.o) $(RPC_FILES:.cpp=.o) $(NODE_FILES:.cpp=.o) $(PEER_FILES:.cpp=.o)

# Compiler/Linker required information
CXX      = g++
CXXFLAGS = -std=c++17 -g -I$(SRC_DIR) -Wall -pedantic -pthread
TARGET_RPC	= pds18-rpc
TARGET_NODE	= pds18-node
TARGET_PEER	= pds18-peer

RPC		= $(TARGET_RPC).cpp
NODE	= $(TARGET_NODE).cpp
PEER	= $(TARGET_PEER).cpp

all: $(TARGET_RPC) $(TARGET_NODE) $(TARGET_PEER)

rpc: $(TARGET_RPC)

node: $(TARGET_NODE)

peer: $(TARGET_PEER)


$(TARGET_RPC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS_FILES)  -o $@ $^ $(RPC)

$(TARGET_NODE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS_FILES)  -o $@ $^ $(NODE)

$(TARGET_PEER): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS_FILES)  -o $@ $^ $(PEER)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) -c $< -o $@

cleanOBJ:
	rm --recursive --force $(OBJ)

clean:
	rm --recursive --force $(OBJ) $(TARGET_RPC) $(TARGET_NODE) $(TARGET_PEER)

rnode1:
	./pds18-node --id 42 --reg-ipv4 $(IP) --reg-port 8042

rnode2:
	./pds18-node --id 43 --reg-ipv4 $(IP) --reg-port 8043

rnode3:
	./pds18-node --id 44 --reg-ipv4 $(IP)--reg-port 8044

rpeer1:
	./pds18-peer --id 1 --username andrej --chat-ipv4 $(IP)--chat-port 8081  -reg-ipv4 $(IP) --reg-port 8042

rpeer2:
	./pds18-peer --id 2 --username aneta --chat-ipv4 $(IP)--chat-port 8082  -reg-ipv4 $(IP) --reg-port 8043

rpeer3:
	./pds18-peer --id 3 --username jozef --chat-ipv4 $(IP) --chat-port 8083  -reg-ipv4 $(IP) --reg-port 8044
