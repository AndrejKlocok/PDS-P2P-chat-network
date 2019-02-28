SRC_DIR  	= src
LIBS_DIR	= libs
BUILD 		= build


# Set of src/inc files used in build process
HEADERS   	= $(wildcard $(SRC_DIR)/*/*.h)
COMMON_FILES= $(wildcard $(SRC_DIR)/common/*.cpp)
RPC_FILES   = $(wildcard $(SRC_DIR)/rpc/*.cpp)
NODE_FILES 	= $(wildcard $(SRC_DIR)/node/*.cpp)
LIBS_FILES	= $(wildcard $(LIBS_DIR)/*.*)

OBJ			= $(COMMON_FILES:.cpp=.o) $(RPC_FILES:.cpp=.o) $(NODE_FILES:.cpp=.o)


# Compiler/Linker required information
CXX      = g++
CXXFLAGS = -std=c++17 -g -I$(SRC_DIR) -Wall -pedantic -pthread
TARGET_RPC	= pds18-rpc
TARGET_NODE	= pds18-node

RPC		= $(TARGET_RPC).cpp
NODE	= $(TARGET_NODE).cpp
	

all: rpc node


rpc:
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) $(COMMON_FILES) $(RPC_FILES)  $(RPC) -o $(BUILD)/$(TARGET_RPC) 

node:
	$(CXX) $(CXXFLAGS) $(LIBS_FILES) $(COMMON_FILES) $(NODE_FILES)  $(NODE) -o $(BUILD)/$(TARGET_NODE) 

clean:
	rm --recursive --force $(BUILD)/$(TARGET_RPC)